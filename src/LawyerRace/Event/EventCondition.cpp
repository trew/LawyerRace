#include <LawyerRace/Event/EventCondition.hpp>

EventCondition::EventCondition()
{
}

EventCondition::~EventCondition()
{
}

bool EventCondition::isTriggered(const SDL_Event& ev) const
{
  for (const std::shared_ptr<Trigger>& trigger : triggers)
  {
    if (trigger->isTriggered(ev))
    {
      return true;
    }
  }
  return false;
}

void EventCondition::addTrigger(Trigger* trigger)
{
  triggers.push_back(std::shared_ptr<Trigger>(trigger));
}

bool EventCondition::hasTriggers() const
{
  return !triggers.empty();
}