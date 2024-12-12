#include "Game.h"
/**
 * @brief Calculates the factorial of a number.
 *
 * @param
 *
 * @return
 *
 * @details
 */
 /**
  * @brief Calculates the factorial of a number.
  *
  */
void Game::initVars()
{
	this->window = nullptr;
	this->endGame = false;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnimies = 10;
	this->points = 0;
	this->mouseHeld = false;
	this->health = 10;
}
/**
 * @brief Calculates the factorial of a number.
 *
 */
void Game::initWindows()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

}
/**
 * @brief Calculates the factorial of a number.
 *
 */
void Game::initEnimies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}
void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Montserrat-Bold.ttf")) {
		std::cout << "Error: init Failed to load font" << std::endl;
	}
}
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");

}
/**
 * @brief Calculates the factorial of a number.
 *
 */
Game::Game()
{
	this->initVars();
	this->initWindows();
	this->initFonts();
	this->initText();
	this->initEnimies();
}
/**
 * @brief Calculates the factorial of a number.
 *
 */
Game::~Game()
{
	delete this->window;
}
/**
 * @brief Calculates the factorial of a number.
 *
 */
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

// ------------------------- Fucntions ---------------------

 /**
  * @brief Calculates the factorial of a number.
  *
  */
void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;

		}
	}

}
/**
 * @brief Calculates the factorial of a number.
 *
 */
void Game::update()
{
	this->pollEvents();
	
	if (this->endGame == false) {
		this->updateMousePosition();
		this->updateText();
		this->updateEnimies();
	}
	if (this->health <= 0) {
		this->endGame = true;
	}
}
/**
*	@return void
*		- clear old frame
*		- render new objects
*		- display frame on window
*/
void Game::render()
{
	this->window->clear();

	//draw game objects - TBD
	this->renderEnimies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}
/**
 * @brief update mouse position relative to window
 *
 * @details
 */
void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
/**
 * @brief spawn enimies and set their color and position
 * set a random position, color, and add enemy to the vector.
 * 
 * @return void 
 *
 */
void Game::spawnEnimies()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>((this->window->getSize().x) - this->enemy.getSize().x)),
		0.f
	);
	this->enemy.setFillColor(sf::Color::Green);
	this->enimies.push_back(this->enemy);


}
/**
 * @brief update enemy spawn timer and spawn enimies 
 * 
 * when the total amount of enimies is smaller than the max
 * 
 *moves the enimies down towards
 */
void Game::updateEnimies()
{
	if (this->enimies.size() < this->maxEnimies) {
		if (this->enemySpawnTimer >= enemySpawnTimerMax) {
			// spawn the enemy and reset timer
			this->spawnEnimies();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}
	for (int i = 0; i < this->enimies.size(); i++) {
		this->enimies[i].move(0.f, 2.f);

		// if the enemy is passed the bottom of the screen 
		if (this->enimies[i].getPosition().y > this->window->getSize().y) {
			this->enimies.erase(this->enimies.begin() + i);
			health -= 1;
			std::cout << "Health :" << health << std::endl;
		}
	}

	// Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < this->enimies.size() && deleted == false; i++) {
				if (enimies[i].getGlobalBounds().contains(this->mousePosView)) {

					// delete the enemy
					this->enimies.erase(this->enimies.begin() + i);
					deleted = true;

					//Gain points
					this->points += 1.f;
					std::cout << "Points :" << points << std::endl;
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
/**
 * @brief TBD
 *
 */
void Game::renderEnimies(sf::RenderTarget& target)
{
	for (auto& e : enimies) {
		target.draw(e);
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << std::endl
		<< "Health: " << this->health << std::endl;
	this->uiText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

