#include "SpaceShip.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>

SpaceShip::SpaceShip(int x, int y) {

	width = 40;
	height = 40;

	// spriteBatcher
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));

	// Positionement
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setOrigin(sf::Vector2f(width / 2, height / 2));

	// Initialistion des vitesses
	speedO = 0;
	speedX = 0;
	speedY = 0;

	// lasers
	numberOfLasers = 50;
	lasersMaxTimeout = 100;
	lasers.resize(numberOfLasers, sf::RectangleShape(sf::Vector2f(5, 2)));
	for (int i = 0; i < numberOfLasers; i++) {
		lasers[i].setOrigin(5, 1);
		lasers[i].setFillColor(sf::Color(0, 255, 0));
	}	
	lasersCounter = 0;
	lasersTimeout = 0;
	lasersAlt = true;
}

void SpaceShip::move(sf::Time elapsed, int WIDTH, int HEIGHT) {

	// Rotations
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) speedO = -500;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) speedO = 500;
	else speedO = 0;

	// Pulse
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		speedX += cos((sprite.getRotation() - 90) * 3.14 / 180) * 10;
		speedY += sin((sprite.getRotation() - 90) * 3.14 / 180) * 10;
		sprite.setTextureRect(sf::IntRect(width, 0, width, height));
	} else {
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	}


	// I stay on the screen
	int x = sprite.getPosition().x;
	int y = sprite.getPosition().y;
	if (x > WIDTH) {
		sprite.setPosition(sf::Vector2f(0, y));
	} else if (x < 0) {
		sprite.setPosition(sf::Vector2f(WIDTH, y));
	}
	if (y > HEIGHT) {
		sprite.setPosition(sf::Vector2f(x, 0));
	} else if (y < 0) {
		sprite.setPosition(sf::Vector2f(x, HEIGHT));
	}

	sprite.rotate((speedO) * elapsed.asSeconds());
	sprite.move(speedX * elapsed.asSeconds(), speedY * elapsed.asSeconds());
}

void SpaceShip::collide(sf::FloatRect boundingBox) {
	if (boundingBox.intersects(sprite.getGlobalBounds())) {
		// GAME OVER
	}
}

void SpaceShip::shot(sf::Time elapsed) {

	lasersTimeout += elapsed.asMilliseconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && lasersTimeout > lasersMaxTimeout) {

		lasersTimeout = 0;
		lasers[lasersCounter].setRotation(sprite.getRotation() - 90);

		sf::Vector2f pos;
		int norm = sqrt( (width / 2)*(width / 2) + (width / 4)*(width / 4) );
		if (lasersAlt) {
			pos.x = sprite.getPosition().x + norm * cos((lasers[lasersCounter].getRotation() - 30) * 3.14 / 180);
			pos.y = sprite.getPosition().y + norm * sin((lasers[lasersCounter].getRotation() - 30) * 3.14 / 180);
		} else {
			pos.x = sprite.getPosition().x - norm * sin((lasers[lasersCounter].getRotation() - 60) * 3.14 / 180);
			pos.y = sprite.getPosition().y + norm * cos((lasers[lasersCounter].getRotation() - 60) * 3.14 / 180);
		}
		laserSound.play();
		lasersAlt = !lasersAlt;
		lasers[lasersCounter].setPosition(pos);
		++lasersCounter;
		if (lasersCounter > numberOfLasers) lasersCounter = 0;
	}

	// deplacement des lasers
	for (int i = 0; i < numberOfLasers; i++) {

		lasers[i].move(
				cos(lasers[i].getRotation() * 3.14 / 180) * 500 * elapsed.asSeconds(),
				sin(lasers[i].getRotation() * 3.14 / 180) * 500 * elapsed.asSeconds());
	}

}
