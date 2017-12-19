// Obj File loader
#pragma once

#include "glHeader.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class FileLoader
{
	public:
		FileLoader();
		~FileLoader();

		bool openFile(string path);

		GLfloat getObjectData();

	private:
		vector <ifstream> fileRefrences;

		vector <glm::vec3> verticies;
		vector <glm::vec2> uvs;
		vector <glm::vec3> normals;
};