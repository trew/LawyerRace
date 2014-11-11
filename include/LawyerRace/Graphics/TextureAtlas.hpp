#ifndef LWR_TEXTUREATLAS_HPP
#define LWR_TEXTUREATLAS_HPP

#include <string>
#include <vector>
#include <memory>
#include "LawyerRace/Graphics/Texture.hpp"
#include "LawyerRace/Graphics/TextureRegion.hpp"
#include "LawyerRace/Utils/Filesystem.hpp"

class AtlasRegion : public TextureRegion {
friend class TextureAtlas;
public:
	virtual ~AtlasRegion();
	std::string getName() const { return name; }
	int getIndex() const { return index; }

private:
	AtlasRegion(std::string name, int index, Texture* t, int x, int y, int w, int h);
	std::string name;
	int index;

};



class TextureAtlas {
public:
	TextureAtlas(SDL_Renderer* renderer, File* _file);
	~TextureAtlas();

	TextureRegion* findRegion(std::string name);
	TextureRegion* findRegion(std::string name, int index);
	std::vector<TextureRegion*> findRegions(std::string name);

	bool isLoaded() const { return loaded; }
private:
	std::vector<Texture*> textures;
	std::vector<AtlasRegion*> regions;

	bool loaded{ false };
	File* m_file;

	void load();
	SDL_Renderer* renderer{ NULL };
};

#endif