#pragma once
#include <SFML/Graphics/Texture.hpp>
#include "AThread.h"

class ImageLoaderThread : public AThread
{
public:
	ImageLoaderThread(int index, sf::Texture* textureToChange);

	bool isRunning = false;

private:
	int imageIndex;
	sf::Texture* textureToChange;

	void run() override;
};