#include "TextureAtlas.h"
#include "TinyXML\tinyxml2.h"
#include "Log.hpp"
#include "Filesystem.hpp"
#include "GameEngine.hpp"

AtlasRegion::AtlasRegion(std::string name, int index, Texture* t, int x, int y, int w, int h) 
	: TextureRegion(t, x, y, w, h), name(name), index(index) {
}

AtlasRegion::~AtlasRegion() {
}

std::string AtlasRegion::getName() const {
	return name;
}

TextureAtlas::TextureAtlas(SDL_Renderer* renderer, std::string _file) : renderer(renderer), m_fileName(_file) {
	load();
}

TextureAtlas::~TextureAtlas() {
}

void TextureAtlas::load() {

	// Find all files for this atlas
	// each page has its own xml-file and its own texture
	// they are named like this:
	//   <name>_<pageNumber>.<xml/png>
	// pagenumber starts on 0

	std::vector<std::string> files;
	int i = 0;
	while (true) {
		std::string indexS = std::to_string(i);
		std::string fileName = "img/" + m_fileName + "_" + indexS + ".xml";

		if (!filesys::file_exists(fileName))
			break;

		files.push_back(fileName);
		i++;
	}

	int pageNumber = 0;
	using namespace tinyxml2;
	for (std::string fileName : files) {
		XMLDocument doc;
		if (doc.LoadFile(fileName.c_str())) {
			LOG_ERROR << "Couldn't load textures\n";
		}
		else {
			XMLElement* root = doc.FirstChildElement();
			std::string textureFileName = "img/" + std::string(root->Attribute("imagePath"));

			std::unique_ptr<Texture> texture(Texture::createTexture(renderer, textureFileName));

			Texture* texturePtr = texture.get(); // save the raw pointer for textureregion creation later
			textures.push_back(std::move(texture));

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
					LOG_ERROR << "Error reading sprite in XML\n";
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

					regions.push_back(std::unique_ptr<AtlasRegion>(new AtlasRegion(name, index, texturePtr, x, y, w, h)));
				}
				sprite = sprite->NextSiblingElement("sprite");
			}

		}
		pageNumber++;
	}
}

TextureRegion* TextureAtlas::findRegion(std::string name) {
	for (auto& ptr : regions) {
		if (ptr->name == name)
			return ptr.get();
	}
	return NULL;
}

TextureRegion* TextureAtlas::findRegion(std::string name, int index) {
	for (auto& ptr : regions) {
		if (ptr->index == index && ptr->name == name)
			return ptr.get();
	}
	return NULL;
}

std::vector<TextureRegion*> TextureAtlas::findRegions(std::string name) {
	std::vector<TextureRegion*> matched;
	for (auto& ptr : regions) {
		if (ptr->name == name)
			matched.push_back(ptr.get());
	}
	return matched;
}