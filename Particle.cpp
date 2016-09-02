#include "Particle.h"

Particle::Particle(const PhysicalState state)
{
  m_state = state;
  m_interpolator = nullptr;
  dead = false;
  printedDead = false;

  m_shape.setSize(sf::Vector2f(1, 1));
  m_shape.setFillColor(sf::Color::Transparent);

  m_drag = sf::Vector2f(0.01, 0.01);
  m_maxSpeed = sf::Vector2f(100, 100);

  m_theta = 0;
}

Particle::~Particle()
{

}

void Particle::reset()
{
  m_state = DefaultState;
  m_shape.setFillColor(m_state.color);
  dead = false;
}

void Particle::setState(const PhysicalState &state)
{
  m_state = state;
}

void Particle::setInterpolator(Interpolator *interpolator)
{
  m_interpolator = interpolator;
}

void Particle::setPosition(const sf::Vector2f &pos)
{
  m_state.position = pos;
}

void Particle::setScale(const sf::Vector2f &scale)
{
  m_state.scale = scale;
}

void Particle::setVelocity(const sf::Vector2f &velocity)
{
  m_state.velocity = velocity;
}

void Particle::setAcceleration(const sf::Vector2f &acceleration)
{
  m_state.acceleration = acceleration;
}

void Particle::applyForce(const sf::Vector2f &force)
{
  
}
void Particle::setColor(const sf::Color &color)
{
  m_state.color = color;
}

void Particle::setWinBox(const sf::FloatRect &box)
{
  m_winBox = box;
}

void Particle::setTheta(const float &theta)
{
  m_theta = theta;
}

void Particle::setLifetime(const ms &lifetime)
{
  m_state.lifetime = lifetime;
}

ms Particle::getAge() const
{
  return m_state.age;
}

ms Particle::getLifetime() const
{
  return m_state.lifetime;
}

sf::Vector2f Particle::getPosition() const
{
  return m_state.position;
}

sf::Vector2f Particle::getScale() const
{
  return m_state.scale;
}

sf::Vector2f Particle::getVelocity() const
{
  return m_state.velocity;
}

sf::Vector2f Particle::getAcceleration() const
{
  return m_state.acceleration;
}

float Particle::getTheta() const
{
  return m_theta;
}

void Particle::update(const ms &delta)
{
  m_state.age += delta;

  //If we're too old, no sense in updating our state
  //if (m_state.age >= m_state.lifetime) {
  //  kill();
  //  return;
  //}

  m_state.acceleration.x *= (1 - m_drag.x * 0.01);
  m_state.acceleration.y *= (1 - m_drag.y * 0.01);

  m_state.velocity += m_state.acceleration * (delta.count() * 0.0001f);
  
  if (std::abs(m_state.velocity.x) > 40) {
    m_state.velocity.x *= (1 - m_drag.x * 0.1);
    m_state.acceleration.x = 0;
  }
  if (std::abs(m_state.velocity.y) > 40) {
    m_state.velocity.y *= (1 - m_drag.x * 0.1);
    m_state.acceleration.y = 0;
  }
    

  m_state.position += m_state.velocity * ( delta.count() * 0.0005f);

  if (m_state.position.x >= m_winBox.width)
    m_state.velocity.x *= -1;
  else if (m_state.position.x < 0)
    m_state.velocity.x *= -1;
  if (m_state.position.y >= m_winBox.height)
    m_state.velocity.y *= -1;
  else if (m_state.position.y < 0)
    m_state.velocity.y *= -1;

  m_shape.setPosition(m_state.position);
  m_shape.setFillColor(m_state.color);
}

void Particle::hide()
{

}

void Particle::show()
{

}

void Particle::render(sf::RenderWindow *window, sf::RenderStates &state, sf::Shader *shader, sf::RenderTexture *tex, sf::Sprite &spr)
{
  sf::Color c;

  if (!dead)
  {
    c = m_shape.getFillColor();

    tex->draw(m_shape);

    shader->setParameter("frag_LightOrigin", m_shape.getPosition());
    shader->setParameter("frag_LightColor", sf::Vector3f(c.r, c.g, c.b));
    //shader->setParameter("frag_LightAttenuation", 50.0f);

    state.shader = shader;
    state.blendMode = sf::BlendAdd;

    tex->draw(spr, state);
    
    //window->draw(m_shape, shader);
  }
}

void Particle::kill()
{
  //dead = true;
}

bool Particle::isDead() const
{
  return dead;
}

void Particle::printParticleState() const
{
  std::cout << "Position:     (" << m_state.position.x     << ", " << m_state.position.y     << ")" << std::endl;
  std::cout << "Acceleration: (" << m_state.acceleration.x << ", " << m_state.acceleration.y << ")" << std::endl;
  std::cout << "Velocity:     (" << m_state.velocity.x     << ", " << m_state.velocity.y     << ")" << std::endl;
  std::cout << "Age:          (" << m_state.age.count() << ", Lifetime: " << m_state.lifetime.count() << std::endl;
}