#pragma once
#include <SFML/Audio.hpp>
#include "AGameObject.h"

class Door : public AGameObject
{
public:
	Door(String name);
	void initialize() override;
	void update(sf::Time deltaTime) override;
	void processInput(sf::Event event) override;

	float percentageDone = 0.0f;

private:
	bool isAnimating = false;
	bool isLooping = false;

	bool spacePressed = false;

	//flag for changing the texture
	bool textureFlag = false;

	//for waiting to scale the open door
	bool waitTimeFlag = false;
	float timePassed = 0.0f;

	//sf::Sprite doorSprite;

	sf::Texture doorOpenTexture;
	sf::Texture doorClosedTexture;
	
	std::vector<sf::Texture*> doorOpenTextureList;
	std::vector<sf::Texture*> doorClosedTextureList;

	int doorIndexRng = 0;
	
	sf::SoundBuffer doorOpenBuffer;
	sf::Sound doorOpenSound;

	void openDoor(sf::Time deltaTime);
	void loopDoor();
	void cleanUp();
};