#include "Ball.h"

Ball::Ball()
{
	maxAxisSpeed = 12;
	circleShape.setRadius(20);
	circleShape.setFillColor(sf::Color::White);
	GenerateVelocity();
}

float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min));
}

void Ball::GenerateVelocity()
{
	float x, y;

	//generate horizontal velocity
	x = RandomNumber(1.5, 7) - RandomNumber(1.5, 7);

	//if horizontal velocity is too low renerate another one
	if (abs(x) < 1)
	{
		GenerateVelocity();
		return;
	}
	//generate vertical velocity
	y = RandomNumber(1.5, 7) - RandomNumber(1.5, 7);
	velocity = sf::Vector2f(x, y);
	float magnitude = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	velocity.x = velocity.x / magnitude;
	velocity.y = velocity.y / magnitude;
	velocity.x = velocity.x * maxAxisSpeed;
	velocity.y = velocity.y * maxAxisSpeed;
}

Ball::~Ball()
{
}

void Ball::Move(float x, float y)
{
	circleShape.move(x, y);
}

void Ball::Draw(sf::RenderWindow* win)
{
	win->draw(circleShape);
}

void Ball::DrawTex(sf::RenderTexture* win)
{
	win->draw(circleShape);
}

void Ball::SetPosition(int x, int y)
{
	circleShape.setPosition(x, y);
}

sf::Vector2f Ball::GetSize()
{
	return sf::Vector2f(circleShape.getLocalBounds().width, circleShape.getLocalBounds().height);
}

sf::Vector2f Ball::GetVelocity()
{
	return velocity;
}

sf::Vector2f Ball::GetPosition()
{
	return circleShape.getPosition();
}

void Ball::Reset()
{
	GenerateVelocity();
}

void Ball::Bounce(int a, int b)
{
	velocity = sf::Vector2f(velocity.x * a, velocity.y * b);
}

bool Ball::DetectCollision(Paddle p)
{
	if (GetPosition().y > p.GetPosition().y + p.GetSize().y 										// NO COLLSION
		|| GetPosition().y + GetSize().y < p.GetPosition().y
		|| GetPosition().x > p.GetPosition().x + p.GetSize().x
		|| GetPosition().x + GetSize().x < p.GetPosition().x)
	{
		return false;
	}
	else
	{
		if (GetPosition().y + (GetSize().y / 2) > p.GetPosition().y + ((p.GetSize().y / 4) * 3))	// Bottom of paddle
		{
			Bounce(-1, 1);
			if (velocity.y < 0.5 && velocity.y > -0.5)
				velocity.y++;
			velocity.y *= velocity.y * 2;
		}
		else if (GetPosition().y + (GetSize().y / 2) < p.GetPosition().y + (p.GetSize().y / 4))		//Top of paddle
		{
			Bounce(-1, 1);
			if (velocity.y < 0.5 && velocity.y > -0.5)
				velocity.y++;
			velocity.y *= velocity.y * -2;
		}
		else																						//Middle of paddle
			Bounce(-1, 1);
	}
	float magnitude = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	velocity.y = velocity.y / magnitude;
	velocity.y = velocity.y * maxAxisSpeed;
	return true;
}