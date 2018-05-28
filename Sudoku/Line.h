#pragma once
#define LINE_TILES 9
#include <vector>
#include "Constants.h"

class Line
{
public:
	Line(char* values, int x, int orientation);
	short int getPossible();

	int x, orientation;
	char values[con::sudokuLines];
	short int possible;
};
