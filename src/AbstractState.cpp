#include "AbstractState.hpp"

AbstractState::AbstractState(GameEngine* engine) : m_engine(engine) {
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