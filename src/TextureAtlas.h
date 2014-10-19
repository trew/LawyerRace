#ifndef _TEXTUREATLAS_H_
#define _TEXTUREATLAS_H_

#include <string>
#include <vector>
#include <memory>
#include "Texture.h"
#include "TextureRegion.h"

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
	TextureAtlas(std::string _file);
	~TextureAtlas();

	TextureRegion* findRegion(std::string name);
	TextureRegion* findRegion(std::string name, int index);
	std::vector<TextureRegion*> findRegions(std::string name);

private:
	std::vector<std::unique_ptr<Texture>> textures;
	std::vector<std::unique_ptr<AtlasRegion>> regions;

	std::string m_fileName;

	void load();
};

#endif