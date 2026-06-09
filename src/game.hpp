#pragma once
#include "playfield.hpp"
#include "menu.hpp"
#include <memory>
#include <random>
#include <chrono>


enum GameState { Init = 0, Playing, Pause, Gameover };
enum MinoDropType { Normal = 0, Soft, Hard };
enum Randomizer { FullRandom = 0, ShuffleBag };

struct Config
{
	int									cols = 10;
	int									rows = 20;
	int									cellSize = 80;
	int									topBarHeight = 100;
	float								gameSpeed = 0.8f;
	Randomizer							randomizer = ShuffleBag;
	bool								showMinoShadow = true;

	std::array<sf::Color, 11>			color =
	{
		sf::Color(37, 36, 86),			// empty cell
		sf::Color(0, 255, 255),			// I shape
		sf::Color(0, 0, 255),			// J shape
		sf::Color(255, 127, 0),			// L shape
		sf::Color(255, 255, 0),			// O shape
		sf::Color(0, 255, 0),			// S shape
		sf::Color(128, 0, 128),			// T shape
		sf::Color(255, 0, 0),			// Z shape
		sf::Color(32, 32, 32),			// border
		sf::Color(0, 0, 0),				// spacing
		sf::Color(255, 255, 255, 16)	// mino shadow
	};
};

struct Score
{
	int points = 0;
	int rows = 0;
	int level = 0;
	float playTime = 0;
	int softDropRows = 0;
	int hardDropRows = 0;
};


class Game
{
private:

	Config								m_config;

	std::shared_ptr<sf::RenderWindow>	m_window;
	std::unique_ptr<Menu>				m_menu;
	std::unique_ptr<Playfield>			m_playfield;
	std::shared_ptr<Tetromino>			m_activeMino;
	std::shared_ptr<Tetromino>			m_minoShadow;

	sf::Clock							m_gameTimer;
	sf::Font							m_font;
	Score								m_score;
	std::vector<int>					m_shuffleBag;

	bool								m_running = false;
	GameState							m_gameState = Init;
	float								m_gameSpeed = 0.0f;
	float								m_timer = 0.0f;
	bool								m_moveMinoDown = false;
	MinoDropType						m_minoDropType = Normal;
	sf::Keyboard::Key					m_lastPressedKey = sf::Keyboard::Unknown;


public:

	Game();

	void run();


private:

	void initWindow();
	void initGame();
	void resetGame();
	int randomShapeType();
	void updateScore(int rows);
	void togglePause();

	void spawnMino();
	void moveMino(sf::Vector2i velocity);
	void rotateMino(int rotation);
	void updateShadowPosition();
	bool checkCollision(const std::array<sf::Vector2i, 4>& positions);

	void movement();
	void collision();
	void inputEvents();
	
	void render();
	sf::Color getColor(int type);
	void drawTopBar();
	void drawPlayField();
	void drawActiveMino();
	void drawMino(const std::shared_ptr<Tetromino>& tetromino, sf::Color color);
};
