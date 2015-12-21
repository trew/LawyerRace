#include <LawyerRace/Core/MenuState.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <iostream>

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

/* RUN ONCE FUNCTIONS */

bool MenuState::init()
{
  float menuPosition[] = { 300.f, 390.f, 480.f, 570.f };

  lwe::AssetManager* assetManager = getEngine()->getAssetManager();
  lwe::TextureAtlas* atlas = assetManager->get<lwe::TextureAtlas>(config::path + "img/spritesheet_0");
  std::vector<lwe::TextureRegion*> regions = atlas->findRegions("button-1-players");

  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[0], [this](lwe::Button* btn) -> void
  {
    config::NUM_OF_PLAYERS = 1;
    getEngine()->setState(((LawyerRace*)getGame())->getGameState());
  }));
  playersButtons.front()->setSelected(true);

  regions = atlas->findRegions("button-2-players");
  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[1], [this](lwe::Button* btn) -> void
  {
    config::NUM_OF_PLAYERS = 2;
    getEngine()->setState(((LawyerRace*)getGame())->getGameState());
  }));

  regions = atlas->findRegions("button-3-players");
  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[2], [this](lwe::Button* btn) -> void
  {
    config::NUM_OF_PLAYERS = 3;
    getEngine()->setState(((LawyerRace*)getGame())->getGameState());
  }));

  regions = atlas->findRegions("button-4-players");
  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[3], [this](lwe::Button* btn) -> void
  {
    config::NUM_OF_PLAYERS = 4;
    getEngine()->setState(((LawyerRace*)getGame())->getGameState());
  }));

  playersButtons[0]->setNext(playersButtons[1].get());
  playersButtons[0]->setPrevious(playersButtons[3].get());

  playersButtons[1]->setNext(playersButtons[2].get());
  playersButtons[1]->setPrevious(playersButtons[0].get());

  playersButtons[2]->setNext(playersButtons[3].get());
  playersButtons[2]->setPrevious(playersButtons[1].get());

  playersButtons[3]->setNext(playersButtons[0].get());
  playersButtons[3]->setPrevious(playersButtons[2].get());

  lwe::TextureRegion* menuBorderRegion = atlas->findRegion("mainmenu-menuframe-453x469");
  lwe::TextureRegion* titleRegion = atlas->findRegion("menu-title");

  menuBorder = std::make_shared<AbstractEntity>(menuBorderRegion);
  menuBorder->setX(config::W_WIDTH / 2.f - menuBorder->getWidth() / 2.f);
  menuBorder->setY(200.f);
  menuBorder->setPreviousX(menuBorder->getX());
  menuBorder->setPreviousY(menuBorder->getY());

  title = std::make_shared<AbstractEntity>(titleRegion);
  title->setX(config::W_WIDTH / 2.f - title->getWidth() / 2.f);
  title->setY(40);
  title->setPreviousX(title->getX());
  title->setPreviousY(title->getY());

  regions = atlas->findRegions("button-play");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[0], [this](lwe::Button*) -> void
  {
    internalState = SELECT_PLAYERS;
  }));
  menuButtons.front()->setSelected(true);
  regions = atlas->findRegions("button-highscores");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[1], [this](lwe::Button*) -> void
  {
    // TODO enter highscores state
  }));
  regions = atlas->findRegions("button-settings");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[2], [this](lwe::Button*) -> void
  {
    // TODO enter settings state
  }));
  regions = atlas->findRegions("button-exit");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], config::W_WIDTH / 2.f, menuPosition[3], [this](lwe::Button*) -> void
  {
    getEngine()->exit();
  }));

  menuButtons[0]->setNext(menuButtons[1].get());
  menuButtons[0]->setPrevious(menuButtons[3].get());

  menuButtons[1]->setNext(menuButtons[2].get());
  menuButtons[1]->setPrevious(menuButtons[0].get());

  menuButtons[2]->setNext(menuButtons[3].get());
  menuButtons[2]->setPrevious(menuButtons[1].get());

  menuButtons[3]->setNext(menuButtons[0].get());
  menuButtons[3]->setPrevious(menuButtons[2].get());

  rockRegion[0] = atlas->findRegion("stone1-17x14");
  rockRegion[1] = atlas->findRegion("stone2-26x25");
  rockRegion[2] = atlas->findRegion("stone3-58x49");

  LOG_INFO("Rock size: %i", rocks.size());
  return true;
}

void MenuState::cleanup()
{
}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
bool MenuState::handleEvent(const SDL_Event &ev)
{
  if (internalState == NORMAL)
  {
    for (std::shared_ptr<lwe::Button> btn : menuButtons)
    {
      if (btn->handleEvent(ev))
      {
        return true;
      }
    }
  }
  else if (internalState == SELECT_PLAYERS)
  {
    if (ev.key.type == SDL_KEYUP && ev.key.keysym.sym == SDLK_ESCAPE)
    {
      internalState = NORMAL;
      return true;
    }

    for (std::shared_ptr<lwe::Button> btn : playersButtons)
    {
      if (btn->handleEvent(ev))
      {
        return true;
      }
    }
  }
  return false;
}

void MenuState::copyDataForInterpolation()
{
  for (std::shared_ptr<Rock> rock : rocks)
  {
    rock->copyDataForInterpolation();
  }
}

void MenuState::update(float timeStep)
{
  for (auto& it = rocks.begin(); it != rocks.end(); )
  {
    (*it)->update(timeStep);

    if ((*it)->getY() + (*it)->getHeight() > config::W_HEIGHT)
    {
      it = rocks.erase(it);
    }
    else
    {
      it++;
    }
  }
  
  while (rocks.size() < 5)
  {
    float y = -config::MAX_R_HEIGHT;
    float x = (float)(rand() % (int)(config::W_WIDTH));
    int rockType = (rand() % 10 + 1);

    if (rockType >= 5 && rockType <= 8)
    {
      rocks.push_back(std::make_shared<Rock>(rockRegion[1], x, y, 2));
    }
    else if (rockType > 8)
    {
      rocks.push_back(std::make_shared<Rock>(rockRegion[2], x, y, 3));
    }
    else
    {
      rocks.push_back(std::make_shared<Rock>(rockRegion[0], x, y, 1));
    }
  }
}

void MenuState::render(SDL_Renderer* const renderer, float timeAlpha)
{
  for (std::shared_ptr<Rock> rock : rocks)
  {
    rock->render(renderer, timeAlpha);
  }

  title->render(renderer, timeAlpha);
  menuBorder->render(renderer, timeAlpha);

  if (internalState == NORMAL)
  {
    for (std::shared_ptr<lwe::Button> button : menuButtons)
    {
      button->render(renderer);
    }
  }
  else if (internalState == SELECT_PLAYERS)
  {
    for (std::shared_ptr<lwe::Button> button : playersButtons)
    {
      button->render(renderer);
    }
  }
}
/* END GAMELOOP FUNCTIONS */
