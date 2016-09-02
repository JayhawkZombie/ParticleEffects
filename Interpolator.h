#ifndef __S_INTERPOLATOR_H
#define __S_INTERPOLATOR_H

#include <vector>
#include <chrono>
#include <iostream>

#include <SFML\Graphics.hpp>

#include "Utils.h"


class Interpolator
{
public:
  Interpolator();
  ~Interpolator();

  bool addInterpolation(const float &distance, const sf::Color &value);
  sf::Color getInterpolatedValue(const float &factor);

private:
  std::vector<std::pair<float, sf::Color>> m_interpolations;
  std::uint32_t m_currentInterpolation;
  ms m_duration;
};


#endif
