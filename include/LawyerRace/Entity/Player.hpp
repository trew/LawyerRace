#ifndef LWR_PLAYER_HPP
#define LWR_PLAYER_HPP

#include "LawyerRace/Core/Gameconfig.hpp"
#include "LawyerRace/Entity/Entity.hpp"
#include "LawyerRace/Entity/Enemy.hpp"
#include "LawyerRace/Utils/FPS.hpp"
#include "LawyerRace/Graphics/Text.hpp"
#include "LawyerRace/Core/KeySet.hpp"
#include "LawyerRace/Graphics/TextureRegion.hpp"

#include <string>

class Player: public Entity {
public:
    Player();
	Player(std::vector<TextureRegion*> regions, KeySet keySet);
	Player(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h, KeySet keySet);

    virtual ~Player();


    /**
     *  Loads a keyset to the player
     *  @param set The KeySet instance from which we load keydata.
     */
    void loadKeySet(const KeySet &set);

	void update(float timeStep) override;
	virtual void render(SDL_Renderer* renderer, float timeAlpha) override;
    void handleEvent(SDL_Event& ev);


    /**
     *  Sets the direction of the player to be facing UP, DOWN, LEFT or RIGHT.
     *  @param Enum Direction.
     */
    void setDirection(Direction);


    /** Updates the score text and positions it on the screen. */
    void updateScore();
    void incScore(int _score);
    void kill();
	bool isDead() const;
	int getScore() const;

private:
	Direction m_direction{ DOWN };
	int m_score{ 0 };
	Text* score_text{ NULL };
	bool dead{ false };
	int playerNum{ 0 };

    KeySet m_keySet;

public:
    static int alivePlayers;
    static int currentPlayerNum;
};

#endif
