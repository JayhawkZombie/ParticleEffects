#ifndef __S_PARTICLE_H
#define __S_PARTICLE_H

#include "Interpolator.h"
#include "Utils.h"

class Particle
{
public:
  Particle(const PhysicalState state = DefaultState);
  ~Particle();

  void setState(const PhysicalState &state);

  void setInterpolator(Interpolator *interpolator);
  void setPosition(const sf::Vector2f &pos);
  void setScale(const sf::Vector2f &scale);
  void setVelocity(const sf::Vector2f &velocity);
  void setAcceleration(const sf::Vector2f &acceleration);
  void applyForce(const sf::Vector2f &force);
  void setColor(const sf::Color &color);
  void setWinBox(const sf::FloatRect &box);
  void setTheta(const float &theta);

  void setLifetime(const ms &lifetime);
  
  ms getAge() const;
  ms getLifetime() const;

  sf::Vector2f getPosition() const;
  sf::Vector2f getScale() const;
  sf::Vector2f getVelocity() const;
  sf::Vector2f getAcceleration() const;
  float getTheta() const;

  virtual void update(const ms &delta);
  virtual void hide();
  virtual void show();
  virtual void render(sf::RenderWindow *window, sf::RenderStates &state, sf::Shader *shader, sf::RenderTexture *tex, sf::Sprite &spr);

  void printParticleState() const;

  virtual void kill();
  virtual void reset();
  bool isDead() const;


protected:
  PhysicalState m_state;
  Interpolator *m_interpolator;

  sf::RectangleShape m_shape;
  sf::FloatRect m_winBox;

  sf::Vector2f m_drag;
  sf::Vector2f m_maxSpeed;

  float m_theta;

  bool dead;
  bool printedDead;

};

#endif
