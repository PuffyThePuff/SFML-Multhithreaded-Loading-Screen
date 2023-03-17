#include "MusicPlayer.h"
#include <iostream>

MusicPlayer::MusicPlayer(String name, std::vector<sf::Texture*> &spriteListPointer, std::vector<sf::SoundBuffer*> &bufferListPointer) : AGameObject(name)
{
	this->textureList = spriteListPointer;
	this->bufferList = bufferListPointer;
}

void MusicPlayer::initialize()
{
	this->sprite = new sf::Sprite();
	//this->sprite->setTexture(*this->textureList[0]);

	//this->musicPlaying.setBuffer(*this->bufferList[0]);
	//this->musicPlaying.play();
}

void MusicPlayer::update(sf::Time deltaTime)
{
	if (fadeInFlag)
	{
		fadeIn();
	}
}

void MusicPlayer::processInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && this->keyFlag == false)
	{
		this->keyFlag = true;
		if (event.key.code == sf::Keyboard::A)
		{
			shiftLeft();
		}
		if (event.key.code == sf::Keyboard::D)
		{
			shiftRight();
		}
		if (event.key.code == sf::Keyboard::Space && percentageDone >= 100.0f && !spacePressed) 
		{
			std::cout << "fading in" << std::endl;
			fadeInFlag = true;
			textureFlag = true;
			spacePressed = true;
		}
	}

	if (event.type == sf::Event::KeyReleased && this->keyFlag == true)
	{
		this->keyFlag = false;
	}

	if (event.type == sf::Event::MouseButtonPressed && percentageDone >= 100.0f)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
		}
	}
}

void MusicPlayer::shiftLeft()
{
	this->index--;
	if (index < 0)
	{
		this->index = this->textureList.size() - 1;
	}

	this->sprite->setTexture(*this->textureList[this->index]);

	this->musicPlaying.setBuffer(*this->bufferList[this->index]);
	this->musicPlaying.play();
}

void MusicPlayer::shiftRight()
{
	this->index++;
	if (index > this->textureList.size() - 1)
	{
		this->index = 0;
	}

	this->sprite->setTexture(*this->textureList[this->index]);

	this->musicPlaying.setBuffer(*this->bufferList[this->index]);
	this->musicPlaying.play();
}

void MusicPlayer::fadeIn()
{
	sf::Color color = this->sprite->getColor();
	color.a += 1;
	this->sprite->setColor(color);	  

	if (textureFlag == true)
	{
		this->sprite->setTexture(*this->textureList[0]);

		sf::Vector2u centerOfSprite = this->sprite->getTexture()->getSize();

		this->sprite->setOrigin(centerOfSprite.x / 2, centerOfSprite.y / 2);

		this->setPosition(960, 540);

		textureFlag = false;
	}

	if (color.a >= 255)
	{
		fadeInFlag = false;
		
		this->sprite->setTexture(*this->textureList[0]);
		this->musicPlaying.setBuffer(*this->bufferList[0]);
		this->musicPlaying.play();
	}
}
