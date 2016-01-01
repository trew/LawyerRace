#ifndef LWR_MENUSTATE_HPP
#define LWR_MENUSTATE_HPP

#include <LawyerEngine/Event/EventCondition.hpp>

#include <LawyerRace/Core/AbstractState.hpp>
#include <LawyerRace/Entity/AbstractEntity.hpp>
#include <LawyerRace/Entity/Rock.hpp>

class MenuState: public AbstractState
{
public:
  MenuState();
  virtual ~MenuState();

  /* STATE FUNCTIONS */
  bool init() override;
  void cleanup() override;

  void copyDataForInterpolation() override;

  void update(float timeStep) override;
  bool handleEvent(const SDL_Event &ev) override;
  void render(SDL_Renderer* renderer, float timeAlpha) override;

private:
  const static int NORMAL = 1;
  const static int SELECT_PLAYERS = 2;
  int internalState { NORMAL };

  lwe::EventCondition back;

  std::shared_ptr<AbstractEntity> menuBorder;
  std::shared_ptr<AbstractEntity> title;

  std::vector<std::shared_ptr<lwe::Button>> playersButtons;
  std::vector<std::shared_ptr<lwe::Button>> menuButtons;

  lwe::TextureRegion* rockRegion[3];
  std::list<std::shared_ptr<Rock>> rocks;
};

#endif
