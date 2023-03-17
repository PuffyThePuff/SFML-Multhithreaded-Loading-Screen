#pragma once
#include <SFML/Audio.hpp>
#include "AGameObject.h"

class MusicPlayer : public AGameObject
{
public:
	MusicPlayer(String name, std::vector<sf::Texture*> &spriteListPointer, std::vector<sf::SoundBuffer*> &bufferListPointer);
	void initialize() override;
	void update(sf::Time deltaTime) override;
	void processInput(sf::Event event) override;

	float percentageDone = 0.0f;

private:
	int index = 0;

	//flag to make sure there's only one key input that gets processed
	bool keyFlag = false;

	bool fadeInFlag = false;

	bool textureFlag = false;

	bool spacePressed = false;

	std::vector<sf::Texture*> textureList;
	std::vector<sf::SoundBuffer*> bufferList;

	sf::Sound musicPlaying;

	void shiftLeft();
	void shiftRight();

	void fadeIn();
};