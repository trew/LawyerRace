#include "LawyerRace/Core/AbstractState.hpp"

AbstractState::AbstractState() {
}

AbstractState::~AbstractState() {
}

GameEngine* AbstractState::getEngine() {
	return m_engine;
}

void AbstractState::copyDataForInterpolation() {
}

void AbstractState::pause() {
}

void AbstractState::resume() {
}