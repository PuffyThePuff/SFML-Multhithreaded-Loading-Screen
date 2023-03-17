#include "ImageLoaderThread.h"
#include <windows.h>

ImageLoaderThread::ImageLoaderThread(int index, sf::Texture* textureToChange)
{
	this->imageIndex = index;
	this->textureToChange = textureToChange;
}

void ImageLoaderThread::run()
{
	isRunning = true;
	Sleep(5000);
	textureToChange->loadFromFile("Assets/Streaming/thumb" + std::to_string(imageIndex) + ".jpg");
	isRunning = false;
}
