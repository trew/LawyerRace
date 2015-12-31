#ifndef LWR_PLAYER_HPP
#define LWR_PLAYER_HPP

#include <LawyerEngine/LawyerEngine.hpp>

#include <LawyerRace/Core/Config.hpp>
#include <LawyerRace/Entity/Enemy.hpp>
#include <LawyerRace/Core/PlayerControls.hpp>
#include <LawyerRace/Event/EventCondition.hpp>

#include <string>

class Player: public AbstractEntity
{
public:
  Player();
  Player(const std::vector<lwe::TextureRegion*>& regions, SDL_Renderer* renderer, const PlayerControls& controls);
  Player(const std::vector<lwe::TextureRegion*>& regions, SDL_Renderer* renderer, float x, float y, float w, float h, const PlayerControls& controls);

  virtual ~Player();

  void update(float timeStep) override;
  virtual void render(SDL_Renderer* renderer, float timeAlpha) override;
  bool handleEvent(const SDL_Event& ev);

  /**
   * Sets the direction of the player to be facing UP, DOWN, LEFT or RIGHT.
   * @param Enum Direction.
   */
  void setDirection(Direction);

  /** Updates the score text and positions it on the screen. */
  void updateScore();
  void incScore(int _score);
  void kill();
  bool isDead() const;
  int getScore() const;

  static int getAlivePlayerCount() { return alivePlayers; }
  static int getPlayerCount() { return currentPlayerNum; }
  static void setPlayerCount(int c) { currentPlayerNum = c; }

private:
  PlayerControls controls;

  Direction m_direction { DOWN };
  int m_score { 0 };
  std::shared_ptr<lwe::Text> scoreText;
  bool dead { false };
  int playerNum { 0 };

  SDL_Renderer* renderer;

  static int alivePlayers;
  static int currentPlayerNum;
};

#endif
