#include "GameState.h"
#include <sstream>

GameState::GameState() {
///Constructor
	GameRunning = true;
	m_player[0] = NULL;
	m_player[1] = NULL;
	m_player[2] = NULL;
	m_player[3] = NULL;
	temp_delay = 0;
}

GameState::~GameState() {
///Destructor
	
}

int GameState::Execute() {
///Runs when game starts. 
	//Initialize all
	if(!Init()) return -1;		

	SDL_Event ev;

	//Game loop
	while(GameRunning) {
		while(SDL_PollEvent(&ev)) {
			OnEvent(&ev);
		}
		Update();
		Render();

		if (FPS::FPSControl.GetFPS() > 200) SDL_Delay(3); //Tiny delay if computer is giving high fps. No need for super high fps.
		if (temp_delay > 0) {
			SDL_Delay(temp_delay);
			temp_delay = 0;
		}
	}

	//Cleanup memory and shut down
	Cleanup();
	return 0;
}


/* RUN ONCE FUNCTIONS */

void GameState::Cleanup() {
///Cleanup memory and prepare new game
	GameRunning = true;

	std::map<int, TTF_Font*>::iterator it_font = Text::standard_font.begin();
	while(it_font != Text::standard_font.end()) {
		TTF_CloseFont((*it_font).second);
		it_font++;
	}
	
	//Delete all sprites
	std::list<Sprite*>::iterator it_Sprite = Sprite::s_spriteList.begin();
	while(it_Sprite != Sprite::s_spriteList.end()) {
		if ((*it_Sprite) != NULL) {
			delete (*it_Sprite); (*it_Sprite) = NULL;
		}
		it_Sprite++;
	}

	Player::currentPlayerNum = 0;
	Player::s_playerList.clear();
	Enemy::s_enemyList.clear();
	Rock::s_rockList.clear();
	Entity::s_entityList.clear();
	Sprite::s_spriteList.clear();
	Dollar::s_dollarList.clear();
	Text::s_textList.clear();

}
/* END RUN ONCE FUNCTIONS */



/* GAMELOOP FUNCTIONS*/
void GameState::OnEvent(SDL_Event* ev) {
///Handle input events
	if (ev->type == SDL_QUIT ) {
		GameRunning = false;
		Game::StateControl.setState(NULL);
	}

	if(currentInGameState == Play) {
		if (ev->type == SDL_KEYDOWN) {
			//Handle movement input
			//TODO: Also set speed to max available speed
			std::list<Player*>::iterator it_player = Player::s_playerList.begin();
			while(it_player != Player::s_playerList.end()) {
				(*it_player)->handleEvent(*ev);
				it_player++;
			}
		}
	} else if (currentInGameState == GameOver) {
		if (ev->type == SDL_KEYDOWN) {
			GameRunning = false;
			Game::StateControl.setState(NULL);
		}
	}
}

void GameState::Update() {
	///Update game objects

	if(currentInGameState == Play) {
		std::list<Player*>::iterator it_player = Player::s_playerList.begin();
		while(it_player != Player::s_playerList.end()) {
			if(!(*it_player)->isDead())
				(*it_player)->update();
			it_player++;
		}

		std::list<Rock*>::iterator it_rock = Rock::s_rockList.begin();
		while(it_rock != Rock::s_rockList.end()) {
			(*it_rock)->update();
			it_rock++;
		}

		std::list<Enemy*>::iterator it_enemy = Enemy::s_enemyList.begin();
		while(it_enemy != Enemy::s_enemyList.end()) {
			(*it_enemy)->update();
			it_enemy++;
		}
	
		checkForCollision();

		createDollar();
		createEnemy();
		createRock();

		if(isGameOver() && currentInGameState != GameOver) {
			//ALL PLAYERS DIED!
			currentInGameState = GameOver;
			Text::s_textList.push_back(new Text("Press key to exit to menu", 48, 0, 0, 255, 255, 255));
			Text::s_textList.back()->centerHorizontal(0,config::W_WIDTH);
			Text::s_textList.back()->bottomAlign(config::W_HEIGHT, 20);

			temp_delay = 1000;
		}
	} 
	else if (currentInGameState == CountDown) {
		if(countDown_compareTime < SDL_GetTicks()) {
			text_countDown->updateText(countDown);
			text_countDown->centerHorizontal(0,config::W_WIDTH);
			text_countDown->centerVertical(0,config::W_HEIGHT / 2);
			countDown_compareTime += 1000;
			countDown--;
			if (countDown < 0) {
				Text::s_textList.remove(text_countDown);
				currentInGameState = Play;
			}
		}
	}

	FPS::FPSControl.Update();
#ifdef WIN32
	std::stringstream ss;
	ss << config::WINDOW_TEXT << "    " << FPS::FPSControl.GetFPS();
	SDL_WM_SetCaption(ss.str().c_str(), ss.str().c_str());
#endif
}


void GameState::Render() {
/// Draw all Sprites to screen
	SDL_FillRect(mainScreen, NULL, 0);	//Reset screen

	std::list<Dollar*>::const_iterator it_dollar = Dollar::s_dollarList.begin();
	while(it_dollar != Dollar::s_dollarList.end()) {
		(*it_dollar)->draw(mainScreen);
		it_dollar++;
	}
	
	std::list<Player*>::const_iterator it_player = Player::s_playerList.begin();
	while(it_player != Player::s_playerList.end()) {
		(*it_player)->draw(mainScreen);
		it_player++;
	}

	std::list<Enemy*>::const_iterator it_enemy = Enemy::s_enemyList.begin();
	while(it_enemy != Enemy::s_enemyList.end()) {
		(*it_enemy)->draw(mainScreen);
		it_enemy++;
	}

	std::list<Rock*>::const_iterator it_rock = Rock::s_rockList.begin();
	while(it_rock != Rock::s_rockList.end()) {
		(*it_rock)->draw(mainScreen);
		it_rock++;
	}

	std::list<Text*>::const_iterator it_text = Text::s_textList.begin();
	while(it_text != Text::s_textList.end()) {
		(*it_text)->draw(mainScreen);
		it_text++;
	}

	if(currentInGameState == GameOver) {
		//Render gameover screen here
	}

	SDL_Flip(mainScreen);
}
/* END GAMELOOP FUNCTIONS */



/* SUPPORTIVE FUNCTIONS */

void GameState::checkForCollision() {
///Checks if player collides with enemy, (powerup or dollar not yet implemented) 
	std::list<Player*>::iterator it_player = Player::s_playerList.begin();
	std::list<Enemy*>::iterator it_enemy;
//	std::list<Powerup*>::iterator it_powerup;
	std::list<Dollar*>::iterator it_dollar;
	std::list<Rock*>::iterator it_rock;

	while(it_player != Player::s_playerList.end()) {
		if ((*it_player)->isDead()) {
			it_player++;
			continue;
		}
		//TODO::::!!!
		/* 
		it_powerup = Powerup::s_powerupList.begin();
		while(it_powerup != Powerup::s_powerupList.end()) {
			if(Entity::collides((*it_powerup), (*it_player))) {
				//Player collides with powerup
			}
			it_powerup++;
		}
		*/
		 
		//Check collision with dollar
		it_dollar = Dollar::s_dollarList.begin();
		Dollar* tmp_dollar = NULL;
		while(it_dollar != Dollar::s_dollarList.end()) {
			if(Entity::collides((*it_player), (*it_dollar))) {
				//Player collides with dollar
				tmp_dollar = (*it_dollar);
			}
			it_dollar++;
		}
		if (tmp_dollar != NULL) {
			(*it_player)->incScore(1);
			Dollar::s_dollarList.remove(tmp_dollar);
			Sprite::s_spriteList.remove(tmp_dollar);
			delete tmp_dollar; tmp_dollar = NULL;
		}
			
		//Check collision with enemy		
		it_enemy = Enemy::s_enemyList.begin();
		Player* tmp_player = NULL;
		while(it_enemy != Enemy::s_enemyList.end()) {
			if(Entity::collides((*it_player), (*it_enemy))) {
				//Player collides with enemy
				tmp_player = (*it_player);
			}
			it_enemy++;
		}
		if(tmp_player != NULL) {
			tmp_player->kill();
		}

		//Check collision with rocks
		it_rock = Rock::s_rockList.begin();
		tmp_player = NULL;
		while(it_rock != Rock::s_rockList.end()) {
			if(Entity::collides((*it_player), (*it_rock))) {
				//Player collides with rock
				tmp_player = (*it_player);
				(*it_rock)->expire();
			}
			it_rock++;
		}
		if(tmp_player != NULL) {
			tmp_player->kill();

		}

		it_player++;
	}

}

void GameState::createDollar() {
	std::list<Player*>::const_iterator it_player = Player::s_playerList.begin();
	while (Dollar::s_dollarList.size() < unsigned(Player::alivePlayers)) {
		Dollar* newDollar = new Dollar(config::D_SRC, 0, 0);
		int newDollar_xPos = 0;
		int newDollar_yPos = 0;
		bool valid = false;
		while(!valid) {	//Loop until valid pos is found
			valid = true;
			newDollar_xPos = rand() % (config::W_WIDTH - newDollar->getWidth())   ;
			newDollar_yPos = rand() % (config::W_HEIGHT - newDollar->getHeight()) ;

			while(it_player != Player::s_playerList.end()) {
				if(Entity::collides((*it_player), newDollar)) {
					valid = false;
					break;
				}
				it_player++;
			}
		}
		newDollar->setXPos(static_cast<float>(newDollar_xPos));
		newDollar->setYPos(static_cast<float>(newDollar_yPos));
		Dollar::s_dollarList.push_back(newDollar);
	}
}

void GameState::createEnemy() {
/*! Creates new enemies
* Amount of enemies in game is HighestCurrentScore / 5.
* Example: 1 Player with 10 points       -> ( 10 / 5 = -- 2 Enemies --
* Example: 2 Players with 9 and 15 points ->( 15 / 5 = -- 3 Enemies --
*/
	if(Enemy::s_enemyList.size() >= static_cast<unsigned int>(config::MAX_ENEMIES)) return;

	unsigned int highestCurrentScore = getHighestCurrentScore();

	while( Enemy::s_enemyList.size() < ((highestCurrentScore / 5) +1) ) {
		int e_xPos;
		int e_yPos;
		//Create enemy out of screen. Randomize up/down, left/right
		if ((rand() % 2) == 1) {
			e_xPos = -config::E_WIDTH;
			e_yPos = -config::E_HEIGHT;
		} else {
			e_xPos = config::W_WIDTH+1;
			e_yPos = config::W_HEIGHT+1;
		}

		//Randomize x and y-position.
		if ((rand() % 2) == 1)  {
			e_xPos = (rand() % (config::W_WIDTH - config::E_WIDTH));
		} else {
			e_yPos = (rand() % (config::W_HEIGHT - config::E_HEIGHT));
		}

		//Finally, create new enemy
		Enemy::s_enemyList.push_back(new Enemy(config::E_SRC, e_xPos, e_yPos));
	}

}

void GameState::createRock() {
/*! Creates and removes rocks
* Amount of rocks in game is                 (HighestCurrentScore - (3 * 5)) / 5 +1
* Example: 1 Player with 10 points        -> ( 10 - (3 * 5) / 5 +1 = 0 rocks
* Example: 2 Players with 9 and 15 points -> ( 15 - (3 * 5) / 5 +1 = 1 rocks
* Example: 1 Player with 25 points        -> ( 25 - (3 * 5) / 5 +1 = 3 rocks
*/
	//Remove expired rocks
	std::list<Rock*>::iterator it_rock = Rock::s_rockList.begin();
	while(it_rock != Rock::s_rockList.end()) {
		if((*it_rock)->isExpired()) {
			Sprite::s_spriteList.remove((*it_rock));
			delete (*it_rock);
			Rock::s_rockList.erase(it_rock++);
		}
		else {
			it_rock++;
		}
	}

	int highestCurrentScore = getHighestCurrentScore() - ((config::ENEMIES_BEFORE_ROCK -1) * 5);
	if(highestCurrentScore < 0) highestCurrentScore = 0;
	int max_amount_of_rocks = highestCurrentScore / 5;
	if (max_amount_of_rocks > config::MAX_ROCKS) max_amount_of_rocks = config::MAX_ROCKS;

	while ( int(Rock::s_rockList.size()) < max_amount_of_rocks) {
		int r_yPos = -config::MAX_R_HEIGHT;
		
		int rockType = (rand() % 10 +1);
		if (rockType >= 7 && rockType <= 9) {
			int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[1]));
			Rock::s_rockList.push_back(new Rock(config::R_SRC[1], r_xPos, r_yPos, 2));
		}
		else if(rockType == 10) {
			int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[2]));
			Rock::s_rockList.push_back(new Rock(config::R_SRC[2], r_xPos, r_yPos, 3));
		}
		else {
			int r_xPos = (rand() % (config::W_WIDTH - config::R_WIDTH[0]));
			Rock::s_rockList.push_back(new Rock(config::R_SRC[0], r_xPos, r_yPos, 1));
		}
	}
}

bool GameState::isGameOver() {
	std::list<Player*>::const_iterator it_player = Player::s_playerList.begin();
	while(it_player != Player::s_playerList.end()) {
		if( !((*it_player)->isDead()) ) {
			return false;
		}
		it_player++;
	}
	return true;
}

int GameState::getHighestCurrentScore() {
	int highestCurrentScore = 0;
	std::list<Player*>::iterator it_player = Player::s_playerList.begin();
	while(it_player != Player::s_playerList.end()) {
		if ((*it_player)->getScore() > highestCurrentScore) 
			highestCurrentScore = (*it_player)->getScore();
		it_player++;
	}
	return highestCurrentScore;
}

void GameState::RenderResult() {
	std::list<Player*> winners = getWinners();
}

std::list<Player*> GameState::getWinners() {
	std::list<Player*> returnList;
	std::list<Player*>::const_iterator it_player = Player::s_playerList.begin();
	int highestScore = getHighestCurrentScore();
	while(it_player != Player::s_playerList.end()) {
		if((*it_player)->getScore() == highestScore) {
			returnList.push_back((*it_player));
		}
		it_player++;
	}
	return returnList;
}
/* END SUPPORTIVE FUNCTIONS */


