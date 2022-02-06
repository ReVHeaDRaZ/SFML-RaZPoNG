#pragma once

class Particle
{
public:
	bool active;
	float x, y;
	Particle();
	~Particle();
	void Init(float x, float y);
	void InitTrail(float x, float y, sf::Vector2f ballVelocity);
	void Update();
	void Draw(sf::RenderWindow* win);

private:
	sf::CircleShape circleShape;
	sf::Vector2f velocity;
	uint8_t lifetime;
};