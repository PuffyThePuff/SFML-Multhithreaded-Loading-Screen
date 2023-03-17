#pragma once
#include <SFML/Audio.hpp>
#include "AThread.h"

class SoundLoaderThread : public AThread
{
public:
	SoundLoaderThread(int index, sf::SoundBuffer* bufferToChange);

	bool isRunning = false;

private:
	int bufferIndex;
	sf::SoundBuffer* bufferToChange;

	void run() override;
};