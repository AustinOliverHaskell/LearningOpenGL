#include "./h/FileLoader.h"
#include "./h/shapeData.h"
#include "./h/Model.h"


using namespace glm;

Model::Model(Model &m)
{
	shapeData = m.getShapeData();
	colorData = m.getColorData();
	shader    = m.getShader();
	faceCount = m.getFaceCount();
}

Model::Model(GLuint s, std::string path, bool tessalate)
{
	shader = s;

	FileLoader * file = new FileLoader();

	if (!file->openFile(path, tessalate))
	{
		std::cout << "Filed to load file: " << path << std::endl;
	}

	faceCount = file->getFaceCount();

	shapeData = file->getObjectData();

	normalData = file->getNormals();

	GLfloat * colors = new GLfloat[faceCount * sizeof(vec3) * 3];

	// Define color data for the object
	for (uint i = 0; i < faceCount * sizeof(vec3); i++)
	{
		colors[i  ] = 0.5;
		colors[i+1] = 0.5;
		colors[i+2] = 0.8;
	}

	colorData = colors;

	cout << faceCount << endl;
}

Model::~Model()
{
	if (setupComplete)
	{
		glDeleteBuffers(1, &verticies);
		glDeleteBuffers(1, &colors);
	}
}

GLfloat * Model::getShapeData()
{
	return shapeData;
}

GLfloat * Model::getColorData()
{
	return colorData;
}

GLuint Model::getShader()
{
	return shader;
}

uint Model::getFaceCount()
{
	return faceCount;
}

void Model::setShader(GLuint s)
{
	shader = s;
}

void Model::setVertexData(GLfloat * data)
{
	shapeData = data;
}

void Model::setColorData(GLfloat * data)
{
	colorData = data;
}

void Model::initBuffers()
{
	glGenBuffers(1, &verticies);
	glBindBuffer(GL_ARRAY_BUFFER, verticies);
	glBufferData(GL_ARRAY_BUFFER, faceCount * sizeof(vec3) * 3, shapeData, GL_STATIC_DRAW);

	glGenBuffers(1, &colors);
	glBindBuffer(GL_ARRAY_BUFFER, colors);
	glBufferData(GL_ARRAY_BUFFER, faceCount * sizeof(vec3) * 3, colorData, GL_STATIC_DRAW);

	glGenBuffers(1, &normals);
	glBindBuffer(GL_ARRAY_BUFFER, normals);
	glBufferData(GL_ARRAY_BUFFER, faceCount * sizeof(vec3) * 3, normalData, GL_STATIC_DRAW);

	setupComplete = true;
}

void Model::draw()
{
	if (setupComplete)
	{
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, verticies); 
		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,  0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
 		glBindBuffer(GL_ARRAY_BUFFER, normals);
 		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, sizeof(vec3)*faceCount*3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}

void Model::printNormals()
{
	
}