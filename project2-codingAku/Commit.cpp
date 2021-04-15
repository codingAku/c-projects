#include "Commit.h"
#include <string>
#include <iostream>

using namespace std;

Commit::Commit(int lineNum)
{
	this->lineNumber = lineNum;
	if (lineNum >= 20)
	{
		this->valid = true;
	}
	else
	{
		this->valid = false;
	}
}
