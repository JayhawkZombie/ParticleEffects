#include "ParticleShield.h"

ParticleShield::ParticleShield()
{

}

ParticleShield::~ParticleShield()
{

}

void ParticleShield::setCenter(const sf::Vector2f &center)
{
  m_center = center;
}

void ParticleShield::peturb(const float &amount)
{

}

void ParticleShield::accelerateToward(const sf::Vector2f &pos, const int &framesHeld)
{

}

void ParticleShield::clearParticleAcceleration()
{

}

ms ParticleShield::update()
{
  static hres_time_point lastCall = hres_clock::now();
  static int count = 0;
  count++;

  hres_time_point timeStarted = hres_clock::now();
  ms delta = std::chrono::duration_cast<ms>(hres_clock::now() - lastCall);

  sf::Vector2f partPos;
  float theta = 0;

  float posX = 0;
  float posY = 0;

  for (auto & particle : m_particles)
  {
    if (!particle.isDead()) {
      //Delta theta
      theta = particle.getTheta();
      theta += dTHETA;
      if (theta >= TWOPI)
        theta -= TWOPI;

      particle.setTheta(theta);
      
      posX = std::cos(theta) * m_distFromCenter;
      posY = std::sin(theta) * m_distFromCenter;

      particle.setPosition(sf::Vector2f(posX, posY));

    }
  }

  lastCall = hres_clock::now();

  return std::chrono::duration_cast<ms>(lastCall - timeStarted);
}

ms ParticleShield::render(sf::RenderWindow *window, sf::RenderStates &state, sf::Shader *shader, sf::RenderTexture *tex, sf::Sprite &spr)
{
  hres_time_point timeStarted = hres_clock::now();

  for (auto & particle : m_particles)
  {
    if (!particle.isDead())
      particle.render(window, state, shader, tex, spr);
  }

  return std::chrono::duration_cast<ms>(hres_clock::now() - timeStarted);
}