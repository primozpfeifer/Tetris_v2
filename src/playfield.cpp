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

int Playfield::clearLines()
{
	int cleared = 0;

	for (int y = 1; y <= m_rows; y++)
	{
		bool full = true;

		// check for full lines
		for (int x = 1; x <= m_cols; x++)
		{
			if (isCellEmpty(sf::Vector2i(x, y)))
			{
				full = false;
				break;
			}
		}
		// full	line found
		if (full)
		{
			cleared++;
			// copy all rows above the current row down one row
			for (int y2 = y; y2 < m_rows; y2++)
			{
				const auto currentLineIterator = m_playfieldGrid.begin() + (y2 - 1) * m_cols;
				std::copy_n(currentLineIterator + m_cols, m_cols, currentLineIterator);
			}
			// clear top row
			std::fill(m_playfieldGrid.end() - m_cols, m_playfieldGrid.end(), 0);
			y--;
		}
	}
	return cleared;
}
