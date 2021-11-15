#include "myFile.h"

myFile::myFile()
{
	this->aSize = 0;
	this->aPath = "";
	this->aDup = false;
	this->dupPath = "";
}

myFile::myFile(size_t _size, string _path)
{
	this->aSize = _size;
	this->aPath = _path;
	this->aDup = false;
	this->dupPath = "";
}

void myFile::setPath(string _path)
{
	this->aPath = _path;
}

void myFile::setSize(size_t _size)
{
	this->aSize = _size;
}

string myFile::getPath()
{
	return this->aPath;
}

size_t myFile::getSize()
{
	return this->aSize;
}

void myFile::isDuplicate(bool _dup)
{
	this->aDup = _dup;
}

bool myFile::isDuplicate()
{
	return this->aDup;
}

void myFile::setDupPath(string _path)
{
	this->dupPath = _path;
}

string myFile::getDupPath()
{
	return this->dupPath;
}