#include "SoundLoaderThread.h"
#include <windows.h>

SoundLoaderThread::SoundLoaderThread(int index, sf::SoundBuffer* bufferToChange)
{
	this->bufferIndex = index;
	this->bufferToChange = bufferToChange;
}

void SoundLoaderThread::run()
{
	isRunning = true;
	Sleep(5000);
	this->bufferToChange->loadFromFile("Assets/Streaming/song" + std::to_string(bufferIndex) + ".wav");
	isRunning = false;
}