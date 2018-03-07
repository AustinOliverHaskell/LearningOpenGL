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
		Model(GLuint s, std::string path, bool tessalate = false);

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

		// ----- Setters -----
		void setColor(float r, float g, float b);
		// -------------------

		// ----- Draw -----
		void draw(Controls * controls, mat4 m);
		void initBuffers(GLuint matID, GLuint viewID, GLuint modelID);
		// ----------------

		// ----- Other -----
		std::string toString();
		void printNormals();
		// -----------------

	private:
		// Shader to use on this object
		GLuint shader;

		GLfloat * shapeData;
		GLfloat * colorData;
		GLfloat * normalData;

		GLuint verticies;
		GLuint colors;
		GLuint normals;

		GLuint MatrixID;
		GLuint ViewMatrixID;
		GLuint ModelMatrixID;

		bool setupComplete;

		uint faceCount;
};