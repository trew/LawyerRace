#ifndef LWR_EVENTCONDITION_HPP
#define LWR_EVENTCONDITION_HPP

#include <SDL.h>

#include <vector>
#include <memory>

#include <LawyerRace/Event/Trigger.hpp>

class EventCondition
{
public:
  EventCondition();
  virtual ~EventCondition();

  bool isTriggered(const SDL_Event& ev) const;

  void addTrigger(Trigger* trigger);
  bool hasTriggers() const;

private:
  std::vector<std::shared_ptr<Trigger>> triggers;
};

#endif