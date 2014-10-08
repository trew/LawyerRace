#include "MovingEntity.hpp"

MovingEntity::MovingEntity(std::string _fileName, float _xPos, float _yPos, float _xVel, float _yVel) : Entity(_fileName, _xPos, _yPos) {
	m_moving = false;
	m_xVel = _xVel;
	m_yVel = _yVel;
}

MovingEntity::~MovingEntity() {
}

void MovingEntity::draw(SDL_Surface* _destSurf, float timeAlpha) {
	if (!isVisible()) return;

	float x = lerp(m_prevX, m_xPos, timeAlpha);
	float y = lerp(m_prevY, m_yPos, timeAlpha);
	Sprite::draw(_destSurf, x, y);
}

float MovingEntity::getVelocityX() const {
	return m_xVel;
}

float MovingEntity::getVelocityY() const {
	return m_yVel;
}

void MovingEntity::setVelocity(const float x, const float y) {
	m_xVel = x;
	m_yVel = y;
}

bool MovingEntity::isMoving() const {
	return m_moving;
}

void MovingEntity::setMoving(bool moving) {
	m_moving = moving;
}

float MovingEntity::lerp(float start, float end, float alpha) {
	if (config::ENABLE_LERP)
		return start + (end - start) * alpha;
	return end;
}
