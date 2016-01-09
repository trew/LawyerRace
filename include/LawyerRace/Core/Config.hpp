#ifndef LWR_CONFIG_HPP
#define LWR_CONFIG_HPP

#include <string>
#include <LawyerRace/Core/PlayerControls.hpp>

///Direction for enemies and player (player uses only DOWN - LEFT)
enum Direction {
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3,
  UP_RIGHT = 4,
  DOWN_RIGHT = 5,
  DOWN_LEFT = 6,
  UP_LEFT = 7,
  STILL = 8
};

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)

class Config
{
public:
  static Config& getInstance()
  {
    static Config instance;
    return instance;
  }

  const std::string& getPath() const;
  void setPath(const std::string& path);

  void setConfigFile(const std::string& file);
  bool loadConfigFile();

  std::string getFile(const std::string& fileName);

  int getWindowWidth() const;
  int getWindowHeight() const;

  int getGameWidth() const;
  int getGameHeight() const;

  const std::string& getWindowText() const;
  int getMaximumPlayerCount() const;
  int getPlayerCount() const;
  void setPlayerCount(int count);

  float getPlayerWidth() const;
  float getPlayerHeight() const;

  float getEnemyWidth() const;
  float getEnemyHeight() const;

  float getDollarWidth() const;
  float getDollarHeight() const;

  float getMaxRockWidth() const;
  float getMaxRockHeight() const;
  float getRockWidth(int type) const;
  float getRockHeight(int type) const;

  bool isPlayerStopEnabled() const;
  void setPlayerStopEnabled(bool enabled);
  bool isOldDiagonalSpeedEnabled() const;
  void setOldDiagonalSpeedEnabled(bool enabled);

  int getMaxEnemyCount() const;
  int getEnemyCountBeforeRocks() const;
  int getMaxRockCount() const;

  float getGameSpeed() const;
  float getPlayerVelocity() const;
  float getEnemyVelocity() const;
  float getRockVelocity(int type) const;

  const std::string& getControlsFile() const;
  void setControlsFile(const std::string& file);

  bool isLinearInterpolationEnabled() const;
  int getMaxFrameSkip() const;
  int getMaxFPS() const;

  const std::string& getDollarRegion() const;
  const std::string& getPlayerRegion(int player) const;
  const std::string& getEnemyRegion() const;
  const std::string& getRockRegion(int type) const;

  const SDL_Color& getBackgroundColor() const;
  void setBackgroundColor(const SDL_Color& color);

private:
  bool initialized { false };

  Config();
  ~Config();

  std::string validateConfigFile(const std::string& file);
  std::string validatePath(const std::string& path);

private:
  std::string path;
  std::string configFile { "cfg/med.lua" };
  std::string controlsFile { "cfg/controls.lua" };

  std::string windowText { "Lawyer Race" };

  int maxPlayerCount { 4 };
  int playerCount { 1 };

  int windowWidth { 1024 };
  int windowHeight { 768 };

  int gameWidth { 1024 };
  int gameHeight { 768 };

  float playerWidth { 30.f };
  float playerHeight { 30.f };

  float enemyWidth { 30.f };
  float enemyHeight { 30.f };

  float dollarWidth { 30.f };
  float dollarHeight { 15.f };

  float maxRockWidth { 58.f };
  float maxRockHeight { 49.f };
  float rockWidth[3];
  float rockHeight[3];

  bool playerStopEnabled { true };
  bool oldDiagonalSpeed { false };

  int maxEnemyCount { 5 };
  int enemyCountBeforeRocks { 3 };
  int maxRockCount { 10 };

  float gameSpeed { 1.f };

  float playerVelocity { 250.f };
  float enemyVelocity { 100.f };
  float rockVelocity[3];

  std::string dollarRegion { "dollar" };
  std::string playerRegion[4];
  std::string enemyRegion { "enemy" };
  std::string rockRegion[3];

  bool enableLinearInterpolation { true };
  int maxFrameSkip { 10 };
  int maxFps { 200 };

  SDL_Color backgroundColor;
};

#endif
