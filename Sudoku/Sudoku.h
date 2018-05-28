#pragma once
#include <vector>
#include "Square.h"
#include "Line.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"



class Sudoku
{
public:
	///Constructor
	Sudoku();
	///Get square at coordinates x and y
	Square getSquare(int x, int y);
	///Get line number 'line' going in a certin orientation
	Line getLine(int line, int orientation);

	///Sets a field at coordinates x and y to a certin value
	bool setField(int x, int y, int value);
	///Sets the selected field to a certin value
	bool setSelected(int value);

	///Sets current cursor to a certin position
	void setCurrentCursor(sf::Vector2i currentCursor);

	///Moves current cursor in a certin direction(0-Right, 1-Down, 2-Left, 3-Up)
	void moveCurrentCursor(int direction);

	///Returns true if sudoku is done
	bool isDone();
	///Returns true if bit on position 'position' of value is true
	bool isPossible(short int value, int position);
	///Returns all numbers that can be currently written in a certin tile
	unsigned short int getPossible(int x, int y);

	///Draws sudoku background
	void drawSudoku();
	///Writes currently written numbers in sudoku
	void writeNumbers();
	///Toggles between 2 write modes(writeNumbers and writePossibleNumbers)
	void toggleWrite();
	///Returns sudokuTexture
	sf::RenderTexture& getRenderTexture();

	///Solves all currently solvable tiles
	bool solve();
	///Gets all currently solvable tiles
	std::vector<sf::Vector3i> getSolvable();

private:

	static sf::Vector2f getFieldPosition(int x, int y);

	sf::Vector2i currentCursor{ 0, 0 };

	sf::Font font;

	bool writePossible{ false };

	void drawBackground(sf::Color backgroundColor = sf::Color::White, sf::Color gridColor = sf::Color::Black);
	sf::RenderTexture backgroundTexture;
	sf::RenderTexture sudokuTexture;
	char arr[con::sudokuFields];
};