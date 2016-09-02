#include "ParticleEffect.h"

ParticleEffect::ParticleEffect(std::uint32_t numParticles)
{
  m_particles.reserve(numParticles);
}

ParticleEffect::~ParticleEffect()
{

}

void ParticleEffect::resetParticles()
{
  for (auto & particle : m_particles)
  {
    particle.setState(DefaultState);
  }
}

void ParticleEffect::printParticleStates() const
{
  for (auto & p : m_particles)
    p.printParticleState();
}

void ParticleEffect::randomParticleSpeed()
{
  for (auto & particle : m_particles)
    particle.setVelocity(randomVec2f(-50, 100));
}

void ParticleEffect::randomParticleAcceleration()
{
  for (auto & particle : m_particles)
    particle.setAcceleration(randomVec2f(-30, 60));
}

void ParticleEffect::randomParticleLifetime()
{
  for (auto & particle : m_particles)
    particle.setLifetime(randomDuration(50, 500));
}

void ParticleEffect::randomParticleColor()
{
  for (auto & particle : m_particles)
    particle.setColor(RandomColor());
}

void ParticleEffect::setNumParticles(const std::uint32_t &num)
{
  m_particles.clear();
  m_particles.reserve(num);

  m_initNumParticles = num;

  Particle p(DefaultState);
  for (int i = 0; i < num; i++)
    m_particles.push_back(p);
}

void ParticleEffect::setInitialPosition(const sf::Vector2f &pos)
{
  for (auto & particle : m_particles)
    particle.setPosition(pos);
}

void ParticleEffect::accelerateToward(const sf::Vector2f &pos, const int &framesHeld)
{
  sf::Vector2f v;
  sf::Vector2f p;
  float dist = 0;

  for (auto & particle : m_particles)
  {
    p = particle.getPosition();

    v = sf::Vector2f(pos.x - particle.getPosition().x, pos.y - particle.getPosition().y);
    
    dist = std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
    v /= dist;

    particle.setAcceleration(v * (framesHeld * 1.0f));
  }
}

void ParticleEffect::clearParticleAcceleration()
{
  for (auto & particle : m_particles)
    particle.setAcceleration(ZERO_VECTOR2F); 
}

void ParticleEffect::addForce(const Force &force)
{
  m_forces.push_back(force);
}

ms ParticleEffect::update()
{
  static hres_time_point lastCall = hres_clock::now();
  static int count = 0;
  count++;

  hres_time_point timeStarted = hres_clock::now();
  ms delta = std::chrono::duration_cast<ms>(hres_clock::now() - lastCall);

  for (auto & particle : m_particles)
  {
    particle.update(delta);

    //If the lifetime has been exceeded, mark the particle for deletion
    //if (particle.getAge() >= particle.getLifetime())
      //particle.kill();
  }

  lastCall = hres_clock::now();

  return std::chrono::duration_cast<ms>(lastCall - timeStarted);
}

ms ParticleEffect::render(sf::RenderWindow *window, sf::RenderStates &state, sf::Shader *shader, sf::RenderTexture *tex, sf::Sprite &spr)
{
  hres_time_point timeStarted = hres_clock::now();

  for (auto & particle : m_particles)
    if (!particle.isDead())
      particle.render(window, state, shader, tex, spr);

  return std::chrono::duration_cast<ms>(hres_clock::now() - timeStarted);
}

std::uint32_t ParticleEffect::getNumParticles() const
{
  return m_particles.size();
}

void ParticleEffect::setInitialParticleState(const PhysicalState &state)
{
  for (auto & particle : m_particles)
    particle.setState(state);
}

void ParticleEffect::setWinBox(const sf::FloatRect &box)
{
  m_winBox = box;

  for (auto & particle : m_particles)
    particle.setWinBox(m_winBox);
}