#ifndef LWR_ABSTRACTSTATE_HPP
#define LWR_ABSTRACTSTATE_HPP

#include <SDL.h>
#include <LawyerEngine/LawyerEngine.hpp>

class AbstractState : public lwe::State
{
public:
  virtual ~AbstractState() {}
  virtual bool init() override { return true; }
  virtual void cleanup() override {}

protected:
  AbstractState() : lwe::State() {}
};

#endif
