#include "LawyerRace/Graphics/TextureAtlas.hpp"
#include "TinyXML/tinyxml2.h"
#include "LawyerRace/Utils/Log.hpp"
#include "LawyerRace/Utils/Filesystem.hpp"
#include "LawyerRace/Core/GameEngine.hpp"

#include <SDL_image.h>

AtlasRegion::AtlasRegion(std::string name, int index, Texture* t, int x, int y, int w, int h) 
	: TextureRegion(t, x, y, w, h), name(name), index(index) {
}

AtlasRegion::~AtlasRegion() {
}

TextureAtlas::TextureAtlas(SDL_Renderer* renderer, File* _file) : renderer(renderer), m_file(_file) {
	load();
}

TextureAtlas::~TextureAtlas() {
	for (auto& texture : textures) {
		delete texture;
	}
	for (auto& region : regions) {
		delete region;
	}
}

bool endsWith(std::string string, std::string suffix) {
	if (string.length() >= suffix.length())
		return (0 == string.compare(string.length() - suffix.length(), suffix.length(), suffix));
	return false;
}

std::string getFileExtension(std::string fileName) {
	auto extensionPos = fileName.rfind(".");
	if (extensionPos != std::string::npos)
		return fileName.substr(extensionPos);
	return "";
}

std::string getFileWithoutExtension(std::string fileName) {
	std::string extension = getFileExtension(fileName);
	if (extension != "") {
		return fileName.substr(0, fileName.rfind(extension));
	}
	else
		return fileName;
}

void TextureAtlas::load() {
	std::vector<std::string> files;

	// Are we dealing with a multipage spritesheet?
	std::string fileNameWithoutExtension = getFileWithoutExtension(m_file->getFileName());
	if (fileNameWithoutExtension.rfind("_") != std::string::npos) {
		SDL_Log("Loading multipage atlas");
		int i = 0;
		while (true) {
			std::string indexS = std::to_string(i);
			std::string fileName = m_file->getFileName() + "_" + indexS + ".xml";

			if (!filesys::fileExists(fileName))
				break;

			files.push_back(fileName);
			i++;
		}
	}
	else {
		if (!filesys::fileExists(m_file->getFileName())) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "File not found: %s", m_file->getFileName().c_str());
			return;
		}
		files.push_back(m_file->getFileName());
		SDL_Log("Loading single page atlas");
	}

	if (files.empty()) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "No atlas files found. %s", m_file->getFileName().c_str());
		return;
	}

	int pageNumber = 0;
	using namespace tinyxml2;
	for (std::string fileName : files) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str())) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load atlas file %s", fileName.c_str());
		}
		else {
			XMLElement* root = doc.FirstChildElement();
			std::string textureFileName = std::string(root->Attribute("imagePath"));

			SDL_Surface* loadedSurface = IMG_Load(textureFileName.c_str());
			if (loadedSurface == NULL) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load texture %s", textureFileName.c_str());
				continue;
			}
			SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from loaded file: %s", textureFileName.c_str());
				continue;
			}
			SDL_FreeSurface(loadedSurface);

			Texture* texture = new Texture(newTexture);
			SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Texture %s loaded successfully.");

			textures.push_back(texture);

			// find all texture regions
			XMLElement* sprite = root->FirstChildElement("sprite");

			while (sprite != NULL) {
				int x, y, w, h;
				x = y = w = h = -1;
				sprite->QueryIntAttribute("x", &x);
				sprite->QueryIntAttribute("y", &y);
				sprite->QueryIntAttribute("w", &w);
				sprite->QueryIntAttribute("h", &h);
				const char* nameStr = sprite->Attribute("n");
				std::string name = nameStr != NULL ? nameStr : "";

				// name.length must be 5 or more to be able to fit ".png" extension
				if (x < 0 || y < 0 || w < 0 || h < 0 || name.length() < 5) {
					SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error reading sprite in XML");
				}
				else {
					name.erase(name.length() - 4, 4); // strip ".png"
					// parse the end and see if it ends with "_<number>"
					// if so, set the number to be the index
					int index = 0;
					int i = name.find_last_of('_');
					if (i != std::string::npos && i != name.size() - 1) {


						std::string numberPart = name.substr(i + 1, name.length() - i);
						int number = atoi(numberPart.c_str());
						index = number;
						if (index < 0) index = 0;

						int numberCount = name.size() - 1 - i;
						name.erase(i, numberCount + 1);
					}

					regions.push_back(new AtlasRegion(name, index, texture, x, y, w, h));
				}
				sprite = sprite->NextSiblingElement("sprite");
			}

		}
		pageNumber++;
	}
	loaded = true;
}

TextureRegion* TextureAtlas::findRegion(std::string name) {
	for (auto& ptr : regions) {
		if (ptr->name == name)
			return ptr;
	}
	return NULL;
}

TextureRegion* TextureAtlas::findRegion(std::string name, int index) {
	for (auto& ptr : regions) {
		if (ptr->index == index && ptr->name == name)
			return ptr;
	}
	return NULL;
}

std::vector<TextureRegion*> TextureAtlas::findRegions(std::string name) {
	std::vector<TextureRegion*> matched;
	for (auto& ptr : regions) {
		if (ptr->name == name)
			matched.push_back(ptr);
	}
	return matched;
}