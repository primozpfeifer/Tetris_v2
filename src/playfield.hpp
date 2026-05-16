#pragma once
#include "tetromino.hpp"


class Playfield
{
private:

	int								m_cols = 0;
	int								m_rows = 0;
	std::vector<int>				m_playfieldGrid;


public:

	Playfield(int cols, int rows);

	void reset();
	bool isCellEmpty(sf::Vector2i position);
	void setCellType(sf::Vector2i position, int type);
	int getCellType(sf::Vector2i position);
	int clearFullRows();
	int countFullCells(int y);
	void clearRow(int y);
	void moveRowDown(int y, int rows);
};