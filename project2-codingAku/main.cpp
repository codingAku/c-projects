#include "Commit.h"
#include "Event.h"
#include "Hacker.h"
#include "Desk.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <iomanip>


using namespace std;
struct Compare
{
	bool operator() (const Event& p1, const Event& p2) const
	{
		
		if (p1.highPriority == p2.highPriority) {
				
			
			if (abs(p2.time - p1.time) < 0.00001)
			{
				
				return p1.HackerID > p2.HackerID;

			}
			return p1.time - p2.time > 0.0001;

		}
		return p1.highPriority > p2.highPriority;
	}	
};
struct Compare1
{
	bool operator() (const Hacker& p1, const Hacker& p2) const
	{
		
		if (p2.validCommits == p1.validCommits)
		{
			if (abs(p2.enteringTimeToHoodieQueue - p1.enteringTimeToHoodieQueue) < 0.00001)
			{
				return p1.ID > p2.ID;
			}
			return p1.enteringTimeToHoodieQueue - p2.enteringTimeToHoodieQueue > 0.0001;

		}
		return p1.validCommits < p2.validCommits;

	}
};
int main(int argc, char* argv[])
{
	priority_queue<Event, vector<Event>, Compare> heap;
	queue<Hacker> stickerQueue;
	priority_queue<Hacker, vector<Hacker>, Compare1> hoodieQueue;

	int invalidStickerAttempts = 0;
	int invalidGiftAttempts = 0;
	float avcommit = 0;

	ifstream reader(argv[1]);
	int numberOfHackers;
	reader >> numberOfHackers;
	vector<Hacker> hackers;
	float arrivalTime;
	for (int i = 1; i <= numberOfHackers; i++)
	{
		reader >> arrivalTime;
		Event a(arrivalTime, i, "arrival");
		heap.push(a);
	}

	int numberOfCommits;
	int hackerID;
	int commitLength;
	float commitTime;
	float avline = 0;
	reader >> numberOfCommits;
	for (int i = 0; i < numberOfCommits; i++)
	{
		reader >> hackerID;
		reader >> commitLength;
		reader >> commitTime;
		Event b(commitTime, hackerID, "commit");

		b.commitLength = commitLength;
		avline += commitLength;
		heap.push(b);
	}

	int numberOfQueueEntrance;
	float entranceTime;
	reader >> numberOfQueueEntrance;
	for (int i = 0; i < numberOfQueueEntrance; i++)
	{
		reader >> hackerID;
		reader >> entranceTime;
		Event c(entranceTime, hackerID, "stickerQueueEntranceAttempt");
		heap.push(c);
	}


	int numOfStickerDesks;
	reader >> numOfStickerDesks;
	vector<Desk> stickerDesks;
	float processTime;
	for (int i = 0; i < numOfStickerDesks; i++)
	{
		reader >> processTime;
		Desk a(processTime);
		stickerDesks.push_back(a);
	}

	int numOfHoodieDesks;
	int idOfdesks = 1;
	reader >> numOfHoodieDesks;
	vector<Desk> HoodieDesks;
	float processTimeD;
	for (int i = 0; i < numOfHoodieDesks; i++)
	{
		reader >> processTimeD;
		Desk a(processTimeD);
		a.ID = idOfdesks;
		idOfdesks++;
		HoodieDesks.push_back(a);
	}

	float totalTime = 0;
	float turnaroundTime = 0;
	int maxLenOfS = 0;
	int maxLenOfH = 0;


	while (!heap.empty())
	{


		Event now = heap.top();


		if (heap.size() == 1)
		{
			totalTime = now.time;
		}
		if (now.type == "arrival")
		{
			Hacker k;
			hackers.push_back(k);
			heap.pop();
		}

		Hacker& hacker = hackers[now.HackerID - 1];
		if (now.type == "commit")
		{
			int i = now.HackerID;
			Commit x(now.commitLength);
			hacker.commits->push_back(x);
			if (x.valid)
			{
				hacker.validCommits++;
			}
			heap.pop();
		}

		else if (now.type == "stickerQueueEntranceAttempt")
		{

			if (hacker.numOfStickers == 3)
			{
				invalidGiftAttempts++;
			}
			else if (hacker.validCommits >= 3)
			{
				Event enter(now.time, now.HackerID, "enterStickerQueue");
				heap.push(enter);
			}
			else {
				invalidStickerAttempts++;
			}


			heap.pop();

		}
		else if (now.type == "enterStickerQueue")
		{


			hacker.enteringTimeToStickerQueue = now.time;
			stickerQueue.push(hacker);
			heap.pop();
			bool fal = false;
			for (int i = 0; i < stickerDesks.size(); i++)
			{
				if (stickerDesks[i].validity)
				{

					Event o(now.time, now.HackerID, "getToStickerDesk");
					o.deskID = i + 1;
					stickerQueue.pop();

					heap.push(o);
					fal = true;
					break;
				}


			}
			if (!fal &&(stickerQueue.size() > maxLenOfS)) { maxLenOfS = stickerQueue.size();}


		}

		else if (now.type == "getToStickerDesk")
		{
			hacker.leavingTimeToStickerQueue = now.time;
			hacker.timeSpentinSQueue += now.time - hacker.enteringTimeToStickerQueue;
			heap.pop();
			Desk x = stickerDesks[now.deskID - 1];
			stickerDesks[now.deskID - 1].validity = false;
			Event j((now.time + x.processTime), now.HackerID, "leaveStickerDesk");
			j.deskID = now.deskID;
			heap.push(j);
		}

		else if (now.type == "leaveStickerDesk")
		{
			Desk x = stickerDesks[now.deskID - 1];
			stickerDesks[now.deskID - 1].validity = true;
			hacker.numOfStickers++;
			heap.pop();
			Event j(now.time, now.HackerID, "enterHoodieQueue");
			j.highPriority = 0;
			heap.push(j);
			if (!stickerQueue.empty()) {
				Event  g(now.time, stickerQueue.front().ID, "getToStickerDesk");
				g.highPriority = 0;
				stickerQueue.pop();
				g.deskID = now.deskID;
				heap.push(g);

			}


		}

		else if (now.type == "enterHoodieQueue") {

			hackers[now.HackerID - 1].enteringTimeToHoodieQueue = now.time;
			hoodieQueue.push(hacker);
			bool tru = true;
			heap.pop();
			for (int i = 0; i < HoodieDesks.size(); i++)
			{
				if (HoodieDesks[i].validity)
				{

					Event o(now.time, now.HackerID, "getToHoodieDesk");
					hoodieQueue.pop();
					o.deskID = i + 1;
					tru = false;
					heap.push(o);
					break;
				}
			}
			if (tru && (hoodieQueue.size() > maxLenOfH)) { maxLenOfH = hoodieQueue.size(); }
		}

		else if (now.type == "getToHoodieDesk")
		{

			hacker.leavingTimeOfHoodieQueue = now.time;

			hacker.timeSpentinHQueue += now.time - hacker.enteringTimeToHoodieQueue;
			heap.pop();
			Desk x = HoodieDesks[now.deskID - 1];
			HoodieDesks[now.deskID - 1].validity = false;
			Event j((now.time + x.processTime), now.HackerID, "leaveHoodieDesk");
			j.deskID = now.deskID;
			heap.push(j);
		}

		else if (now.type == "leaveHoodieDesk")
		{
			Desk x = HoodieDesks[now.deskID - 1];
			HoodieDesks[now.deskID - 1].validity = true;
			hacker.numOfHoodies++;
			hackers[now.HackerID - 1].leavingTimeOfHoodieDesk = now.time;
			turnaroundTime += now.time - hacker.enteringTimeToStickerQueue;
			heap.pop();
			if (!hoodieQueue.empty()) {
				Event  g(now.time, hoodieQueue.top().ID, "getToHoodieDesk");
				g.highPriority = 0;
				hoodieQueue.pop();
				g.deskID = now.deskID;
				heap.push(g);

			}
		}

	}






	float number = 0;
	float waitingTimeS = 0;
	float waitingTimeH = 0;
	float minWaitingTime = -1;
	int maxID = 0;
	int minID = -1;
	float maxWaitingTime = -1;

	ofstream writer(argv[2]);
	writer << fixed;
	writer << setprecision(3);



	for (auto a : hackers) {
		if (a.timeSpentinHQueue + a.timeSpentinSQueue - maxWaitingTime > 0.00001) {
			maxWaitingTime = a.timeSpentinHQueue + a.timeSpentinSQueue;
			maxID = a.ID;
		}
		if (a.numOfStickers == 3) {
			minWaitingTime = a.timeSpentinHQueue + a.timeSpentinSQueue;
			minID = a.ID;

		}
		waitingTimeH += a.timeSpentinHQueue;
		waitingTimeS += a.timeSpentinSQueue;

		number += a.numOfHoodies;
	}
	for (auto a : hackers) {
		if (a.timeSpentinHQueue + a.timeSpentinSQueue - minWaitingTime < 0.00001 && a.numOfStickers == 3) {
			if (abs(a.timeSpentinHQueue + a.timeSpentinSQueue - minWaitingTime )< 0.00001) {
				minID = min(minID, a.ID);

			}
			else {
				minWaitingTime = a.timeSpentinHQueue + a.timeSpentinSQueue;
				minID = a.ID;
			}
		}
	}
	writer << maxLenOfS << endl;
	writer << maxLenOfH << endl;
	writer << number / hackers.size() << endl;
	writer << float(waitingTimeS / number) << endl;
	writer << float(waitingTimeH / number) << endl;
	writer << float(numberOfCommits) / numberOfHackers << endl;
	writer << float(avline / numberOfCommits )<< endl;
	writer << float(turnaroundTime / number) << endl;
	writer << invalidStickerAttempts << endl;
	writer << invalidGiftAttempts << endl;
	writer << maxID << " " << maxWaitingTime << endl;
	if (minID == -1) {
		writer << minID << " " << (int)minWaitingTime << endl;
	}
	else { writer << minID << " " << minWaitingTime << endl; }
	writer << totalTime;
	return 0;
}