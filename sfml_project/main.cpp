#include <iostream>
#include <vector>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../ParticleEffect.h"
#include "../ParticleShield.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "And there was light");

  srand(time(NULL));

  ParticleEffect effect;

  effect.setNumParticles(800);
  //effect.randomParticleAcceleration();
  effect.randomParticleSpeed();
  effect.randomParticleLifetime();
  effect.randomParticleColor();

  effect.setWinBox(sf::FloatRect(0, 0, 800, 800));

  effect.setInitialPosition(sf::Vector2f(400, 400));

  //effect.printParticleStates();

  ParticleShield shield;
  shield.setNumParticles(300);
  shield.randomParticleSpeed();
  shield.randomParticleColor();
  shield.setWinBox(sf::FloatRect(NOLIMIT_VECTOR2F, NOLIMIT_VECTOR2F));
  shield.setInitialPosition(sf::Vector2f(200, 200));
  shield.setCenter(sf::Vector2f(200, 200));

  sf::Text fps;
  sf::Text pUpdate;
  sf::Text pRender;
  sf::Text numParticles;
  sf::Font font;

  bool fontLoaded = false;

  if (!font.loadFromFile("D:\\Fonts\\OpenSans\\OpenSans-Regular.ttf")) {
    std::cerr << "Failure to load font" << std::endl;
  }
  else {
    fontLoaded = true;
    fps.setFont(font);
    pUpdate.setFont(font);
    pRender.setFont(font);
    numParticles.setFont(font);
  }

  fps.setPosition(sf::Vector2f(20, 20));
  fps.setCharacterSize(10);

  pUpdate.setPosition(sf::Vector2f(20, 40));
  pUpdate.setCharacterSize(10);

  pRender.setPosition(sf::Vector2f(20, 60));
  pRender.setCharacterSize(10);

  numParticles.setPosition(sf::Vector2f(20, 80));
  numParticles.setCharacterSize(10);

  ms timeForFrameUpdate = ms(0);
  hres_time_point now = hres_clock::now();

  ms timeForParticleUpdate = ms(0);
  ms timeForParticleRender = ms(0);

  bool mouseWasDown = false;

  int framesHeld = 0;

  sf::Shader *shader = new sf::Shader();
  shader->loadFromFile("shader.frag", sf::Shader::Fragment);

  shader->setParameter("frag_ScreenResolution", sf::Vector2f(800, 800));
  shader->setParameter("frag_LightAttenuation", 600.f);

  sf::RenderStates states;
  states.shader = shader;
  states.blendMode = sf::BlendAdd;

  sf::RenderTexture rTexture;
  rTexture.create(800, 800);
  sf::Sprite worldSprite;
  worldSprite.setTexture(rTexture.getTexture());

  sf::RectangleShape bg;
  bg.setFillColor(sf::Color::Black);
  bg.setPosition(sf::Vector2f(0, 0));
  bg.setSize(sf::Vector2f(800, 80));

  sf::CircleShape c;
  c.setPosition(sf::Vector2f(200, 200));
  c.setRadius(2);
  c.setFillColor(sf::Color::Red);

  sf::CircleShape m;
  m.setPosition(sf::Vector2f(0, 0));
  m.setRadius(10);
  m.setFillColor(sf::Color::Transparent);

  bool up = false;

	while (window.isOpen())
	{
		sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      else if (event.type == sf::Event::MouseButtonReleased)
        effect.clearParticleAcceleration();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      framesHeld++;
      effect.accelerateToward(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window ).y), framesHeld);
    }
    else
    {
      framesHeld = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      up = true;
    }
    if (up && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
      effect.setNumParticles(effect.getNumParticles() * 1.2);
      effect.randomParticleSpeed();
      effect.randomParticleLifetime();
      effect.randomParticleColor();
      effect.setWinBox(sf::FloatRect(0, 0, 800, 800));

      effect.setInitialPosition(sf::Vector2f(400, 400));
      up = false;
    }

    now = hres_clock::now();

    window.clear();
    //window.draw(bg, shader);
    rTexture.clear();

    timeForParticleUpdate = effect.update();
    timeForParticleRender = effect.render(&window, states, shader, &rTexture, worldSprite);
    timeForFrameUpdate = std::chrono::duration_cast<ms>(hres_clock::now() - now);

    //shield.update();
    //shield.render(&window, states, shader);

    if (fontLoaded) {
      fps.setString(std::string         ("fps         : " + std::to_string(1000.f / timeForFrameUpdate.count())));
      pUpdate.setString(std::string     ("pUpdate     : " + std::to_string(timeForParticleUpdate.count())));
      pRender.setString(std::string     ("pRender     : " + std::to_string(timeForParticleRender.count())));
      numParticles.setString(std::string("numParticles: " + std::to_string(effect.getNumParticles())));
    }

    states.blendMode = sf::BlendAdd;

    rTexture.draw(c);
    shader->setParameter("frag_LightOrigin", sf::Vector2f(c.getPosition().x + c.getRadius() / 2, c.getPosition().y + c.getRadius() / 2));
    shader->setParameter("frag_LightColor", sf::Vector3f(c.getFillColor().r, c.getFillColor().g, c.getFillColor().b));
    //shader->setParameter("frag_LightAttenuation", 100.0f);
    rTexture.draw(worldSprite, states);

    rTexture.draw(m);
    m.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
    shader->setParameter("frag_LightOrigin", m.getPosition());
    shader->setParameter("frag_LightColor", sf::Vector3f(0, 255, 255));
    //shader->setParameter("frag_LightAttenuation", 500.f);
    rTexture.draw(worldSprite, states);

    rTexture.display();
    window.draw(worldSprite);

    window.draw(fps);
    window.draw(pUpdate);
    window.draw(pRender);
    window.draw(numParticles);

    window.display();
	}

  delete shader;

	return 0;
}