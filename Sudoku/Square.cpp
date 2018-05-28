#include "stdafx.h"
#include "Square.h"

Square::Square(char * values, int x, int y) : x{ x }, y{ y }
{
	for(int i = 0; i< con::sudokuSquareVolume;i++)
	{
		this->values[i] = values[i];
	}
}

short int Square::getPossible()
{
	short int result{ 0 };
	for (int i = 0; i< con::sudokuSquareVolume; i++)
	{
		short int mask{ 1 };
		if(values[i])
		{
			mask <<= values[i] - 1;
			result |= mask;
		}
	}
	return ~result;
}
