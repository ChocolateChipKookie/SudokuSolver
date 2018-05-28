#include "stdafx.h"
#include "Sudoku.h"
#include "Constants.h"
#include <iostream>
#include <bitset>

#define HORIZONTAL 0
#define VERTICAL 1

Sudoku::Sudoku()
{
	unsigned textureSize = static_cast<unsigned>((con::sudokuLevel - 1) * con::subGridThickness * con::sudokuLevel + (con::sudokuLevel + 1) * con::gridThickness + con::sudokuLevel*con::sudokuLevel*con::size);
	backgroundTexture.create(textureSize, textureSize);
	sudokuTexture.create(textureSize, textureSize);

	for (char& i : arr) i = 0;

	font.loadFromFile("arial.ttf");

	drawBackground();
}

bool Sudoku::setField(int x, int y, int value)
{
	if(value == 0)
	{
		arr[x + y * con::sudokuLines] = value;
		return true;
	}

	short int mask{ 1 };
	mask <<= value - 1;

	if (getPossible(x, y) & mask)
	{
		arr[x + y*con::sudokuLines] = value;
		return true;
	}
	return false;
}

Square Sudoku::getSquare(int x, int y)
{
	char result[con::sudokuSquareVolume]{0};

	for(int i = 0; i< con::sudokuLines;i++)
	{
		result[i] = arr[(y*con::sudokuLevel + i / con::sudokuLevel) * con::sudokuLines + x * con::sudokuLevel + i % con::sudokuLevel];
	}

	return Square(result, x, y);
}

Line Sudoku::getLine(int line, int orientation)
{
	char result[con::sudokuLines]{ 0 };

	if(orientation==HORIZONTAL)
	{
		for (int i = 0; i< con::sudokuLines; i++)
		{
			result[i] = arr[line * con::sudokuLines + i];
		}
	}
	else
	{
		for (int i = 0; i< con::sudokuLines; i++)
		{
			result[i] = arr[line + i * con::sudokuLines];
		}
	}

	return Line(result, line, orientation);
}

bool Sudoku::setSelected(int value)
{
	return setField(currentCursor.x, currentCursor.y, value);
}

void Sudoku::setCurrentCursor(sf::Vector2i currentCursor)
{
	this->currentCursor = currentCursor;
}

void Sudoku::moveCurrentCursor(int direction)
{
	switch(direction)
	{
	case 0:
		currentCursor.x++;
		currentCursor.x %= 9;
		break;
	case 1:
		currentCursor.y++;
		currentCursor.y %= 9;
		break;
	case 2:
		currentCursor.x--;
		if (currentCursor.x < 0)currentCursor.x += 9;
		break;
	case 3:
		currentCursor.y--;
		if (currentCursor.y < 0)currentCursor.y += 9;
		break;
	}
}

bool Sudoku::isPossible(short int value, int position)
{
	short int mask{ 1 };
	mask = mask << position;
	return (value & mask) != 0;
}

unsigned short int Sudoku::getPossible(int x, int y)
{
	Line l1{ getLine(x, VERTICAL) };
	Line l2{ getLine(y, HORIZONTAL) };
	Square s{ getSquare(x / con::sudokuLevel, y / con::sudokuLevel) };

	return  l1.getPossible() & l2.getPossible() & s.getPossible();
}



sf::Vector2f Sudoku::getFieldPosition(int x, int y)
{
	float x1{ static_cast<float>(con::gridThickness + (2 * con::subGridThickness + con::sudokuLevel * con::size + con::gridThickness)*(x / con::sudokuLevel) + (con::size + con::subGridThickness)*(x % con::sudokuLevel)
		)
	};
	float y1{ static_cast<float>(con::gridThickness + (2 * con::subGridThickness + con::sudokuLevel * con::size + con::gridThickness)*(y / con::sudokuLevel) + (con::size + con::subGridThickness)*(y % con::sudokuLevel)
		)
	};

	return { x1, y1 };
}

void Sudoku::drawSudoku()
{
	sf::Sprite background(backgroundTexture.getTexture());
	sudokuTexture.draw(background);

	sf::RectangleShape currentFieldRect({ static_cast<float>(con::size), static_cast<float>(con::size) });
	currentFieldRect.setFillColor(sf::Color::Blue);
	const auto position = getFieldPosition(currentCursor.x, currentCursor.y);
	currentFieldRect.setPosition(position.x, position.y);
	sudokuTexture.draw(currentFieldRect);

	sudokuTexture.display();
}

void Sudoku::toggleWrite()
{
	writePossible = !writePossible;
}

void Sudoku::writeNumbers()
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	text.setStyle(sf::Text::Regular);
	text.setFillColor(sf::Color::Cyan);

	sf::Text smallText;
	smallText.setFont(font);
	smallText.setCharacterSize(30);
	smallText.setStyle(sf::Text::Regular);
	smallText.setFillColor(sf::Color::Cyan);

	for(int i = 0; i<con::sudokuLines;i++)
	{
		for (int j = 0; j<con::sudokuLines; j++)
		{
			if(arr[j + i * con::sudokuLines] != 0)
			{
				text.setString(std::to_string(arr[j + i * con::sudokuLines]));

				auto position = getFieldPosition(j, i);
				const auto bounds = text.getLocalBounds();
				text.setOrigin({ bounds.left, bounds.top });
				position.x = position.x + (static_cast<float>(con::size) - bounds.width) / 2;
				position.y = position.y + (static_cast<float>(con::size) - bounds.height) / 2;

				text.setPosition(position.x, position.y);
				sudokuTexture.draw(text);
			}
			else if(writePossible)
			{
				auto possible = getPossible(j, i);

				for (int k = 0; k<con::sudokuLevel; k++)
				{
					for (int l = 0; l<con::sudokuLevel; l++)
					{
						if (isPossible(possible, l + k * 3))
						{
							smallText.setString(std::to_string(l + 1 + k * 3));

							auto position = getFieldPosition(j, i);
							const auto bounds = smallText.getLocalBounds();
							smallText.setOrigin({ bounds.left, bounds.top });
							position.x = position.x + static_cast<float>(con::size / 3 * l) + static_cast<float>(con::size / 3 - bounds.width) / 2;
							position.y = position.y + static_cast<float>(con::size / 3 * k) + static_cast<float>(con::size / 3 - bounds.height) / 2;

							smallText.setPosition(position.x, position.y);
							sudokuTexture.draw(smallText);
						}
					}
				}
			}
		}
	}

	sudokuTexture.display();
}

void Sudoku::drawBackground(sf::Color backgroundColor, sf::Color gridColor)
{
	unsigned squareSize{ static_cast<unsigned>((con::sudokuLevel - 1) * con::subGridThickness + con::sudokuLevel * con::size) };

	sf::RectangleShape mainSquaresRect({ static_cast<float>(squareSize),
		static_cast<float>(squareSize)
		});
	mainSquaresRect.setFillColor(backgroundColor);
	mainSquaresRect.setOutlineThickness(static_cast<float>(con::gridThickness));
	mainSquaresRect.setOutlineColor(gridColor);

	sf::RectangleShape subGridRect({ static_cast<float>(con::size),
		static_cast<float>(con::size)
		});
	subGridRect.setFillColor(backgroundColor);
	subGridRect.setOutlineThickness(static_cast<float>(con::subGridThickness));
	subGridRect.setOutlineColor(gridColor);

	for (int i = 0; i < con::sudokuLevel; i++)
	{
		for (int j = 0; j < con::sudokuLevel; j++)
		{
			mainSquaresRect.setPosition(
				static_cast<float>(con::gridThickness + (squareSize + con::gridThickness)*j),
				static_cast<float>(con::gridThickness + (squareSize + con::gridThickness)*i));
			backgroundTexture.draw(mainSquaresRect);
		}
	}

	for (int i = 0; i < con::sudokuLevel*con::sudokuLevel; i++)
	{
		for (int j = 0; j < con::sudokuLevel*con::sudokuLevel; j++)
		{
			const auto position = getFieldPosition(j, i);
			subGridRect.setPosition(position.x, position.y);
			backgroundTexture.draw(subGridRect);
		}
	}


	backgroundTexture.display();
}

sf::RenderTexture& Sudoku::getRenderTexture()
{
	drawSudoku();
	writeNumbers();
	return sudokuTexture;
}



bool Sudoku::solve()
{
	for(auto solvable : getSolvable())
	{
		setField(solvable.x, solvable.y, solvable.z);
	}
	return false;
}

std::vector<sf::Vector3i> Sudoku::getSolvable()
{
	std::vector<sf::Vector3i> solvable;

	for (int i = 0; i < con::sudokuLines; i++)
	{
		for (int j = 0; j < con::sudokuLines; j++)
		{
			if(arr[i*con::sudokuLines+ j] == 0)
			{
				unsigned short int possible = getPossible(j, i);
				if (static_cast<std::bitset<con::sudokuSquareVolume>>(possible).count() == 1)
				{
					solvable.push_back({ j, i, static_cast<int>(log2(possible & con::bottom9Mask) + 1) });
				}
			}
		}
	}

	for (int i = 0; i < con::sudokuLines; i++)
	{
		unsigned short int possibleArray[con::sudokuLines]{ 0 };
		for (int j = 0; j < con::sudokuLines; j++)
		{
			if (arr[i*con::sudokuLines + j] == 0) possibleArray[j] = getPossible(j, i);
		}

		//k je broj koji se provjerava, i je redak j je stupac
		for (int k = 0; k < con::sudokuLines; k++)
		{
			int position{0};
			int numberOf{0};
			unsigned short int mask{ static_cast<unsigned short>(1 << k) };
			for (int j = 0; j < con::sudokuLines; j++)
			{
				if (possibleArray[j] & mask & con::bottom9Mask)
				{
					numberOf++;
					if (numberOf > 1)break;
					position = j;
				}
			}
			if(numberOf==1)
			{
				solvable.push_back({ position, i, k + 1 });
			}
		}

		for (int j = 0; j < con::sudokuLines; j++)
		{
			if (arr[j*con::sudokuLines + i] == 0) possibleArray[j] = getPossible(i, j);
			else possibleArray[j] = 0;
		}

		//k je broj koji se provjerava, i je stupac, j je redak
		for (int k = 0; k < con::sudokuLines; k++)
		{
			int position{ 0 };
			int numberOf{ 0 };
			const unsigned short int mask{ static_cast<unsigned short>(1 << k) };

			for (int j = 0; j < con::sudokuLines; j++)
			{
				if (possibleArray[j] & mask & con::bottom9Mask)
				{
					numberOf++;
					if (numberOf > 1)break;
					position = j;
				}
			}
			if (numberOf == 1)
			{
				solvable.push_back({ i, position, k + 1 });
			}
		}
	}

	//i je x, j je y(i i j su djelovi rough grida)
	for (int i = 0; i < con::sudokuLevel; i++)
	{
		for (int j = 0; j < con::sudokuLevel; j++)
		{
			unsigned short int possibleArray[con::sudokuLines]{ 0 };
			for (int m = 0; m < con::sudokuLines; m++)
			{
				if (arr[(i*con::sudokuLevel + m / 3)*con::sudokuLines + j * con::sudokuLevel + m % 3] == 0)
				{
					possibleArray[m] = getPossible(j * con::sudokuLevel + m % 3, i*con::sudokuLevel + m / 3);
				}
			}

			for (int k = 0; k < con::sudokuLines; k++)
			{
				int position{ 0 };
				int numberOf{ 0 };
				unsigned short int mask{ static_cast<unsigned short>(1 << k) };
				for (int j = 0; j < con::sudokuLines; j++)
				{
					if (possibleArray[j] & mask & con::bottom9Mask)
					{
						numberOf++;
						if (numberOf > 1)break;
						position = j;
					}
				}
				if (numberOf == 1)
				{
					solvable.push_back({ j * con::sudokuLevel + position % 3, i*con::sudokuLevel + position / 3, k + 1 });
				}
			}
		}
	}


	return solvable;
}
