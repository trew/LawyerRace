#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <LawyerRace/Core/MenuState.hpp>

std::unique_ptr<lwe::Font> LawyerRace::standardFont;

LawyerRace::LawyerRace()
{
}

LawyerRace::~LawyerRace()
{
  // must be deleted before the engine is destroyed
  standardFont.reset();
}

GameState* LawyerRace::getGameState() const
{
  return gameState.get();
}

MenuState* LawyerRace::getMenuState() const
{
  return menuState.get();
}

SettingsState* LawyerRace::getSettingsState() const
{
  return settingsState.get();
}

void LawyerRace::init()
{
  menuState = std::make_unique<MenuState>();
  gameState = std::make_unique<GameState>();
  settingsState = std::make_unique<SettingsState>();

  Config& config = Config::getInstance();

  LOG_DEBUG("Loading fonts...");
  LawyerRace::standardFont = std::make_unique<lwe::Font>();
  LawyerRace::standardFont->loadFromFile(config.getFile("font/VeraMono.ttf"));
  LawyerRace::standardFont->getTTF_Font(12);
  LawyerRace::standardFont->getTTF_Font(48);
  LawyerRace::standardFont->getTTF_Font(72);

  LOG_DEBUG("Loading texture atlas...");
  if (!getEngine()->getAssetManager()->load<lwe::TextureAtlas>(config.getFile("img/spritesheet_0")))
  {
    LOG_ERROR("Error loading texture atlas: %s", (config.getFile("img/spritesheet_0")).c_str());
  }

  getEngine()->setState(menuState.get());
}
