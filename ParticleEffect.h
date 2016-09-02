#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include <vector>

#include "Particle.h"
#include "Utils.h"


class ParticleEffect
{
public:
	ParticleEffect(std::uint32_t numParticles = 0);

	~ParticleEffect();

  void randomParticleSpeed();
  void randomParticleAcceleration();
  void randomParticleLifetime();
  void randomParticleColor();
  virtual void setInitialPosition(const sf::Vector2f &pos);

  virtual void accelerateToward(const sf::Vector2f &pos, const int &framesHeld);
  virtual void clearParticleAcceleration();

  void printParticleStates() const;

  virtual void resetParticles();

  void setNumParticles(const std::uint32_t &num);
  virtual void addForce(const Force &force);

  std::uint32_t getNumParticles() const;

  virtual ms update();
  virtual ms render(sf::RenderWindow *window, sf::RenderStates &state, sf::Shader *shader, sf::RenderTexture *tex, sf::Sprite &spr);

  void setInitialParticleState(const PhysicalState &state);
  void setWinBox(const sf::FloatRect &box);


protected:
	std::vector<Particle> m_particles;
  std::vector<Force> m_forces;

	sf::Vector2f m_forceLocation;
	sf::Vector2f m_forceAttenuation;

  int m_initNumParticles;
  sf::FloatRect m_winBox;

	hres_time_point m_pointOfLastUpdate;
	
};


#endif