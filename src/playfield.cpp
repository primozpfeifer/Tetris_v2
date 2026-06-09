#pragma once
#include "playfield.hpp"


Playfield::Playfield(int cols, int rows) : m_cols(cols), m_rows(rows)
{
	m_playfieldGrid.resize(m_cols * m_rows, 0);
}


void Playfield::reset()
{
	std::fill(m_playfieldGrid.begin(), m_playfieldGrid.end(), 0);
}

bool Playfield::isCellEmpty(sf::Vector2i position)
{
	if (position.x < 1 || position.x > m_cols)
	{
		return false;
	}
	else if (position.y > m_rows)
	{
		return true;
	}
	else if (position.y < 1)
	{
		return false;
	}
	else
	{
		return getCellType(position) == 0;
	}
}

void Playfield::setCellType(sf::Vector2i position, int type)
{
	m_playfieldGrid[(position.x - 1) + (position.y - 1) * m_cols] = type;
}

int Playfield::getCellType(sf::Vector2i position)
{
	return m_playfieldGrid[(position.x - 1) + (position.y - 1) * m_cols];
}

int Playfield::clearFullRows()
{
	int fullRows = 0;

	for (int y = 1; y <= m_rows; y++)
	{
		int fullCells = countFullCells(y);

		// full	row found
		if (fullCells == m_cols)
		{
			fullRows++;
			clearRow(y);
		}

		// empty row found -> cancel the scan
		else if (fullCells == 0)
		{
			break;
		}

		// move row down for the amount of full rows found so far (if any)
		else if (fullRows > 0)
		{
			moveRowDown(y, fullRows);
		}
	}

	return fullRows;
}

int Playfield::countFullCells(int y)
{
	int fullCells = 0;
	
	for (int x = 1; x <= m_cols; x++)
	{
		if (!isCellEmpty(sf::Vector2i(x, y)))
		{
			fullCells++;
		}
	}

	return fullCells;
}

void Playfield::clearRow(int y)
{
	for (int x = 1; x <= m_cols; x++)
	{
		setCellType(sf::Vector2i(x, y), 0);
	}
}

void Playfield::moveRowDown(int y, int rows)
{
	for (int x = 1; x <= m_cols; x++)
	{
		setCellType(sf::Vector2i(x, y - rows), getCellType(sf::Vector2i(x, y)));	// copy row down
		setCellType(sf::Vector2i(x, y), 0);											// clear row
	}
}