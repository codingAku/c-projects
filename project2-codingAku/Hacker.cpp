#include "Hacker.h"
#include "Commit.h"
using namespace std;
#include <vector>
#include <iterator>

static int id = 1;
Hacker::Hacker()
{
	this->commits = new vector<Commit>();
	this->ID = id++;
	this->validCommits = 0;
	this->numOfHoodies = 0;
	this->numOfStickers = 0;
	this->enteringTimeToStickerQueue = 0;
	this->leavingTimeToStickerQueue = 0;
	this->enteringTimeToHoodieQueue = 0;
	this->leavingTimeOfHoodieQueue = 0;
	this->timeSpentinSQueue = 0;
	this->timeSpentinHQueue = 0;
	this->leavingTimeOfHoodieDesk = 0;
	this->turnaroundTime = 0;
	

	
}
//Hacker::~Hacker() {
//	delete[] this->commits;
//}

	//Hacker::Hacker(const Hacker& hacker) {

	//for (int i = 0; i < this->commits->size(); i++) {
	//	hacker.commits[i] = this->commits[i];
	//}
			
		
	








