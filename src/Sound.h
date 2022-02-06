#pragma once

sf::SoundBuffer impactBuffer[3];
sf::SoundBuffer scoreBuffer;
sf::Sound impactSound;
sf::Sound scoreSound;
sf::Music gameMusic;
bool InitSounds();
void PlayImpactSound(bool paddle);

bool InitSounds(){
	if (!impactBuffer[0].loadFromFile("content/impactWood_heavy_001.ogg"))
    {
		std::cout<<"Couldn't load Sounds";
		return 0;
	}
	if (!impactBuffer[1].loadFromFile("content/impactWood_heavy_002.ogg"))
    {
		std::cout<<"Couldn't load Sounds";
		return 0;
	}
	if (!impactBuffer[2].loadFromFile("content/impactWood_heavy_003.ogg"))
    {
		std::cout<<"Couldn't load Sounds";
		return 0;
	}
	if (!scoreBuffer.loadFromFile("content/magic_impact.wav"))
    {
		std::cout<<"Couldn't load Sounds";
		return 0;
	}
	if (!gameMusic.openFromFile("content/gameloop90bpm.ogg"))
    {
		std::cout<<"Couldn't load Sounds";
		return 0;
	}

	impactSound.setBuffer(impactBuffer[0]);
	scoreSound.setBuffer(scoreBuffer);
	gameMusic.setLoop(true);
	gameMusic.setVolume(80);

	return 1;
}

void PlayImpactSound(bool paddle){
	if(paddle)
	{
		impactSound.setBuffer(impactBuffer[0]);
		impactSound.play();
	}
	else
	{
		impactSound.setBuffer(impactBuffer[1]);
		impactSound.play();
	}
}