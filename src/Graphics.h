#pragma once
#include <string>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "glHeader.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define TIME_WINDOW 10;

class Graphics
{
	public:
		Graphics(std::string name);
		~Graphics();

		void openWindow();

		void setupGL();

		void drawTriangle();
	private:
		GLFWwindow* window;
		std::string windowName;

		GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
};