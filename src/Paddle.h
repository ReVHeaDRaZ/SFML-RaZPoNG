#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
public:
	Paddle();
	~Paddle();
	void Move(float y, unsigned int windowHeight, sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown);
	void AiMove(float y, unsigned int windowHeight, bool UpIs1DownIs0);
	void Draw(sf::RenderTarget* win);
	void SetPosition(int x, int y);
	int GetScore();
	void ResetScore();
	void IncrementScore();
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();

private:
	sf::RectangleShape rectShape;
	int score;
};
