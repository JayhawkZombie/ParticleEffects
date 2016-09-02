#include "Utils.h"

template <typename duration>
duration GetTimeSincePoint(const hres_time_point &point)
{
  hres_time_point now = GetCurrentEpoch();

  return std::chrono::duration_cast<duration>(now - point);
}

ms randomDuration(const int &lowerBound, const int &upperBound)
{
  int time = rand() % upperBound + lowerBound;

  return ms(time);
}

sf::Vector2f randomVec2f(const int &lowerBound, const int &upperBound)
{
  return sf::Vector2f(rand() % upperBound + lowerBound, rand() % upperBound + lowerBound);
}

hres_time_point GetCurrentEpoch()
{
  return hres_clock::now();
}

sf::Color BlendColors(const sf::Color &color1, const sf::Color &color2, const float &factor)
{
  sf::Color newColor;

  newColor.r = (1 - factor) * color1.r + factor * color2.r;
  newColor.g = (1 - factor) * color1.g + factor * color2.g;
  newColor.b = (1 - factor) * color1.b + factor * color2.b;
  newColor.a = (1 - factor) * color1.a + factor * color2.a;

  return newColor;
}

sf::Color RandomColor()
{
  sf::Color c(
    rand() % 255, rand() % 255, rand() % 255
  );

  return c;
}