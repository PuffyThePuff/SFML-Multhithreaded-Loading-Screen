#pragma once
#include "AGameObject.h"

class ProgressBar : public AGameObject
{
public:
	ProgressBar(String name);
	~ProgressBar();
	void initialize() override;
	void update(sf::Time deltaTime) override;
	void processInput(sf::Event event) override;

	//override draw function cause this doesn't have sprites
	void draw(sf::RenderWindow* targetWindow) override;

	void setPercentage(float percentage);

private:
	sf::RectangleShape rectBarOutline;
	sf::RectangleShape rectBarProgress;

	sf::Text pressSpaceText;

	bool isFilled = false;
};