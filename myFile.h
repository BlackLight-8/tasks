#pragma once
#include <string>

using namespace std;
class myFile
{
private:
	string dupPath;
	string aPath;
	size_t aSize;
	bool aDup;
public:
	myFile();
	myFile(size_t, string);
	void setPath(string);
	string getPath();
	void setSize(size_t);
	size_t getSize();
	void isDuplicate(bool);
	bool isDuplicate();
	string getDupPath();
	void setDupPath(string);
};

