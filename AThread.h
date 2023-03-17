#pragma once
#include <thread>

class AThread
{
public:
	AThread();
	~AThread();

	void start();

protected:
	virtual void run() = 0;
};