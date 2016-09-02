#include "Interpolator.h"

Interpolator::Interpolator()
{
  m_currentInterpolation = 0;
  m_duration = std::chrono::milliseconds(0);
}

Interpolator::~Interpolator()
{

}

bool Interpolator::addInterpolation(const float &distance, const sf::Color &value)
{
  m_interpolations.push_back(std::pair<float, sf::Color>(distance, value));

  return true;
}

sf::Color Interpolator::getInterpolatedValue(const float &factor)
{
  std::uint32_t Se = 0;
  std::uint32_t Sb = 0;

  while (Se < m_interpolations.size() && m_interpolations[Se].first < factor)
    Se++;

  float Sl = m_interpolations[Se].first - m_interpolations[Sb].first;

  sf::Color interpolatedColor = m_interpolations[Se].second;

  if (Sl) {
    float de = (factor - m_interpolations[Sb].first) / Sl;
    
    interpolatedColor = BlendColors(m_interpolations[Se].second, m_interpolations[Sb].second, de);
  }

  return interpolatedColor;
}