#include "Rock.h"

std::list<Rock*> Rock::s_rockList;

Rock::Rock() {
}

Rock::Rock(const std::string _fileName, const int _xPos, const int _yPos, const int _rockType) 
: Entity(_fileName, _xPos, _yPos),
m_expired(false)
{
	m_vel = config::R_VELOCITY[0];
	m_height = config::R_HEIGHT[0];
	m_width = config::R_WIDTH[0];

	if (_rockType == 2) {
		m_vel = config::R_VELOCITY[1];
		m_height = config::R_HEIGHT[1];
		m_width = config::R_WIDTH[1];
	}
	else if (_rockType == 3) {
		m_vel = config::R_VELOCITY[2];
		m_height = config::R_HEIGHT[2];
		m_width = config::R_WIDTH[2];
	}
}

Rock::~Rock() {
}

void Rock::draw(SDL_Surface* _destSurf) {
	Entity::draw(_destSurf);
}

void Rock::update() {
	m_yPos += (FPS::FPSControl.GetSpeedFactor() * m_vel);
	if (m_yPos > config::W_HEIGHT) m_expired = true;
}

bool Rock::isExpired() const {
	return m_expired;
}

void Rock::expire() {
	m_expired = true;
}
