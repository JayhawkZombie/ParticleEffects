#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H

#include <SFML\Graphics.hpp>

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(const sf::Vector2f &loc, const bool &constemit);

	ParticleEmitter(const ParticleEmitter &) = delete;
	ParticleEmitter(const ParticleEmitter &&) = delete;

	~ParticleEmitter();

	void setEmitLocation(const sf::Vector2f &pos);
	void setEmitSpeed(const float &speed);
	void setInitialEmitForce(const sf::Vector2f &force);

	void reEmit();
	void stopEmitting();

	void emit();

private:
	sf::Vector2f m_location;
	sf::Vector2f m_initialEmitForce;
	float m_emitSpeed;

	bool m_constantEmit;
	
};

#endif