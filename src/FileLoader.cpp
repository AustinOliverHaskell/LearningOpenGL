#include "./h/FileLoader.h"
#include "./h/defs.h"
#include "./objLoaders/objload.h"
#include <iostream>
#include <fstream>

using namespace std;

FileLoader::FileLoader()
{
	vertexCount = 0;
	faceCount = 0;
}

FileLoader::~FileLoader()
{
	delete vertexData;
}

GLfloat * FileLoader::getObjectData()
{
	return vertexData;
}

uint FileLoader::getFaceCount()
{
	return faceCount;
}

uint FileLoader::getVertexCount()
{
	return vertexCount;
}

bool FileLoader::openFile(string path)
{
	bool retVal = true;

	ifstream in;

	in.open(path);

	// Check if the file is open
	retVal = in.is_open();

	if (!retVal)
	{
		return retVal;
	}

	// Load the file
	obj::ObjModel model = obj::parseObjModel(in);

	// Make sure that the model is in triangle form
	tesselateObjModel(model);


	// Just get the first group
	auto it = model.faces.cbegin();

	faceCount = it->second.first.size() / 3;

	vector <GLfloat> temp;

	for (auto x = it->second.first.begin(); x != it->second.first.end(); ++x)
	{
		int pos = (x->v)*3;

		temp.push_back(model.vertex[pos]);
		temp.push_back(model.vertex[pos+1]);
		temp.push_back(model.vertex[pos+2]);
	}

	vertexData  = new GLfloat[temp.size()];
	vertexCount = temp.size();

	for (uint i = 0; i < temp.size(); i++)
	{
		vertexData[i] = temp[i];
	}

	return retVal;
}