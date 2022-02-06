#include "Particle.h"
#include "Ball.h"

Particle::Particle()
{
	active = false;
	circleShape.setRadius(RandomNumber(1, 4));
}

Particle::~Particle()
{}

void Particle::Init(float x, float y)
{
	active = true;
	this->lifetime = rand();
	circleShape.setPosition(x, y);
	circleShape.setFillColor(sf::Color(255, lifetime / 2, lifetime / 2, this->lifetime));
	velocity = sf::Vector2f(RandomNumber(1.f, 10.f) - 5, RandomNumber(1.f, 10.f) - 5);
}

void Particle::InitTrail(float x, float y, sf::Vector2f ballVelocity)
{
	active = true;
	this->lifetime = rand();
	circleShape.setPosition(x, y);
	circleShape.setFillColor(sf::Color(255, lifetime / 2, lifetime / 2, this->lifetime));
	if(ballVelocity.y < 1.f && ballVelocity.y > -1.f)
		ballVelocity.y = RandomNumber(1.f,10.f) -5;
	velocity = sf::Vector2f(ballVelocity.x * RandomNumber(0.5, 2.0) *-0.3, ballVelocity.y * RandomNumber(0.5, 2.0) *-0.3);
}

void Particle::Update()
{
	if (this->lifetime > 5 && active == true)
	{
		circleShape.move(velocity);
		circleShape.setFillColor(sf::Color(255, lifetime / 2, lifetime / 2, this->lifetime));
		this->lifetime--;
	}
	else
	{
		active = false;
	}
}

void Particle::Draw(sf::RenderWindow* win)
{
	if (active)
	{
		win->draw(circleShape);
		if(circleShape.getPosition().x < 0 || circleShape.getPosition().x+10 > win->getSize().x)
			active=false;
		if(circleShape.getPosition().y < 0 || circleShape.getPosition().y+10 > win->getSize().y)
			active=false;
	}
}