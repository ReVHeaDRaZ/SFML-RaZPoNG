#pragma once
#include <sstream>
#include <string>

sf::Font font;
sf::Text p1Score, p2Score, headingmain, heading, controls, instructions, instructions2, start1, start2;

void InitTextObjects(sf::RenderWindow* window);

template <typename T>
//function to convert a non-string variable to a string.
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}


void InitTextObjects(sf::RenderWindow* window)
{
	//Set Styles
	p1Score.setFont(font);
	p1Score.setFillColor(sf::Color::White);
	p1Score.setOutlineColor(sf::Color::White);
	p1Score.setString("0");
	p1Score.setCharacterSize(54);
	p1Score.setStyle(sf::Text::Bold);
	p2Score = p1Score; // copy the shared properties
	heading = p1Score;
	controls = p1Score;
	instructions = p1Score;
	instructions2 = p1Score;
	start1 = p1Score;
	start2 = p1Score;

	//Set Strings
	start1.setString("PReSS SPaCE to STaRT 1P");
	start2.setString("CLiCK MouSe to STaRT 2P");
	controls.setString("CoNTRoLS");
	instructions.setString("Player1-  UP,DOWN");
	instructions2.setString("Player2-  W,S");
	heading.setString("RaZPoNG");
	headingmain = heading;
	headingmain.setCharacterSize(200);

	//Set positions
	p1Score.setPosition(60, 30);
	p2Score.setPosition(window->getSize().x - 80, 30);
	heading.setPosition((window->getSize().x / 2) - 90, 30);
	headingmain.setPosition((window->getSize().x / 2) - 290, 30);
	controls.setPosition(40, (window->getSize().y / 2) - 80);
	instructions.setPosition(40, window->getSize().y / 2);
	instructions2.setPosition(40, window->getSize().y / 2 + 80);
	start1.setPosition((window->getSize().x / 2)- 200, (window->getSize().y) - 100);
	start2.setPosition((window->getSize().x / 2)- 200, (window->getSize().y) - 180);

	//load the font
	//note that this path is relative to the workspace
	if (!font.loadFromFile("content/shredded.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
}