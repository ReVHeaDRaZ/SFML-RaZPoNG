#include "Paddle.h"

Paddle::Paddle()
{
	rectShape.setSize(sf::Vector2f(15, 150));
	rectShape.setFillColor(sf::Color(200, 200, 200, 200));
	score = 0;
}

Paddle::~Paddle()
{
}

void Paddle::IncrementScore()
{
	score++;
}

int Paddle::GetScore()
{
	return score;
}

void Paddle::ResetScore()
{
	score=0;
}

void Paddle::Move(float y, unsigned int windowHeight, sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown)
{
	if (sf::Keyboard::isKeyPressed(keyUp))
	{
		if (GetPosition().y <= 0)
		{
			return;
		}
		rectShape.move(0, -y);
	}
	else if (sf::Keyboard::isKeyPressed(keyDown))
	{
		if (GetPosition().y + GetSize().y >= windowHeight)
		{
			return;
		}
		rectShape.move(0, y);
	}
}

void Paddle::AiMove(float y, unsigned int windowHeight, bool UpIs1DownIs0)
{
	if (UpIs1DownIs0) 		//UP
	{
		if (GetPosition().y <= 0)
		{
			return;
		}
		rectShape.move(0, -y);
	}
	else if (!UpIs1DownIs0)	//DOWN
	{
		if (GetPosition().y + GetSize().y >= windowHeight)
		{
			return;
		}
		rectShape.move(0, y);
	}
}

void Paddle::Draw(sf::RenderTarget* win)
{
	win->draw(rectShape);
}

void Paddle::SetPosition(int x, int y)
{
	rectShape.setPosition(x, y);
}

sf::Vector2f Paddle::GetSize()
{
	return sf::Vector2f(rectShape.getLocalBounds().width, rectShape.getLocalBounds().height);
}

sf::Vector2f Paddle::GetPosition()
{
	return rectShape.getPosition();
}