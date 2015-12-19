#ifndef LWR_GAMESTATE_HPP
#define LWR_GAMESTATE_HPP

#include <list>

#include <SDL.h>

#include "LawyerRace/Core/Gameconfig.hpp"
#include "LawyerRace/Entity/Player.hpp"
#include "LawyerRace/Entity/Enemy.hpp"
#include "LawyerRace/Entity/Dollar.hpp"
#include "LawyerRace/Entity/Rock.hpp"

#include "LawyerRace/Core/AbstractState.hpp"

#include <LawyerEngine/LawyerEngine.hpp>

enum InGameState {
    Play = 0,
    CountDown,
    Paused,
    GameOver
};

class GameState: public lwe::State {
public:
  GameState();
  virtual ~GameState() {}

public:

    /* STATE FUNCTIONS */

  bool init() override;
  void cleanup() override;

	void copyDataForInterpolation() override;

	void update(const float timeStep) override;
  bool handleEvent(const SDL_Event &ev) override;
  void render(SDL_Renderer* const renderer, const float timeAlpha) override;

	void pause() override;
	void resume() override;

  /* !STATE FUNCTIONS */

  /* SUPPORTIVE FUNCTIONS */
	void checkForCollision();
	
  /** Creates a dollar and places it randomly on the screen. */
  void createDollar();


  /**
   * Creates new enemies
   * Amount of enemies in game is HighestCurrentScore / 5.
   * Example: 1 Player with 10 points       -> ( 10 / 5 = -- 2 Enemies --
   * Example: 2 Players with 9 and 15 points ->( 15 / 5 = -- 3 Enemies --
   */
  void createEnemy();


  /**
   * Creates and removes rocks
   * Amount of rocks in game is                 (HighestCurrentScore - (3 * 5)) / 5 +1
   * Example: 1 Player with 10 points        -> ( 10 - (3 * 5) / 5 +1 = 0 rocks
   * Example: 2 Players with 9 and 15 points -> ( 15 - (3 * 5) / 5 +1 = 1 rocks
   * Example: 1 Player with 25 points        -> ( 25 - (3 * 5) / 5 +1 = 3 rocks
   */
  void createRock();


  /**
   *  Checks if all players are dead.
   *  @return True if all players are dead, False otherwise.
   */
  bool isGameOver();


  /**
   *  Checks the score of all players and retrieves the highest of them.
   *  @return The highest score out of all the players.
   */
  int getHighestCurrentScore();


  /**
   *  Gets a list of all players which has the highest score.
   *  @return a list of player pointers which all has the highest score.
   */
  std::list<Player*> getWinners();


private:
  std::unique_ptr<lwe::EntityManager> entityManager;
  Player* m_player[4];

  int countDown;
	bool m_paused{ false };
  unsigned int countDown_compareTime;
  InGameState currentInGameState;
  LawyerText* text_countDown;

	lwe::TextureAtlas* atlas{ NULL };
};

#endif
