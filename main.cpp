#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "SpaceShip.cpp"
#include "Comets.cpp"

int main() {

	// Creation de la fenetre
	const int WIDTH = 800;
	const int HEIGHT = 600;
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Comet Smashers", sf::Style::Close);
	window.setVerticalSyncEnabled(true);


	// Chargement de la texture
	sf::Texture texture;
	sf::Texture background;
	if (!texture.loadFromFile("texture.png") || !background.loadFromFile("space.png")) {
		std::cout << "error" << std::endl;
		return 1;
	}

	// backgound
	sf::Sprite back;
	back.setTexture(background);

	// Sons
	sf::SoundBuffer buffer;
	buffer.loadFromFile("shot.wav");

	// Creation du joueur
	SpaceShip player1 (WIDTH / 2, HEIGHT / 2);
	player1.sprite.setTexture(texture);
	player1.laserSound.setBuffer(buffer);

	// Creation des comets
	Comets comets (WIDTH, HEIGHT);
	for (int i = 0; i < comets.numberOfComets; i++) {
		comets.sprites[i].setTexture(&texture);
	}

	// Debut du programme
	sf::Clock clock;
	while (window.isOpen()) {

		// Fermeture de la fenetre
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
		}

		sf::Time elapsed = clock.restart();

		// Nettoyage de la fenetre
		window.clear();

		// Background
		window.draw(back);

		// SpaceShip logics
		player1.move(elapsed, WIDTH, HEIGHT);
		comets.move(elapsed, WIDTH, HEIGHT);
		player1.shot(elapsed);

		// Affichage de comets
		for (int i = 0; i < comets.toDisplay; i++) {
			// player1.collide(comets.sprites[i].getGlobalBounds());
			window.draw(comets.sprites[i]);
		}

		// Affichage du vaisseau et des lasers
		window.draw(player1.sprite);
		for (int i = 0; i < player1.numberOfLasers; i++) {
			// comets.collide(player1.lasers[i].getGlobalBounds());
			window.draw(player1.lasers[i]);
		}

		// Affichage
		window.display();
	}
	return 0;
}
