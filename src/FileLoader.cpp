#include "FileLoader.h"
#include "defs.h"
#include "./objLoaders/objload.h"
#include <iostream>

FileLoader::FileLoader()
{
	
}

FileLoader::~FileLoader()
{

}

GLfloat FileLoader::getObjectData()
{

	return 0;
}

bool FileLoader::openFile(string path)
{
	Model m = loadModelFromFile(path);

	

	return retVal;
}