#ifndef LWR_TEXTUREATLAS_HPP
#define LWR_TEXTUREATLAS_HPP

#include <string>
#include <vector>
#include <memory>
#include "LawyerRace/Graphics/Texture.hpp"
#include "LawyerRace/Graphics/TextureRegion.hpp"

class AtlasRegion : public TextureRegion {
friend class TextureAtlas;
public:
	virtual ~AtlasRegion();
	std::string getName() const;
	int getIndex() const;

private:
	AtlasRegion(std::string name, int index, Texture* t, int x, int y, int w, int h);
	std::string name;
	int index;

};



class TextureAtlas {
public:
	TextureAtlas(SDL_Renderer* renderer, std::string _file);
	~TextureAtlas();

	TextureRegion* findRegion(std::string name);
	TextureRegion* findRegion(std::string name, int index);
	std::vector<TextureRegion*> findRegions(std::string name);

private:
	std::vector<std::unique_ptr<Texture>> textures;
	std::vector<std::unique_ptr<AtlasRegion>> regions;

	std::string m_fileName;

	void load();
	SDL_Renderer* renderer{ NULL };
};

#endif