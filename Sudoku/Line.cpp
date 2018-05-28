#include "stdafx.h"
#include "Line.h"

Line::Line(char * values, int x, int orientation): x(x), orientation(orientation)
{
	for (int i = 0, k = con::sudokuLevel*con::sudokuLevel; i< k; i++)
	{
		this->values[i] = values[i];
	}
}

short int Line::getPossible()
{
	short int result{ 0 };
	for (int i = 0, k = con::sudokuLevel*con::sudokuLevel; i< k; i++)
	{
		short int mask{ 1 };
		if (values[i])
		{
			mask <<= values[i] - 1;
			result |= mask;
		}
	}
	return ~result;
}


