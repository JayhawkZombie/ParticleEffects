#ifndef __S_UTILS_H
#define __S_UTILS_H

#include <chrono>
#include <cstdlib>

#include <SFML\Graphics.hpp>

typedef std::chrono::milliseconds ms;
typedef std::chrono::high_resolution_clock::time_point hres_time_point;
typedef std::chrono::high_resolution_clock hres_clock;

typedef sf::Vector2f V2f;

const float __MAX_FLOAT = std::numeric_limits<float>::max();

const sf::Vector2f ZERO_VECTOR2F = sf::Vector2f(0, 0);
const sf::Vector2f ONE_VECTOR2F = sf::Vector2f(1, 1);
const sf::Vector2f NOLIMIT_VECTOR2F = sf::Vector2f(__MAX_FLOAT, __MAX_FLOAT);
const ms ZERO_TIME = ms(0);

template <typename duration>
duration GetTimeSincePoint(const hres_time_point &tp);

ms randomDuration(const int &lowerBound, const int &upperBound);

hres_time_point GetCurrentEpoch();

sf::Color BlendColors(const sf::Color &color1, const sf::Color &color2, const float &factor);
sf::Color RandomColor();

sf::Vector2f randomVec2f(const int &lowerBound, const int &upperBound);

struct PhysicalState
{
  PhysicalState() {
    position = velocity = acceleration = ZERO_VECTOR2F;
    scale = ONE_VECTOR2F;
    color = sf::Color::White;
    lifetime = age = ZERO_TIME;
    mass = 1;
  }
  PhysicalState(const PhysicalState &s) {
    position = s.position; velocity = s.velocity; acceleration = s.acceleration;
    scale = s.scale; color = s.color; lifetime = s.lifetime; age = s.age;
  }

  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  sf::Vector2f scale;

  sf::Color color;

  ms lifetime;
  ms age;

  float mass;
};

struct Force
{
  Force() {
    magnitude = ONE_VECTOR2F;
    attenuation = NOLIMIT_VECTOR2F;
    position = ZERO_VECTOR2F;
  }

  Force(const Force &f) {
    magnitude = f.magnitude; attenuation = f.attenuation; position = f.position;
  }

  sf::Vector2f magnitude;
  sf::Vector2f attenuation;
  sf::Vector2f position;
};

const PhysicalState DefaultState = PhysicalState();
const Force DefaultForce = Force();

#endif
