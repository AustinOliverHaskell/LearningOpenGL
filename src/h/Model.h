#pragma once

#include "glHeader.h"
#include <iostream>

using namespace glm;


/**
	This class just handles the model transformations and also holds its
	 own model data. Knows which shader to use on itslef
*/
class Model
{
	public:
		Model(Model &m);
		Model(GLuint s, std::string path);

		~Model();

		// ----- Setters -----
		void setShader(GLuint s);
		void setVertexData(GLfloat * data);
		void setColorData(GLfloat * data);
		// -------------------

		// ----- Getters -----
		GLuint getShader();
		GLfloat * getShapeData();
		GLfloat * getColorData();
		uint getFaceCount();
		// -------------------

		// ----- Draw -----
		void draw();
		void initBuffers();
		// ----------------

		// ----- Other -----
		std::string toString();
		// -----------------

	private:
		// Shader to use on this object
		GLuint shader;

		GLfloat * shapeData;
		GLfloat * colorData;

		GLuint verticies;
		GLuint colors;

		bool setupComplete;

		uint faceCount;
};