#include <LawyerRace/Core/MenuState.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Utils/PositionHelper.hpp>
#include <iostream>

MenuState::MenuState()
{
  back.addTrigger(std::make_shared<lwe::KeyboardTrigger>(SDLK_ESCAPE));
  back.addTrigger(std::make_shared<lwe::GameControllerButtonTrigger>(SDL_CONTROLLER_BUTTON_B));
}

MenuState::~MenuState()
{
}

/* RUN ONCE FUNCTIONS */

bool MenuState::init()
{
  getEngine()->setBackgroundColor({0, 0, 0, 255});

  internalState = NORMAL;
  float menuPosition[] = { 272.f, 362.f, 452.f, 542.f };

  Config& config = Config::getInstance();
  lwe::AssetManager* assetManager = getEngine()->getAssetManager();
  lwe::TextureAtlas* atlas = assetManager->get<lwe::TextureAtlas>(config.getFile("img/spritesheet_0"));
  std::vector<lwe::TextureRegion*> regions = atlas->findRegions("button-1-players");

  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[0]));
  playersButtons.back()->setAction([this](lwe::Button* btn) -> void
  {
    Config::getInstance().setPlayerCount(1);
    getEngine()->setState(getGame<LawyerRace>()->getGameState());
  });
  playersButtons.front()->setSelected(true);

  regions = atlas->findRegions("button-2-players");
  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[1]));
  playersButtons.back()->setAction([this](lwe::Button* btn) -> void
  {
    Config::getInstance().setPlayerCount(2);
    getEngine()->setState(getGame<LawyerRace>()->getGameState());
  });

  regions = atlas->findRegions("button-3-players");
  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[2]));
  playersButtons.back()->setAction([this](lwe::Button* btn) -> void
  {
    Config::getInstance().setPlayerCount(3);
    getEngine()->setState(getGame<LawyerRace>()->getGameState());
  });

  regions = atlas->findRegions("button-4-players");
  playersButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[3]));
  playersButtons.back()->setAction([this](lwe::Button* btn) -> void
  {
    Config::getInstance().setPlayerCount(4);
    getEngine()->setState(getGame<LawyerRace>()->getGameState());
  });

  playersButtons[0]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), playersButtons[0]->getWidth()));
  playersButtons[1]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), playersButtons[1]->getWidth()));
  playersButtons[2]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), playersButtons[2]->getWidth()));
  playersButtons[3]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), playersButtons[3]->getWidth()));

  lwe::Button::createVerticalButtonGroup({playersButtons[0], playersButtons[1], playersButtons[2], playersButtons[3]});

  lwe::TextureRegion* menuBorderRegion = atlas->findRegion("mainmenu-menuframe-453x469");
  lwe::TextureRegion* titleRegion = atlas->findRegion("menu-title");

  menuBorder = std::make_shared<AbstractEntity>(menuBorderRegion);
  menuBorder->setX(config.getGameWidth() / 2.f - menuBorder->getWidth() / 2.f);
  menuBorder->setY(200.f);
  menuBorder->setPreviousX(menuBorder->getX());
  menuBorder->setPreviousY(menuBorder->getY());

  title = std::make_shared<AbstractEntity>(titleRegion);
  title->setX(config.getGameWidth() / 2.f - title->getWidth() / 2.f);
  title->setY(40);
  title->setPreviousX(title->getX());
  title->setPreviousY(title->getY());

  regions = atlas->findRegions("button-play");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[0]));
  menuButtons.back()->setAction([this](lwe::Button*) -> void
  {
    internalState = SELECT_PLAYERS;
  });
  menuButtons.front()->setSelected(true);
  regions = atlas->findRegions("button-highscores");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[1]));
  menuButtons.back()->setAction([this](lwe::Button*) -> void
  {
    // TODO enter highscores state
  });

  regions = atlas->findRegions("button-settings");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[2]));
  menuButtons.back()->setAction([this](lwe::Button*) -> void
  {
    getEngine()->setState(getGame<LawyerRace>()->getSettingsState(), false);
  });

  regions = atlas->findRegions("button-exit");
  menuButtons.push_back(std::make_shared<lwe::Button>(regions[0], regions[1], regions[1], 0.f, menuPosition[3]));
  menuButtons.back()->setAction([this](lwe::Button*) -> void
  {
    getEngine()->exit();
  });

  menuButtons[0]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), menuButtons[0]->getWidth()));
  menuButtons[1]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), menuButtons[1]->getWidth()));
  menuButtons[2]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), menuButtons[2]->getWidth()));
  menuButtons[3]->setX(positionHelper::centerHorizontal(0.f, (float)config.getGameWidth(), menuButtons[3]->getWidth()));


  lwe::Button::createVerticalButtonGroup({menuButtons[0], menuButtons[1], menuButtons[2], menuButtons[3]});

  rockRegion[0] = atlas->findRegion("stone1-17x14");
  rockRegion[1] = atlas->findRegion("stone2-26x25");
  rockRegion[2] = atlas->findRegion("stone3-58x49");

  return true;
}

void MenuState::cleanup()
{
  playersButtons.clear();
  menuButtons.clear();
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
    bool result = false;
    if (back(ev, &result)) // if event is consumed
    {
      if (result) // if condition is met
      {
        internalState = NORMAL;
      }
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
  Config& config = Config::getInstance();
  for (auto it = rocks.begin(); it != rocks.end(); )
  {
    (*it)->update(timeStep);

    if ((*it)->getY() + (*it)->getHeight() > config.getGameHeight())
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
    float y = -config.getMaxRockHeight();
    float x = (float)(rand() % (int)(config.getGameWidth()));
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
