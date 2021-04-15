#ifndef Event_h
#define Event_h

using namespace std;
#include <string>
#include "Commit.h"

class Event
{
public:
	string type;
	int HackerID;
	int commitLength;
	int deskID;
	int highPriority = 1;
	Event(float time, int hackerID, string type);
	float time;

};


#endif