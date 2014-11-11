#ifndef LWR_ENEMY_HPP
#define LWR_ENEMY_HPP

#include "LawyerRace/Entity/Entity.hpp"
#include "LawyerRace/Entity/Player.hpp"

class Player;
class Enemy: public Entity {

public:
	Enemy(std::vector<TextureRegion*> regions, const float x, const float y, const float w, const float h, bool movingX, bool movingY);
    virtual ~Enemy();

    void update(float timeStep) override;
	void render(SDL_Renderer* renderer, float alphaTime);

    void updateMovement(float timeStep);


    /**
     * Sets target depending on distance. Measures from Enemys center to Players center. 
     * Doesn't target non-moving players.
     */
    void updateTarget();


    /** Update the direction to face current target */
    void updateDirection();

    void startMovement();
    void stopMovement();
    void toggleMovement();

private:
	Direction m_direction{ DOWN };
	Player* currentTarget{ NULL };
	bool m_movingX{ false };
	bool m_movingY{ false };
	int m_diagonalSensitivity{ 0 };
};

#endif
