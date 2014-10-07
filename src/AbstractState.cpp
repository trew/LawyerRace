#include "AbstractState.hpp"

AbstractState::AbstractState(GameEngine* engine) : m_engine(engine) {
}

AbstractState::~AbstractState() {
}

GameEngine* AbstractState::GetEngine() {
	return m_engine;
}

void AbstractState::Pause() {
}

void AbstractState::Resume() {
}