#include "Rock.hpp"
#include "Log.hpp"

std::list<Rock*> Rock::s_rockList;

Rock::Rock() {
}

Rock::Rock(const std::string _fileName, const int _xPos, const int _yPos, const int _rockType) 
: Entity(_fileName, _xPos, _yPos),
m_expired(false)
{
    if (_rockType < 0 || _rockType > 3) {
        LOG_ERROR << "Tried to create rock of unsupported type.\n";
        return;
    }

    m_vel = config::R_VELOCITY[_rockType-1];
    m_height = config::R_HEIGHT[_rockType-1];
    m_width = config::R_WIDTH[_rockType-1];
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
