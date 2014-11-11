#ifndef LWR_ENTITY_HPP
#define LWR_ENTITY_HPP

#include "LawyerRace/Entity/EntityManager.hpp"
#include "LawyerRace/Graphics/TextureRegion.hpp"
#include <string>
#include <vector>

class Entity {
friend class EntityManager;

public:
    Entity();
	Entity(TextureRegion* region);
	Entity(TextureRegion* region, const float x, const float y, const float w, const float h);
	Entity(std::vector<TextureRegion*> regions);
	Entity(std::vector<TextureRegion*> regions, const float x, const float y);
	Entity(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h);

    virtual ~Entity();

	void copyDataForInterpolation();

    /**
     *  Checks for collision between 2 entities
     *
     *  @param _entityA The first entity
     *  @param _entityB The second entity
     *  @return True if the entities intersect, False otherwise
     */
    static bool collides(Entity* const _entityA, Entity* const _entityB);

	virtual void render(SDL_Renderer* renderer, float timeAlpha, unsigned int index);
	virtual void render(SDL_Renderer* renderer, float timeAlpha);
	virtual void update(float timeStep);

	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);

	float getWidth() const;
	float getHeight() const;
	void setWidth(float w);
	void setHeight(float h);

	float getVelocityX() const;
	float getVelocityY() const;
	void setVelocity(const float x, const float y);

	float getPreviousX() const;
	float getPreviousY() const;

	void setPreviousX(const float x);
	void setPreviousY(const float y);

	bool isMoving() const;
	void setMoving(bool moving);

	bool isVisible() const;
	void setVisible(bool visible);

	float lerp(float start, float end, float alpha);

protected:
	EntityManager* const getManager() const;

private:
	EntityManager* manager{ NULL };
	std::vector<TextureRegion*> m_regions;

	bool m_visible{ true };
	float m_x{ 0 };
	float m_y{ 0 };
	float m_width{ 0 };
	float m_height{ 0 };

	float m_xVel{ 0 };
	float m_yVel{ 0 };
	float m_prevX{ 0 };
	float m_prevY{ 0 };
	bool m_moving{ false };

	bool m_shouldBeRemoved{ false };
};

#endif
