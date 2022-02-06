#pragma once

#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Ball
{
public:
	Ball();
	~Ball();
	void GenerateVelocity();
	sf::Vector2f GetVelocity();
	void Move(float x, float y);
	void Draw(sf::RenderWindow* win);
	void DrawTex(sf::RenderTexture* win);
	void SetPosition(int x, int y);
	sf::Vector2f GetPosition();
	sf::Vector2f GetSize();
	void Reset();
	void Bounce(int a, int b);
	bool DetectCollision(Paddle p);

private:
	sf::CircleShape circleShape;
	sf::Vector2f velocity;
	int maxAxisSpeed;
};

float RandomNumber(float Min, float Max);
