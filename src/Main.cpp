#include "Platform/Platform.hpp"
#include "Ball.h"
#include "Paddle.h"
#include "Particle.h"
#include "Razshaders.h"
#include <sstream>
#include <string>
#include "ui.h"
#include "Sound.h"

#define MAX_PARTICLES 		2000	//2000
#define NUM_PARTICLES 		250		//250
#define NUM_TRAIL_PARTICLES 5		//5

int winW = 1024; // Window Size
int winH = 768;

enum Gamestate {MENU, PLAYING};
bool singlePlayer = true;

int main()
{
	//Create a window
	sf::RenderWindow window(sf::VideoMode(winW, winH), "RaZ Pong", sf::Style::Close);
	window.setFramerateLimit(50);

	//Initialize Shaders
	if(!InitShaders()) return -1;

	//Initialize Sounds
	if(!InitSounds()) return -1;

	//Creating text and setting it's font and parameters
	InitTextObjects(&window);

	//instantiate objects and set positions
	Ball ball;
	ball.SetPosition((window.getSize().x - ball.GetSize().x) / 2, (window.getSize().y - ball.GetSize().y) / 2);

	Paddle p1, p2;
	p1.SetPosition(window.getSize().x - 40, (window.getSize().y - p1.GetSize().y) / 2);
	p2.SetPosition(40, (window.getSize().y - p2.GetSize().y) / 2);

	Particle particles[MAX_PARTICLES];
	for (int i = 0; i < MAX_PARTICLES; i++)
		particles[i] = Particle();

	//Gamestate
	Gamestate gamestate = MENU;

	// Start a Clock for shaders
	sf::Clock clk;

	//Set FireShader Resolution for MainMenu
	SetFireShaderResolution(512,512);

	// Window Loop-------------------------------------------------
	while (window.isOpen())
	{
		sf::Event event;

		switch (gamestate)
		{
		case MENU:
			/*MENU*/
		if(gameMusic.getStatus()==0) gameMusic.play();

		while (window.pollEvent(event)) //handle event input
		{
			//Close window if x button is pressed
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();

			//Start
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				gameMusic.stop();
				gamestate = PLAYING;
				SetFireShaderResolution(45,45); // Set FireShader Res for Ball
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				gameMusic.stop();
				gamestate = PLAYING;
				SetFireShaderResolution(45,45);
				singlePlayer = false;
			}
		}

		// Set shader parameters
		UpdateShaderParameters(&clk, window.getSize().x/2, (window.getSize().y/2)+350);

		// Draw Rendertextures for post effects (Textwarp)
		rendertexture.clear(sf::Color(255,0,0,15));
		rendertexture.draw(headingmain);
		rendertexture.draw(controls);
		rendertexture.draw(instructions);
		rendertexture.draw(instructions2);
		rendertexture.draw(start1);
		rendertexture.draw(start2);
		rendertexture.display();

		window.clear();
		window.draw(fireball,&fireshader);
		render.setTexture(rendertexture.getTexture()); 	//Set Text to render Sprite
		window.draw(render, &warpshader);				//Draw Render sprite with shader
		window.display();

		break; // END OF MENU


		case PLAYING:
			/*PLAYING*/

		while (window.pollEvent(event)) //handle event input
		{
			//Close window if x button is pressed
			if (event.type == sf::Event::Closed)
				window.close();

			//Back to Main Menu
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				p1.ResetScore();
				p2.ResetScore();
				p1Score.setString("0");
				p2Score.setString("0");
				gamestate = MENU;
				SetFireShaderResolution(512,512); // Set FireShader Res for MainMenu
				singlePlayer = true;
			}
			//Reset
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				ball.SetPosition((window.getSize().x - ball.GetSize().x) / 2, (window.getSize().y - ball.GetSize().x) / 2);
				p1.SetPosition(window.getSize().x - 40, (window.getSize().y - p1.GetSize().y) / 2);
				p2.SetPosition(40, (window.getSize().y - p2.GetSize().y) / 2);
				ball.Reset();
				p1.ResetScore();
				p2.ResetScore();
				p1Score.setString("0");
				p2Score.setString("0");
			}
		}

		//move according to velocity
		ball.Move(ball.GetVelocity().x, ball.GetVelocity().y);

		// Ball Particle Trail
		for (int i = 0; i < NUM_TRAIL_PARTICLES; i++)
			{
				for (int j = 0; j < MAX_PARTICLES; j++)
				{
					if (!particles[j].active)
					{
						particles[j].InitTrail(ball.GetPosition().x + (ball.GetSize().x /2), ball.GetPosition().y + (ball.GetSize().y/2), ball.GetVelocity());
						break;
					}
				}
			}


		//if ball moves out of screen
		if (ball.GetPosition().y <= 0)
		{
			ball.SetPosition(ball.GetPosition().x, 0);
			ball.Bounce(1, -1);
			PlayImpactSound(0);
		}

		if (ball.GetPosition().y + ball.GetSize().y >= window.getSize().y)
		{
			ball.SetPosition(ball.GetPosition().x, window.getSize().y - ball.GetSize().y);
			ball.Bounce(1, -1);
			PlayImpactSound(0);
		}

		//if player2 scores
		if (ball.GetPosition().x <= 40)
		{
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				for (int j = 0; j < MAX_PARTICLES; j++)
				{
					if (!particles[j].active)
					{
						particles[j].Init(ball.GetPosition().x, ball.GetPosition().y);
						break;
					}
				}
			}
			scoreSound.play();
			p2.IncrementScore();
			p2Score.setString(to_string(p2.GetScore()));
			ball.Reset();
			ball.SetPosition((window.getSize().x - ball.GetSize().x) / 2, (window.getSize().y - ball.GetSize().x) / 2);
			p1.SetPosition(window.getSize().x - 40, (window.getSize().y - p1.GetSize().y) / 2);
			p2.SetPosition(40, (window.getSize().y - p2.GetSize().y) / 2);
		}

		//if player1 scores
		if (ball.GetPosition().x + ball.GetSize().x >= window.getSize().x - 20)
		{
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				for (int j = 0; j < MAX_PARTICLES; j++)
				{
					if (!particles[j].active)
					{
						particles[j].Init(ball.GetPosition().x, ball.GetPosition().y);
						break;
					}
				}
			}
			scoreSound.play();
			p1.IncrementScore();
			p1Score.setString(to_string(p1.GetScore()));
			ball.Reset();
			ball.SetPosition((window.getSize().x - ball.GetSize().x) / 2, (window.getSize().y - ball.GetSize().x) / 2);
			p1.SetPosition(window.getSize().x - 40, (window.getSize().y - p1.GetSize().y) / 2);
			p2.SetPosition(40, (window.getSize().y - p2.GetSize().y) / 2);
		}

		//Players movement
		p1.Move(12, window.getSize().y, sf::Keyboard::Up, sf::Keyboard::Down);
		if(!singlePlayer)
			p2.Move(12, window.getSize().y, sf::Keyboard::W, sf::Keyboard::S);
		else
		{
			if(ball.GetPosition().x < window.getSize().x/4)	p2.AiMove(10, window.getSize().y, p2.GetPosition().y>ball.GetPosition().y);
		}
		//Collision Detection
		if(ball.DetectCollision(p1)) PlayImpactSound(1);
		if(ball.DetectCollision(p2)) PlayImpactSound(1);

		// Set shader parameters
		UpdateShaderParameters(&clk, ball.GetPosition().x, ball.GetPosition().y);

		// Draw Text (Pre render to Rendertexture for post effects (Textwarp)
		rendertexture.clear(sf::Color::Transparent);
		rendertexture.draw(p1Score);
		rendertexture.draw(p2Score);
		rendertexture.draw(heading);
		rendertexture.display();

		//clearing back buffer (old image) and drawing the new image
		window.clear();

		// Draw Shader objects
		window.draw(fireball, &fireshader);			   	//Fireball Sprite with shader
		render.setTexture(rendertexture.getTexture()); 	//Set Text to render sprite
		window.draw(render, &warpshader);				//Draw Text sprite with shader

		// Draw Paddles (Pre Render for shaders)
		rendertexture.clear(sf::Color::Transparent);
		p2.Draw(&rendertexture);
		p1.Draw(&rendertexture);
		rendertexture.display();
		render.setTexture(rendertexture.getTexture());	//Set Paddles to render sprite
		window.draw(render, &bloomshader);				//Then draw with shader

		//Draw Ball glow
		window.draw(fireball, renderstate);

		//ball.Draw(&window); // For testing shader positions

		// Draw Particles
		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			particles[i].Update();
			particles[i].Draw(&window);
		}

		window.display();

		break; //END OF PLAYING

		default:
			break;

		} // End of state switch
	} // End of Window Loop
	return 0;
}