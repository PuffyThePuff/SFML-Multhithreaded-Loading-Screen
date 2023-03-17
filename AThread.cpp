#include "AThread.h"

AThread::AThread()
{
	
}

AThread::~AThread()
{
	
}

void AThread::start()
{
	std::thread(&AThread::run, this).detach();
}