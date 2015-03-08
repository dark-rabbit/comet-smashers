#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SpaceShip {
	
	public:
		// Constructeurs
		SpaceShip(int, int);

		// Méthodes
		void move(sf::Time, int, int);
		void collide(sf::FloatRect);
		void shot(sf::Time);
		sf::Sprite sprite;
		std::vector<sf::RectangleShape> lasers;
		sf::Sound laserSound;

	
		int width;
		int height;
		int speedO;
		int speedX;
		int speedY;
		int numberOfLasers;
		int lasersCounter;
		int lasersTimeout;
		int lasersMaxTimeout;
		bool lasersAlt;
};

#endif
