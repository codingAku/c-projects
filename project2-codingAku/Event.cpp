#include "Event.h"
#include "Commit.h"
#include <string>
#include <iostream>
using namespace std;
 

Event::Event(float time, int hackerID, string type)
{
	this->time = time;
	this->HackerID = hackerID;
	this->type = type;
	

}



