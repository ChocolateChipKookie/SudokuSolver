#pragma once
#define SQUARE_TILES 9 
#include <vector>
#include "Constants.h"


class Square
{
public:
	Square(char* values, int x, int y);
	short int getPossible();

	int x, y;
	char values[con::sudokuSquareVolume];
	short int possible;

private:

};
