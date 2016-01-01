#include <LawyerRace/Entity/Player.hpp>
#include <iostream>
#include <sstream>
#include <LawyerRace/Utils/PositionHelper.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>

int Player::alivePlayers = 0;
int Player::currentPlayerNum = 0;

Player::Player(const std::vector<lwe::TextureRegion*>& regions, SDL_Renderer* const renderer, const PlayerControls& controls)
  : Player(regions, renderer, 0, 0, config::P_WIDTH, config::P_HEIGHT, controls)
{
}

Player::Player(const std::vector<lwe::TextureRegion*>& regions,
               SDL_Renderer* const renderer,
               const float x,
               const float y,
               const float w,
               const float h,
               const PlayerControls& controls)
  : AbstractEntity(regions, x, y, w, h), renderer(renderer)
{
  currentPlayerNum++;
  alivePlayers++;
  playerNum = currentPlayerNum;

  if(playerNum == 1)
  {
    scoreText = std::make_shared<lwe::Text>(renderer, LawyerRace::standardFont.get(), " ", 12, 0.f, 0.f, 70, 70, 230);
  }
  else if (playerNum == 2)
  {
    scoreText = std::make_shared<lwe::Text>(renderer, LawyerRace::standardFont.get(), " ", 12, 0.f, 0.f, 230, 0, 0);
  }
  else if (playerNum == 3)
  {
    scoreText = std::make_shared<lwe::Text>(renderer, LawyerRace::standardFont.get(), " ", 12, 0.f, 0.f, 0, 230, 0);
  }
  else if (playerNum == 4)
  {
    scoreText = std::make_shared<lwe::Text>(renderer, LawyerRace::standardFont.get(), " ", 12, 0.f, 0.f, 230, 230, 0);
  }
  updateScore();
  this->controls = controls;

  setVelocity(config::P_VELOCITY, config::P_VELOCITY);
}

Player::~Player()
{
}

void Player::render(SDL_Renderer* const renderer, float timeAlpha)
{
  AbstractEntity::render(renderer, timeAlpha, dead ? 4 : m_direction);
  scoreText->render();
}

bool Player::handleEvent(const SDL_Event& ev)
{
  if (dead)
  {
    return false;
  }

  if (controls.getUp()(ev))
  {
    setMoving(true);
    setDirection(UP);
    return true;
  }
  else if (controls.getDown()(ev))
  {
    setMoving(true);
    setDirection(DOWN);
    return true;
  }
  else if (controls.getLeft()(ev))
  {
    setMoving(true);
    setDirection(LEFT);
    return true;
  }
  else if (controls.getRight()(ev))
  {
    setMoving(true);
    setDirection(RIGHT);
    return true;
  }
  else if (controls.getStop()(ev))
  {
    if (config::PLAYER_STOP_ENABLED)
    {
      setMoving(!isMoving());
      return true;
    }
  }

  return false;
}


void Player::update(float timeStep)
{
  if (!isMoving() || dead)
  {
    return;    //Return if no movement
  }

  if (m_direction == UP)
  {
    setY(getY() - (getVelocityY() * timeStep));
    if (getY() < 0)
    {
      setY(0); //Prevent from going out of screen
    }
  }
  else if (m_direction == DOWN)
  {
    setY(getY() + (getVelocityY() * timeStep));
    if (getY() + getHeight() > config::W_HEIGHT)
    {
      setY(static_cast<float>(config::W_HEIGHT - getHeight())); //Prevent from going out of screen
    }
  }

  else if (m_direction == LEFT)
  {
    setX(getX() - (getVelocityX() * timeStep));
    if (getX() < 0)
    {
      setX(0); //Prevent from going out of screen
    }
  }
  else if (m_direction == RIGHT)
  {
    setX(getX() + (getVelocityX() * timeStep));
    if (getX() + getWidth() > config::W_WIDTH)
    {
      setX(static_cast<float>(config::W_WIDTH - getWidth())); //Prevent from going out of screen
    }
  }
}

void Player::updateScore()
{
  std::stringstream ss;
  if (dead)
  {
    ss << "Player " << playerNum << ": " << m_score << " DEAD!";
  }
  else
  {
    ss << "Player " << playerNum << ": " << m_score;
  }
  scoreText->updateText(ss.str());
  scoreText->ensureTextUpdated();

  using namespace positionHelper;
  //Position text correctly
  if (config::NUM_OF_PLAYERS == 4)
  {
    float newXPos = (float)((config::W_WIDTH / 4.f) * (playerNum-1) + 20);
    scoreText->setX(newXPos);
  }
  else if (config::NUM_OF_PLAYERS == 3)
  {
    if (playerNum == 1)
    {
      scoreText->setX(leftAlign(0, 10));
    }
    else if (playerNum == 2)
    {
      scoreText->setX(centerHorizontal(0, (float)config::W_WIDTH, scoreText->getWidth()));
    }
    else if (playerNum == 3)
    {
      scoreText->setX(rightAlign((float)config::W_WIDTH, 10, scoreText->getWidth()));
    }
  }
  else if (config::NUM_OF_PLAYERS == 2)
  {
    if (playerNum == 1)
    {
      scoreText->setX(leftAlign(0, 10));
    }
    else if (playerNum == 2)
    {
      scoreText->setX(rightAlign((float)config::W_WIDTH, 10, scoreText->getWidth()));
    }
  } 
  else if (config::NUM_OF_PLAYERS == 1)
  {
    scoreText->setX(centerHorizontal(0, (float)config::W_WIDTH, scoreText->getWidth()));
  }
}

void Player::incScore(int _score) {
  m_score += _score;
  updateScore();
}

void Player::kill() {
  dead = true;
  setMoving(false);
  alivePlayers--;
  updateScore();
}

bool Player::isDead() const{
  return dead;
}

int Player::getScore() const {
  return m_score;
}


void Player::setDirection(Direction newDir) {
  m_direction = newDir;
}
