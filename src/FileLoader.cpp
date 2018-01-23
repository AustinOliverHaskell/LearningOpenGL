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

GLfloat * FileLoader::getNormals()
{
	return &normals[0];
}

uint FileLoader::getFaceCount()
{
	return faceCount;
}

uint FileLoader::getVertexCount()
{
	return vertexCount;
}

uint FileLoader::getNormalCount()
{
	return normals.size();

}

bool FileLoader::openFile(string path, bool tesselate)
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

	// Object isnt in triangle form
	if (tesselate)
	{
		// Make sure that the model is in triangle form
		tesselateObjModel(model);
	}


	// Just get the start iterator for the faces map
	auto it = model.faces.cbegin();

	// Second in this context refers to the value of the map
	// second.first refers to the first item of the contaned tuple
	faceCount = it->second.first.size() / 3;

	vector <GLfloat> temp;

	//cout << "FaceList" << endl;

	// second.first is refering to the underlying vector of facepoints 
	for (auto x = it->second.first.begin(); x != it->second.first.end(); ++x)
	{
		// Get the vertex info and then multiply it by 3 to offset it
		//  around the x y and z points
		int pos = (x->v)*3;

		//cout << pos/3+1 << " - ";

		// Push back each point that is listed in the face description
		temp.push_back(model.vertex[pos]);
		temp.push_back(model.vertex[pos+1]);
		temp.push_back(model.vertex[pos+2]);

		// If the file did not get tessalated, because this is a crash otherwise
		if (!tesselate)
		{
			int norPos = (x->n)*3;

			normals.push_back(model.normal[norPos]);
			normals.push_back(model.normal[norPos+1]);
			normals.push_back(model.normal[norPos+2]);
		}
	}

	vertexData  = new GLfloat[temp.size()];
	vertexCount = temp.size();

	for (uint i = 0; i < temp.size(); i++)
	{
		vertexData[i] = temp[i];
	}



	return retVal;
}