#include <LawyerEngine/LawyerEngine.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <LawyerRace/Core/MenuState.hpp>
#include <iostream>
#include <LawyerRace/Utils/PositionHelper.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>

using namespace positionHelper;

GameState::GameState()
{
  entityManager = std::make_unique<lwe::EntityManager>();
  m_player[0] = NULL;
  m_player[1] = NULL;
  m_player[2] = NULL;
  m_player[3] = NULL;

  pausedExitToMainMenuCondition.addTrigger(new lwe::KeyboardTrigger(SDLK_ESCAPE));
  pausedExitToMainMenuCondition.addTrigger(new lwe::GameControllerButtonTrigger(SDL_CONTROLLER_BUTTON_B));

  gameOverExitToMainMenuCondition.addTrigger(new lwe::KeyboardTrigger(SDLK_RETURN));
  gameOverExitToMainMenuCondition.addTrigger(new lwe::GameControllerButtonTrigger(SDL_CONTROLLER_BUTTON_A));
  pauseCondition.addTrigger(new lwe::KeyboardTrigger(SDLK_PAUSE, true));
  pauseCondition.addTrigger(new lwe::GameControllerButtonTrigger(SDL_CONTROLLER_BUTTON_START, true));
}

/* RUN ONCE FUNCTIONS */

bool GameState::init()
{
  
  LOG_DEBUG("Loading textures");
  {
    atlas = getEngine()->getAssetManager()->get<lwe::TextureAtlas>(config::path + "img/spritesheet_0");
  }

  LOG_DEBUG("Loading players...");

  float wh = (float)config::W_HEIGHT;
  float ww = (float)config::W_WIDTH;
  for (int i = 0; i < config::NUM_OF_PLAYERS; i++)
  {
    m_player[i] = entityManager->create<Player>(atlas->findRegions(config::P_SRC[i]),
                                                getEngine()->getRenderer(),
                                                0.f,
                                                0.f,
                                                config::P_WIDTH,
                                                config::P_HEIGHT,
                                                config::CONTROLS[i]);
    m_player[i]->setY(centerVertical(0, wh, m_player[i]->getHeight()));
  }

  if (config::NUM_OF_PLAYERS == 1)
  {
    m_player[0]->setX(centerHorizontal(0, ww, m_player[0]->getWidth()));
  }
  else if (config::NUM_OF_PLAYERS == 2)
  {
    m_player[0]->setX(centerHorizontal(0, ww - (m_player[0]->getWidth() * 3), m_player[0]->getWidth()));
    m_player[1]->setX(centerHorizontal(m_player[1]->getWidth() * 3, ww, m_player[1]->getWidth()));
  }
  else if (config::NUM_OF_PLAYERS == 3)
  {
    m_player[0]->setX(centerHorizontal(0, ww - (m_player[0]->getWidth() * 6), m_player[0]->getWidth()));
    m_player[1]->setX(centerHorizontal(0, ww, m_player[1]->getWidth()));
    m_player[2]->setX(centerHorizontal((m_player[0]->getWidth() * 6), ww, m_player[2]->getWidth()));
  }
  else if (config::NUM_OF_PLAYERS == 4)
  {
    m_player[0]->setX(centerHorizontal(0, ww - (m_player[0]->getWidth() * 9), m_player[0]->getWidth()));
    m_player[1]->setX(centerHorizontal(0, ww - (m_player[1]->getWidth() * 3), m_player[1]->getWidth()));
    m_player[2]->setX(centerHorizontal((m_player[2]->getWidth() * 3), ww, m_player[2]->getWidth()));
    m_player[3]->setX(centerHorizontal((m_player[3]->getWidth() * 9), ww, m_player[3]->getWidth()));
  }

  countDown = 3;
  text_countDown = std::make_shared<lwe::Text>(getEngine()->getRenderer(), LawyerRace::standardFont.get(), std::to_string(3), 72, 0.f, 0.f, 255, 255, 255);
  text_countDown->setX(centerHorizontal(0, ww, text_countDown->getWidth()));
  text_countDown->setY(centerVertical(0, wh / 2, text_countDown->getHeight()));
  textList.push_back(text_countDown);

  pausedText = std::make_shared<lwe::Text>(getEngine()->getRenderer(), LawyerRace::standardFont.get(), "Game Paused", 72, 0.f, 0.f, 255, 255, 255);
  pausedText->setX(centerHorizontal(0, ww, pausedText->getWidth()));
  pausedText->setY(centerHorizontal(0, wh, pausedText->getHeight()));

  currentInGameState = CountDown;
  countDown_compareTime = SDL_GetTicks();
  return true;
}

void GameState::cleanup()
{
  textList.clear();

  Player::setPlayerCount(0);
  Player::setAlivePlayerCount(0);
  entityManager->clear();
}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
bool GameState::handleEvent(const SDL_Event &ev)
{
  if (m_paused)
  {
    if (pauseCondition(ev))
    {
      onResume();
      return true;
    }

    if (pausedExitToMainMenuCondition(ev))
    {
      onResume();
      getEngine()->setState(((LawyerRace*)getGame())->getMenuState());
      return true;
    }

    return false;
  }

  if(currentInGameState == Play)
  {
    if (pauseCondition(ev))
    {
      onPause();
      return true;
    }

    //Handle movement input
    //TODO: Also set speed to max available speed
    for (auto& e : entityManager->getAll<Player>())
    {
      Player* p = reinterpret_cast<Player*>(e);
      if (p->handleEvent(ev))
      {
        return true;
      }
    }
  }
  else if (currentInGameState == GameOver)
  {
    if (gameOverExitToMainMenuCondition(ev))
    {
      int c = 1;
      for (auto& e : entityManager->getAll<Player>())
      {
        Player* p = reinterpret_cast<Player*>(e);
        LOG_DEBUG("Player %i: %i", c, p->getScore());
        c++;
      }
      getEngine()->setState(((LawyerRace*)getGame())->getMenuState());
      return true;
    }
  }

  return false;
}

void GameState::copyDataForInterpolation()
{
  for (auto& e : entityManager->getAllEntities())
  {
    e->copyDataForInterpolation();
  }
}

void GameState::update(float timeStep)
{
  if (m_paused)
  {
    return;
  }

  entityManager->refresh();

  if (currentInGameState == Play)
  {
    for (auto& e : entityManager->getAllEntities())
    {
      e->update(timeStep);
    }
    checkForCollision();

    createDollar();
    createEnemy();
    createRock();

    if(isGameOver() && currentInGameState != GameOver)
    {
      //ALL PLAYERS DIED!
      currentInGameState = GameOver;
      std::shared_ptr<lwe::Text> t = std::make_shared<lwe::Text>(getEngine()->getRenderer(), LawyerRace::standardFont.get(), "Press enter to exit to menu", 48, 0.f, 0.f, 255, 255, 255);
      textList.push_back(t);
      t->setX(centerHorizontal(0, (float)config::W_WIDTH, t->getWidth()));
      t->setY(bottomAlign((float)config::W_HEIGHT, 20, t->getHeight()));
    }
  }
  else if (currentInGameState == CountDown)
  {
    if(countDown_compareTime < SDL_GetTicks())
    {
      text_countDown->updateText(countDown);
      text_countDown->setX(centerHorizontal(0, (float)config::W_WIDTH, text_countDown->getWidth()));
      text_countDown->setY(centerVertical(0, (float)config::W_HEIGHT / 2, text_countDown->getHeight()));
      countDown_compareTime += 1000;
      countDown--;
      if (countDown < 0)
      {
        textList.remove(text_countDown);
        currentInGameState = Play;
      }
    }
  }
}

void GameState::render(SDL_Renderer* const renderer, float timeAlpha)
{
  for (auto& e : entityManager->getAllEntities())
  {
    e->render(renderer, timeAlpha);
  }

  for (std::shared_ptr<lwe::Text> text : textList)
  {
    text->render();
  }

  if (m_paused)
  {
    pausedText->render();
  }

  if(currentInGameState == GameOver)
  {
    //Render gameover screen here
  }
}
/* END GAMELOOP FUNCTIONS */

void GameState::onPause()
{
  m_paused = true;
}

void GameState::onResume()
{
  m_paused = false;
}

/* SUPPORTIVE FUNCTIONS */

void GameState::checkForCollision()
{
  for (auto& e : entityManager->getAll<Player>())
  {
    Player* p = reinterpret_cast<Player*>(e);
    if (p->isDead())
    {
      continue;
    }

    //Check collision with dollar
    for (auto& e : entityManager->getAll<Dollar>())
    {
      Dollar* d = reinterpret_cast<Dollar*>(e);
      // TODO: check if dollar is scheduled for removal!

      if (AbstractEntity::collides(p, d))
      {
        p->incScore(1);

        // this doesn't actually remove the dollar until next loop, so two players CAN fetch
        // the same dollar at the same update and both players will have their scores incremented
        entityManager->remove(d);
      }
    }

    //Check collision with enemy
    for (auto& e : entityManager->getAll<Enemy>())
    {
      Enemy* en = reinterpret_cast<Enemy*>(e);
      if(AbstractEntity::collides(p, en))
      {
        //Player collides with enemy
        p->kill();
        goto continueOuterLoop;
      }
    }

    //Check collision with rocks
    for (auto& e : entityManager->getAll<Rock>())
    {
      Rock* r = reinterpret_cast<Rock*>(e);
      if (AbstractEntity::collides(p, r))
      {
        //Player collides with rock
        entityManager->remove(r);
        p->kill();
        goto continueOuterLoop;
      }
    }

    continueOuterLoop:;
  }
}

void GameState::createDollar()
{
  auto& dollarList = entityManager->getAll<Dollar>();
  while (dollarList.size() < unsigned(Player::getAlivePlayerCount()))
  {
    Dollar* newDollar = entityManager->create<Dollar>(atlas->findRegion(config::D_SRC), 0.f, 0.f, config::D_WIDTH, config::D_HEIGHT);
    int newDollar_xPos = 0;
    int newDollar_yPos = 0;
    bool valid = false;
    while (!valid)
    { //Loop until valid pos is found
      valid = true;
      newDollar_xPos = rand() % (config::W_WIDTH - (int)newDollar->getWidth())   ;
      newDollar_yPos = rand() % (config::W_HEIGHT - (int)newDollar->getHeight()) ;
      newDollar->setX(static_cast<float>(newDollar_xPos));
      newDollar->setY(static_cast<float>(newDollar_yPos));

      for (auto& e : entityManager->getAll<Player>())
      {
        Player* p = reinterpret_cast<Player*>(e);
        if (AbstractEntity::collides(p, newDollar))
        {
          valid = false;
          break;
        }
      }
    }

    newDollar->setX(static_cast<float>(newDollar_xPos));
    newDollar->setY(static_cast<float>(newDollar_yPos));
    newDollar->copyDataForInterpolation();
  }
}

void GameState::createEnemy()
{
  auto& enemyList = entityManager->getAll<Enemy>();
  if(enemyList.size() >= static_cast<unsigned int>(config::MAX_ENEMIES)) return;

  unsigned int highestCurrentScore = getHighestCurrentScore();

  while( enemyList.size() < ((highestCurrentScore / 5) +1) )
  {
    float e_x;
    float e_y;
    //Create enemy out of screen. Randomize up/down, left/right
    if ((rand() % 2) == 1)
    {
      e_x = -config::E_WIDTH;
      e_y = -config::E_HEIGHT;
    }
    else
    {
      e_x = config::W_WIDTH+1.f;
      e_y = config::W_HEIGHT+1.f;
    }

    //Randomize x and y-position.
    if ((rand() % 2) == 1)
    {
      e_x = (float)(rand() % (int)(config::W_WIDTH - config::E_WIDTH));
    }
    else
    {
      e_y = (float)(rand() % (int)(config::W_HEIGHT - config::E_HEIGHT));
    }

    bool movingX = true, movingY = true;

    auto enemyListSize = entityManager->getAll<Enemy>().size();
    if (enemyListSize > 0)
    {
      if (enemyListSize % 2 == 1)
        movingX = false;
      else
        movingY = false;
    }

    //Finally, create new enemy
    entityManager->create<Enemy>(atlas->findRegions(config::E_SRC), (float)e_x, (float)e_y, config::E_WIDTH, config::E_HEIGHT, movingX, movingY);
  }
}

void GameState::createRock()
{
  // this function must be called right after entityManager->refresh() is called
  int highestCurrentScore = getHighestCurrentScore() - ((config::ENEMIES_BEFORE_ROCK -1) * 5);
  if(highestCurrentScore < 0)
  {
    highestCurrentScore = 0;
  }

  std::size_t max_amount_of_rocks = std::size_t(highestCurrentScore / 5);

  if (max_amount_of_rocks > std::size_t(config::MAX_ROCKS))
  {
    max_amount_of_rocks = std::size_t(config::MAX_ROCKS);
  }

  auto& rockList = entityManager->getAll<Rock>();

  while ( rockList.size() < max_amount_of_rocks )
  {
    float y = -config::MAX_R_HEIGHT;

    int rockType = (rand() % 10 +1);
    if (rockType >= 7 && rockType <= 9)
    {
      float x = (float)(rand() % (int)(config::W_WIDTH - config::R_WIDTH[1]));
      entityManager->create<Rock>(atlas->findRegion(config::R_SRC[1]), x, y, 2);
    }
    else if(rockType == 10)
    {
      float x = (float)(rand() % (int)(config::W_WIDTH - config::R_WIDTH[2]));
      entityManager->create<Rock>(atlas->findRegion(config::R_SRC[2]), x, y, 3);
    }
    else
    {
      float x = (float)(rand() % (int)(config::W_WIDTH - config::R_WIDTH[0]));
      entityManager->create<Rock>(atlas->findRegion(config::R_SRC[0]), x, y, 1);
    }
  }
}

bool GameState::isGameOver()
{
  for (auto& e : entityManager->getAll<Player>())
  {
    Player* p = reinterpret_cast<Player*>(e);
    if (!(p->isDead()))
    {
      return false;
    }
  }

  return true;
}

int GameState::getHighestCurrentScore()
{
  int highestCurrentScore = 0;
  for (auto& e : entityManager->getAll<Player>())
  {
    Player* p = reinterpret_cast<Player*>(e);
    if (p->getScore() > highestCurrentScore)
    {
      highestCurrentScore = p->getScore();
    }
  }

  return highestCurrentScore;
}

std::list<Player*> GameState::getWinners()
{
  std::list<Player*> returnList;
  int highestScore = getHighestCurrentScore();
  for (auto& e : entityManager->getAll<Player>())
  {
    Player* p = reinterpret_cast<Player*>(e);
    if (p->getScore() == highestScore)
    {
      returnList.push_back(p);
    }
  }

  return returnList;
}
/* END SUPPORTIVE FUNCTIONS */
