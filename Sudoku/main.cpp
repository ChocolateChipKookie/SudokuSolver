// MandelbrotSet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Sudoku.h"
#include <iostream>

int main()
{

	unsigned windowSize = static_cast<unsigned>(2 * con::subGridThickness * 3 + 4 * con::gridThickness + 9 * con::size);
	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Sudoku");
	window.setPosition({ 10, 10 });

	Sudoku sudoku;

	sf::RectangleShape rect({50, 50});
	rect.setPosition(0.f, 0.f);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	rect.setFillColor(sf::Color::White);

	sf::Sprite sprite;

	bool solve{ false };

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
					sudoku.moveCurrentCursor(0);
					break;
				case sf::Keyboard::Left:
					sudoku.moveCurrentCursor(2);
					break;
				case sf::Keyboard::Up:
					sudoku.moveCurrentCursor(3);
					break;
				case sf::Keyboard::Down:
					sudoku.moveCurrentCursor(1);
					break;


				case sf::Keyboard::LShift:
					sudoku.toggleWrite();
					break;

				case sf::Keyboard::RShift:
					solve = !solve;
					break;

				case sf::Keyboard::BackSpace:
					sudoku.setSelected(0);
					break;

				case sf::Keyboard::Num1:
				case sf::Keyboard::Numpad1:
					sudoku.setSelected(1);
					break;
				case sf::Keyboard::Num2:
				case sf::Keyboard::Numpad2:
					sudoku.setSelected(2);
					break;
				case sf::Keyboard::Num3:
				case sf::Keyboard::Numpad3:
					sudoku.setSelected(3);
					break;
				case sf::Keyboard::Num4:
				case sf::Keyboard::Numpad4:
					sudoku.setSelected(4);
					break;
				case sf::Keyboard::Num5:
				case sf::Keyboard::Numpad5:
					sudoku.setSelected(5);
					break;
				case sf::Keyboard::Num6:
				case sf::Keyboard::Numpad6:
					sudoku.setSelected(6);
					break;
				case sf::Keyboard::Num7:
				case sf::Keyboard::Numpad7:
					sudoku.setSelected(7);
					break;
				case sf::Keyboard::Num8:
				case sf::Keyboard::Numpad8:
					sudoku.setSelected(8);
					break;
				case sf::Keyboard::Num9:
				case sf::Keyboard::Numpad9:
					sudoku.setSelected(9);
					break;
				}
			}
		}

		if (solve)
		{
			sudoku.solve();
		}
		sprite.setTexture(sudoku.getRenderTexture().getTexture());
		window.clear(sf::Color::White);
		window.draw(sprite);

		window.display();
	}

	return 0;
}
