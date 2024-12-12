#pragma once
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

/**
 *	@file Game.h
 * 
 * 	@brief Class that acts like Game Engine - wrapper class		
 * 
 */
class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	std::vector<sf::RectangleShape> enimies;
	sf::RectangleShape enemy;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game Logic
	bool endGame;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnimies;
	unsigned points;
	bool mouseHeld;
	int health;

	// Resources 
	sf::Font font;

	// text
	sf::Text uiText;

	// Private Functions
	void initVars();
	void initWindows();
	void initEnimies();
	void initFonts();
	void initText();

public:
	// C'tor and D'tor
	Game();
	virtual ~Game();

	// Accessors 
	const bool running() const;
	const bool getEndGame() const;

	// Functions
	void pollEvents();
	void update();
	void render();
	void updateMousePosition();
	void spawnEnimies();
	void updateEnimies();
	void renderEnimies(sf::RenderTarget& target);
	void updateText();
	void renderText(sf::RenderTarget& target);
};

