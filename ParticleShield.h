#ifndef __S_PARTICLESHIELD_H
#define __S_PARTICLESHIELD_H

#include "ParticleEffect.h"

#include <cmath>

const float TWOPI =  2 * 3.141592653;
const float dTHETA = 2 * TWOPI / 100.0f;

class ParticleShield : public ParticleEffect
{
public:
  ParticleShield();
  ~ParticleShield();

  void setCenter(const sf::Vector2f &center);
  virtual void peturb(const float &amount);

  virtual void accelerateToward(const sf::Vector2f &pos, const int &framesHeld);
  virtual void clearParticleAcceleration();

  virtual ms update();
  virtual ms render(sf::RenderWindow *window, sf::RenderStates &state, sf::Shader *shader, sf::RenderTexture *tex, sf::Sprite &spr);


protected:
  sf::Vector2f m_center;
  float m_distFromCenter;
};


#endif
