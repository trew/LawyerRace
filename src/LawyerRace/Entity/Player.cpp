#include <LawyerRace/Entity/Player.hpp>
#include <iostream>
#include <sstream>
#include <LawyerRace/Utils/PositionHelper.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>

int Player::alivePlayers = 0;

Player::Player(const int player,
               const std::vector<lwe::TextureRegion*>& regions,
               SDL_Renderer* const renderer,
               const PlayerControls& controls)
  : Player(player,
           regions,
           renderer,
           0,
           0,
           Config::getInstance().getPlayerWidth(),
           Config::getInstance().getPlayerHeight(),
           controls)
{
}

Player::Player(const int player,
               const std::vector<lwe::TextureRegion*>& regions,
               SDL_Renderer* const renderer,
               const float x,
               const float y,
               const float w,
               const float h,
               const PlayerControls& controls)
  : AbstractEntity(regions, x, y, w, h), renderer(renderer)
{
  alivePlayers++;
  playerNum = player;

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

  setVelocity(Config::getInstance().getPlayerVelocity(), Config::getInstance().getPlayerVelocity());
}

Player::~Player()
{
}

void Player::render(SDL_Renderer* const renderer, const float timeAlpha)
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
    if (Config::getInstance().isPlayerStopEnabled())
    {
      setMoving(!isMoving());
      return true;
    }
  }

  return false;
}


void Player::update(const float timeStep)
{
  if (!isMoving() || dead)
  {
    return; //Return if no movement
  }

  Config& config = Config::getInstance();

  const int ww = config.getGameWidth();
  const int wh = config.getGameHeight();

  if (m_direction == UP)
  {
    setY(getY() - (getVelocityY() * timeStep));
    if (getY() < 0)
    {
      setY(0); //Prevent from going out of screen
      setMoving(false);
    }
  }
  else if (m_direction == DOWN)
  {
    setY(getY() + (getVelocityY() * timeStep));
    if (getY() + getHeight() > wh)
    {
      setY((float)wh - getHeight()); //Prevent from going out of screen
      setMoving(false);
    }
  }

  else if (m_direction == LEFT)
  {
    setX(getX() - (getVelocityX() * timeStep));
    if (getX() < 0)
    {
      setX(0); //Prevent from going out of screen
      setMoving(false);
    }
  }
  else if (m_direction == RIGHT)
  {
    setX(getX() + (getVelocityX() * timeStep));
    if (getX() + getWidth() > ww)
    {
      setX((float)ww - getWidth()); //Prevent from going out of screen
      setMoving(false);
    }
  }
}

void Player::updateScore()
{
  std::stringstream ss;
  if (dead)
  {
    ss << "Player " << playerNum << ": " << getScore() << " DEAD!";
  }
  else
  {
    ss << "Player " << playerNum << ": " << getScore();
  }
  scoreText->updateText(ss.str());
  scoreText->ensureTextUpdated();

  // Position text correctly
  using namespace positionHelper;

  Config& config = Config::getInstance();

  if (config.getPlayerCount() == 4)
  {
    float newXPos = (float)((config.getGameWidth() / 4.f) * (playerNum - 1) + 20);
    scoreText->setX(newXPos);
  }
  else if (config.getPlayerCount() == 3)
  {
    if (playerNum == 1)
    {
      scoreText->setX(leftAlign(0, 10));
    }
    else if (playerNum == 2)
    {
      scoreText->setX(centerHorizontal(0, (float)config.getGameWidth(), scoreText->getWidth()));
    }
    else if (playerNum == 3)
    {
      scoreText->setX(rightAlign((float)config.getGameWidth(), 10, scoreText->getWidth()));
    }
  }
  else if (config.getPlayerCount() == 2)
  {
    if (playerNum == 1)
    {
      scoreText->setX(leftAlign(0, 10));
    }
    else if (playerNum == 2)
    {
      scoreText->setX(rightAlign((float)config.getGameWidth(), 10, scoreText->getWidth()));
    }
  } 
  else if (config.getPlayerCount() == 1)
  {
    scoreText->setX(centerHorizontal(0, (float)config.getGameWidth(), scoreText->getWidth()));
  }
}

int Player::getScore() const
{
  return score;
}

void Player::setScore(const int s)
{
  if (score != s)
  {
    score = s;
    updateScore();
  }
}

void Player::setDead(const bool d)
{
  if (dead == d)
  {
    return;
  }

  dead = d;
  if (d)
  {
    setMoving(false);
    alivePlayers--;
    updateScore();
  }
  else
  {
    alivePlayers++;
    updateScore();
  }
}

bool Player::isDead() const
{
  return dead;
}

void Player::setDirection(const Direction newDir)
{
  m_direction = newDir;
}
