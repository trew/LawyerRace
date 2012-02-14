#include "Rock.h"

std::list<Rock*> Rock::s_rockList;

Rock::Rock() {
}

Rock::Rock(const char* _fileName, const int _xPos, const int _yPos, const int _rockType) 
: Entity(_fileName, _xPos, _yPos),
m_expired(false)
{
	m_vel = R_1_VELOCITY;
	m_height = R_1_HEIGHT;
	m_width = R_1_WIDTH;

	if (_rockType == 2) {
		m_vel = R_2_VELOCITY;
		m_height = R_2_HEIGHT;
		m_width = R_2_WIDTH;
	}
	else if (_rockType == 3) {
		m_vel = R_3_VELOCITY;
		m_height = R_3_HEIGHT;
		m_width = R_3_WIDTH;
	}
}

Rock::~Rock() {
}

void Rock::draw(SDL_Surface* _destSurf) {
	Entity::draw(_destSurf);
}

void Rock::update() {
	m_yPos += (FPS::FPSControl.GetSpeedFactor() * m_vel);
	if (m_yPos > W_HEIGHT) m_expired = true;
}

bool Rock::isExpired() const {
	return m_expired;
}

void Rock::expire() {
	m_expired = true;
}