#include <LawyerRace/Core/LawyerRace.hpp>
#include <LawyerRace/Core/GameState.hpp>
#include <LawyerRace/Core/MenuState.hpp>

lua_State* LawyerRace::LuaState { nullptr }; // TODO: change to non-static
std::unique_ptr<lwe::Font> LawyerRace::standardFont;

LawyerRace::LawyerRace()
{
  if (LuaState == nullptr)
  {
    LuaState = luaL_newstate();
    luaL_openlibs(LuaState);
  }
}

LawyerRace::~LawyerRace()
{
  if (LuaState != nullptr)
  {
    lua_close(LuaState);
    LuaState = nullptr;
  }

  standardFont.release();
}

GameState* LawyerRace::getGameState() const
{
  return gameState.get();
}

MenuState* LawyerRace::getMenuState() const
{
  return menuState.get();
}

void LawyerRace::init()
{
  menuState = std::make_shared<MenuState>();
  gameState = std::make_shared<GameState>();

  LOG_DEBUG("Loading fonts...");
  LawyerRace::standardFont = std::make_unique<lwe::Font>();
  LawyerRace::standardFont->loadFromFile(config::path + "font/VeraMono.ttf");
  LawyerRace::standardFont->getTTF_Font(12);
  LawyerRace::standardFont->getTTF_Font(48);
  LawyerRace::standardFont->getTTF_Font(72);

  LOG_DEBUG("Loading texture atlas...");
  if (!getEngine()->getAssetManager()->load<lwe::TextureAtlas>(config::path + "img/spritesheet_0"))
  {
    LOG_ERROR("Error loading texture atlas: %s", (config::path + "img/spritesheet_0").c_str());
  }

  getEngine()->setState(menuState.get());
}
