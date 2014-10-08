#ifndef _MOVINGENTITY_H_
#define _MOVINGENTITY_H_

#include "Entity.hpp"

class MovingEntity : public Entity {
public:
	MovingEntity(std::string _fileName, float _xPos, float _yPos, float _xVel, float _yVel);
	~MovingEntity();

	virtual void draw(SDL_Surface* dest, float timeAlpha);

	float getVelocityX() const;
	float getVelocityY() const;

	void setVelocity(const float x, const float y);

	bool isMoving() const;
	void setMoving(bool moving);

	float lerp(float start, float end, float alpha);
private:
	float m_xVel;
	float m_yVel;
	bool m_moving;
};

#endif