#include "LawyerRace/Entity/Entity.hpp"
#include "LawyerRace/Core/Gameconfig.hpp"
#include <iostream>

Entity::Entity() {
}

Entity::Entity(TextureRegion* region) {
	m_regions.push_back(region);
	m_width = (float)region->getRegionWidth();
	m_height = (float)region->getRegionHeight();
}

Entity::Entity(TextureRegion* region, const float x, const float y, const float w, const float h) : m_x(x), m_y(y), m_width(w), m_height(h), m_prevX(x), m_prevY(y) {
	m_regions.push_back(region);
}

Entity::Entity(std::vector<TextureRegion*> regions) : Entity(regions, 0, 0) {
}

Entity::Entity(std::vector<TextureRegion*> regions, const float x, const float y) : m_x(x), m_y(y), m_prevX(x), m_prevY(y) {
	if (regions.empty()) return;
	m_regions.insert(m_regions.end(), regions.begin(), regions.end());
	m_width = (float)m_regions.front()->getRegionWidth();
	m_height = (float)m_regions.front()->getRegionHeight();
}

Entity::Entity(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h) : m_x(x), m_y(y), m_width(w), m_height(h), m_prevX(x), m_prevY(y) {
	m_regions.insert(m_regions.end(), regions.begin(), regions.end());
}

Entity::~Entity() {
}

void Entity::copyDataForInterpolation() {
	m_prevX = m_x;
	m_prevY = m_y;
}

//Static functions

bool Entity::collides(Entity* _entityA, Entity* _entityB) {
    //topA < bottomB
    //topB < bottomA
    //rightA < leftB
    //rightB < leftA

    if ((_entityA->m_x + _entityA->m_width < _entityB->m_x)) return false;
    if ((_entityB->m_x + _entityB->m_width < _entityA->m_x)) return false;
    if ((_entityA->m_y + _entityA->m_height < _entityB->m_y)) return false;
    if ((_entityB->m_y + _entityB->m_height < _entityA->m_y)) return false;

    return true;
}

void Entity::render(SDL_Renderer* renderer, float timeAlpha, unsigned int index) {
	if (!isVisible()) return;
	if (index >= m_regions.size() || index < 0) return;

	float x = lerp(m_prevX, m_x, timeAlpha);
	float y = lerp(m_prevY, m_y, timeAlpha);

	TextureRegion* region = m_regions[index];

	SDL_Rect destRect;
	destRect.x = (int)x;
	destRect.y = (int)y;
	destRect.h = (int)m_height;
	destRect.w = (int)m_width;

	SDL_RenderCopy(renderer, region->getTexture()->getTexture(), &region->getRect(), &destRect);
}

void Entity::render(SDL_Renderer* renderer, float timeAlpha) {
	Entity::render(renderer, timeAlpha, 0);
}

void Entity::update(float timeStep) {
}

float Entity::getX() const {
	return m_x;
}

float Entity::getY() const {
	return m_y;
}

void Entity::setX(float x) {
	m_x = x;
}

void Entity::setY(float y) {
	m_y = y;
}

float Entity::getWidth() const {
	return m_width;
}

float Entity::getHeight() const {
	return m_height;
}

void Entity::setWidth(float w) {
	if (w > 0) m_width = w;
}

void Entity::setHeight(float h) {
	if (h > 0) m_height = h;
}

float Entity::getVelocityX() const {
	return m_xVel;
}

float Entity::getVelocityY() const {
	return m_yVel;
}

void Entity::setVelocity(const float x, const float y) {
	m_xVel = x;
	m_yVel = y;
}

float Entity::getPreviousX() const {
	return m_prevX;
}

float Entity::getPreviousY() const {
	return m_prevY;
}

void Entity::setPreviousX(const float x) {
	m_prevX = x;
}

void Entity::setPreviousY(const float y) {
	m_prevY = y;
}

bool Entity::isMoving() const {
	return m_moving;
}

void Entity::setMoving(bool moving) {
	m_moving = moving;
}

bool Entity::isVisible() const {
	return m_visible;
}

void Entity::setVisible(bool visible) {
	m_visible = visible;
}

EntityManager* const Entity::getManager() const {
	return manager;
}

float Entity::lerp(float start, float end, float alpha) {
	if (config::ENABLE_LERP)
		return start + (end - start) * alpha;
	return end;
}
