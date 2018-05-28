#pragma once

namespace con
{
	static int size{ 70 };
	static int gridThickness{ 6 };
	static int subGridThickness{ 2 };

	static const int sudokuLevel{ 3 };
	static const int sudokuSquareVolume{ sudokuLevel*sudokuLevel };
	static const int sudokuLines{ sudokuLevel*sudokuLevel };
	static const int sudokuFields{ sudokuLevel*sudokuLevel*sudokuLevel*sudokuLevel };

	static int bottom9Mask{ 511 };
}