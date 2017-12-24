// Graphics Debugging
#pragma once

#include "glHeader.h"
#include <iostream> 

class GraphicDebugger
{
public:
	// Setup
	GraphicDebugger();

	// Calculates framecount from last sec
	void showFPS();


private:
	int fps;
	double lastTime;
};

GraphicDebugger::GraphicDebugger()
{
	fps = 0;
	lastTime = glfwGetTime();
}

void GraphicDebugger::showFPS()
{
	double currentTime = glfwGetTime();
	fps++;

	// Its been one second
	if (currentTime - lastTime >= 1.0)
	{
		std::cout << "FPS: " << fps << " - " << "each frame is " << 1000.0/(double)fps << "ms "<<std::endl;
		fps = 0;
		lastTime = currentTime;
	}
}