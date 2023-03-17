#include "Door.h"

#include "LoadingScreen.h"

#include <iostream>

Door::Door(String name) : AGameObject(name)
{
	
}

void Door::initialize()
{
	this->sprite = new sf::Sprite();
	
	//doorOpenTexture.loadFromFile("Assets/OakDoorOpen.png");
	//doorClosedTexture.loadFromFile("Assets/OakDoorClosed.png");

	for (int i = 0; i < 5; i++)
	{
		sf::Texture* doorOpenTexture = new sf::Texture();
		doorOpenTextureList.push_back(doorOpenTexture);
		doorOpenTexture->loadFromFile("Assets/DoorOpen" + to_string(i) + ".png");

		sf::Texture* doorClosedTexture = new sf::Texture();
		doorClosedTextureList.push_back(doorClosedTexture);
		doorClosedTexture->loadFromFile("Assets/DoorClosed" + to_string(i) + ".png");
	}

	//doorOpenTexture = *doorOpenTextureList[0];
	//doorClosedTexture = *doorClosedTextureList[0];

	this->sprite->setTexture(*doorClosedTextureList[0]);

	sf::Vector2u centerOfSprite = this->sprite->getTexture()->getSize();

	this->sprite->setOrigin(centerOfSprite.x / 2, centerOfSprite.y / 2);

	this->setPosition(960, 540);
	this->setScale(0.5f, 0.5f);
	
	doorOpenBuffer.loadFromFile("Assets/doorOpen.wav");
	doorOpenSound.setBuffer(doorOpenBuffer);
}

void Door::processInput(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonPressed && !isAnimating && !isLooping)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			isAnimating = true;
		}
	}

	if (event.type == sf::Event::KeyPressed && !isAnimating && !isLooping)
	{
		if (event.key.code == sf::Keyboard::Space && percentageDone >= 100.0f && !spacePressed)
		{
			isAnimating = true;
			spacePressed = true;
		}
	}
}

void Door::update(sf::Time deltaTime)
{
	//std::cout << percentageDone << std::endl;

	if (isAnimating)
	{
		//std::cout << "open" << std::endl;
		openDoor(deltaTime);
	}
	if (isLooping)
	{
		//std::cout << "loop" << std::endl;
		loopDoor();
	}
}

//sets the sprite and gradually scales it
void Door::openDoor(sf::Time deltaTime)
{
	if (!waitTimeFlag)
	{
		if (!textureFlag)
		{
			doorOpenSound.play();
			textureFlag = true;
			this->sprite->setTexture(*doorOpenTextureList[doorIndexRng]);
		}

		timePassed += deltaTime.asSeconds();
		if (timePassed >= 0.75f)
		{
			timePassed = 0.0f;
			waitTimeFlag = true;
		}
		return;
	}

	if (!textureFlag)
	{
		doorOpenSound.play();
		textureFlag = true;
		this->sprite->setTexture(*doorOpenTextureList[doorIndexRng]);
	}
	
	sf::Color color = this->sprite->getColor();
	color.a -= 1;

	if (color.a == 0)
	{
		this->sprite->setColor(color);
		isAnimating = false;

		if (!spacePressed)
		{
			isLooping = true;
		}
		else
		{
			//clean up
			cleanUp();
		}

		this->sprite->setTexture(*doorClosedTextureList[doorIndexRng]);
		return;
	}

	this->sprite->setColor(color);

	this->setScale(this->scaleX + 0.02f, this->scaleY + 0.02f);
}

//loop it back to the beginning;
void Door::loopDoor()
{
	waitTimeFlag = false;

	if (textureFlag)
	{
		textureFlag = false;
		doorIndexRng = std::rand() % 4 + 0;
		this->sprite->setTexture(*doorClosedTextureList[doorIndexRng]);
	}

	this->setScale(0.5f, 0.5f);

	sf::Color color = this->sprite->getColor();
	color.a += 1;

	if (color.a == 255)
	{
		this->sprite->setColor(color);
		isLooping = false;
		//doorOpenTexture = *doorOpenTextureList[doorIndexRng];
		return;
	}
	
	this->sprite->setColor(color);
}

void Door::cleanUp()
{
	this->sprite->setColor(sf::Color::Transparent);
	this->sprite->setScale(0, 0);
	this->doorOpenSound.setVolume(0);
}
