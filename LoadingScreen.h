#pragma once
#include <SFML/Graphics.hpp>
#include "ProgressBar.h"
#include "ImageLoaderThread.h"
#include "SoundLoaderThread.h"
#include "Door.h"
#include "FPSCounter.h"
#include "MusicPlayer.h"
#include <SFML/Audio.hpp>

using namespace std;
class LoadingScreen : private sf::NonCopyable
{
public:
	static const sf::Time TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	LoadingScreen();
	void run();
	
	//sound list
	std::vector<sf::SoundBuffer*> bufferList;

	//image list
	std::vector<sf::Texture*> textureList;

private:
	sf::RenderWindow window;

	ProgressBar* progress_bar;
	Door* door;
	FPSCounter* fpsCounter;
	MusicPlayer* musicPlayer;

	static const int THREAD_MAX = 3;		//UNUSED - change to equal amount of images and songs to display and play
	static const int IMG_THREAD_MAX = 3;
	static const int SOUND_THREAD_MAX = 3;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

	std::vector<ImageLoaderThread*> imageLoaderList;
	std::vector<SoundLoaderThread*> soundLoaderList;

	bool transitionFlag = true;
	bool doTransition = false;
};

