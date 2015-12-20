#ifndef LWR_PLAYER_HPP
#define LWR_PLAYER_HPP

#include <LawyerEngine/LawyerEngine.hpp>

#include <LawyerRace/Core/Config.hpp>
#include <LawyerRace/Entity/Enemy.hpp>
#include <LawyerRace/Core/KeySet.hpp>
#include <LawyerRace/Graphics/LawyerText.hpp>

#include <string>

class Player: public AbstractEntity
{
public:
  Player();
  Player(std::vector<lwe::TextureRegion*> regions, KeySet keySet);
  Player(std::vector<lwe::TextureRegion*> regions, float x, float y, float w, float h, KeySet keySet);

  virtual ~Player();


  /**
   * Loads a keyset to the player
   * @param set The KeySet instance from which we load keydata.
   */
  void loadKeySet(const KeySet &set);

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
  Direction m_direction { DOWN };
  int m_score { 0 };
  LawyerText* score_text { NULL };
  bool dead { false };
  int playerNum { 0 };

  KeySet m_keySet;

  static int alivePlayers;
  static int currentPlayerNum;
};

#endif
