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

		uint getFaceCount();
		uint getVertexCount();
		uint getNormalCount();

		GLfloat * getObjectData();
		GLfloat * getNormals();

	private:
		vector <ifstream> fileRefrences;

		vector <glm::vec3> verticies;
		vector <glm::vec2> uvs;
		vector <float> normals;

		GLfloat * vertexData;
		GLfloat * uvsData;

		uint vertexCount; 
		uint faceCount;
};