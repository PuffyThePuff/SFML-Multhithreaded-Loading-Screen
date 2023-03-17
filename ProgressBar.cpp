#include "ProgressBar.h"

#include <iostream>

ProgressBar::ProgressBar(String name) : AGameObject(name)
{
	
}

ProgressBar::~ProgressBar()
{

}

void ProgressBar::initialize()
{
	rectBarOutline.setFillColor(sf::Color::Red);
	rectBarOutline.setSize(sf::Vector2f(1920.0f, 20.0f));

	rectBarProgress.setFillColor(sf::Color::Green);
	rectBarProgress.setSize(sf::Vector2f(1.0f, 20.0f));
	rectBarProgress.setScale(0.0f, 1.0f);
	
	sf::Font* font = new sf::Font();
	font->loadFromFile("Assets/Sansation.ttf");
	pressSpaceText.setFont(*font);

	sf::FloatRect textRect = pressSpaceText.getLocalBounds();
	pressSpaceText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);

	pressSpaceText.setPosition(1920 / 2, 0);
	pressSpaceText.setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	pressSpaceText.setOutlineThickness(2.5f);
	pressSpaceText.setCharacterSize(20);
	pressSpaceText.setString("");
}

void ProgressBar::update(sf::Time deltaTime)
{

}

void ProgressBar::processInput(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space && isFilled)
		{
			this->setScale(0, 0);
			rectBarOutline.setScale(0, 0);
			rectBarProgress.setScale(0, 0);
			pressSpaceText.setScale(0, 0);
		}
	}

	if (event.type == sf::Event::MouseButtonPressed && isFilled)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			this->setScale(0, 0);
			rectBarOutline.setScale(0, 0);
			rectBarProgress.setScale(0, 0);
			pressSpaceText.setScale(0, 0);
		}
	}
}

void ProgressBar::draw(sf::RenderWindow* target_window)
{
	target_window->draw(rectBarOutline);
	target_window->draw(rectBarProgress);
	target_window->draw(pressSpaceText);
}

void ProgressBar::setPercentage(float percentage)
{
	if (!isFilled)
	{
		float percent = 1920.0f * percentage;
		//std::cout << percent << std::endl;
		rectBarProgress.setScale(percent, 1.0f);

		if (percent == 1920.0f)
		{
			isFilled = true;
		}

		return;
	}

	if (pressSpaceText.getString().isEmpty() && isFilled)
	{
		pressSpaceText.setString("PRESS SPACE TO CONTINUE");
		std::cout << "string set" << std::endl;
	}
}