#include "LoadingScreen.h"

#include <iostream>

#include "GameObjectManager.h"

const sf::Time LoadingScreen::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

LoadingScreen::LoadingScreen() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Loading Screen", sf::Style::Close)
{
	//initialize vectors here
	for (int i = 0; i < SOUND_THREAD_MAX; i++)
	{
		bufferList.push_back(new sf::SoundBuffer);
	}
	for (int i = 0; i < IMG_THREAD_MAX; i++)
	{
		textureList.push_back(new sf::Texture);
	}

	//threads for images
	for (int i = 0; i < IMG_THREAD_MAX; i++)
	{
		ImageLoaderThread* newThread = new ImageLoaderThread(i, textureList[i]);
		newThread->start();
		imageLoaderList.push_back(newThread);
	}

	//threads for sounds
	for (int i = 0; i < SOUND_THREAD_MAX; i++)
	{
		SoundLoaderThread* newThread = new SoundLoaderThread(i, bufferList[i]);
		newThread->start();
		soundLoaderList.push_back(newThread);
	}
	
	door = new Door("door");
	GameObjectManager::getInstance()->addObject(door);

	//progress bar
	progress_bar = new ProgressBar("ProgressBar");
	GameObjectManager::getInstance()->addObject(progress_bar);

	//FPS counter
	fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	musicPlayer = new MusicPlayer("MusicPlayer", textureList, bufferList);
	GameObjectManager::getInstance()->addObject(musicPlayer);
}

void LoadingScreen::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	window.setFramerateLimit(60);
	float numberDone = 0.0f;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			//still loading assets
			if (numberDone < SOUND_THREAD_MAX + IMG_THREAD_MAX)
			{
				for (int i = 0; i < soundLoaderList.size(); i++)
				{
					SoundLoaderThread* currentThread = soundLoaderList[i];
					if (!currentThread->isRunning)
					{
						numberDone++;
						std::cout << numberDone << std::endl;
						soundLoaderList.erase(soundLoaderList.begin() + i);
						delete currentThread;
						i--;
					}
				}

				for (int i = 0; i < imageLoaderList.size(); i++)
				{
					ImageLoaderThread* currentThread = imageLoaderList[i];
					if (!currentThread->isRunning)
					{
						numberDone++;
						std::cout << numberDone << std::endl;
						imageLoaderList.erase(imageLoaderList.begin() + i);
						delete currentThread;
						i--;
					}
				}
				
				door->percentageDone = (numberDone / (SOUND_THREAD_MAX + IMG_THREAD_MAX) * 100);
				musicPlayer->percentageDone = (numberDone / (SOUND_THREAD_MAX + IMG_THREAD_MAX) * 100);

				progress_bar->setPercentage(numberDone / (SOUND_THREAD_MAX + IMG_THREAD_MAX));
			}

			//loading is done
			else
			{
				//only done once
				if (transitionFlag)
				{
					transitionFlag = false;
				}
			}

			timeSinceLastUpdate -= TIME_PER_FRAME;

			processEvents();
			//update(TIME_PER_FRAME);
			update(elapsedTime);
		}

		render();
	}
}

void LoadingScreen::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            GameObjectManager::getInstance()->processInput(event);
            break;
        }
	}
}

void LoadingScreen::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
}

void LoadingScreen::render()
{
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}
