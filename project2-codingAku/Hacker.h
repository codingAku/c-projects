#ifndef Hacker_h
#define Hacker_h

#include "Commit.h"
using namespace std;
#include <vector> 
class Hacker {
	
public:
	int ID;
	int validCommits;
	int numOfHoodies;
	int numOfStickers;
	float enteringTimeToStickerQueue = 0;
	float leavingTimeToStickerQueue = 0;
	float enteringTimeToHoodieQueue = 0;
	float leavingTimeOfHoodieQueue = 0;
	float timeSpentinSQueue = 0;
	float timeSpentinHQueue = 0;
	float leavingTimeOfHoodieDesk = 0;
	float turnaroundTime = 0;
	vector<Commit>* commits;
	Hacker();
	//Hacker(const Hacker& hacker);


};
#endif // !Hacker.h

