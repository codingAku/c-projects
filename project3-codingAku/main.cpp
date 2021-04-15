#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <chrono>
#include <algorithm>

using namespace std;
static int num = 0;
static auto t1 = std::chrono::high_resolution_clock::now();
static auto t2 = std::chrono::high_resolution_clock::now();
struct Edge {
	bool valid = true;
	int to;

	Edge(int to) {
		this->to = to;
			
	}
};
struct Vertex {
	
	int id;
	int inDegree = 0;
	int outDegree = 0;
	int usedEdges = 0;
	vector<Edge*> edgeList;


	Vertex(int id) {
		this->id = id;
		
	}


};


bool checkEuler(vector<Vertex*>* vertexes) {
	for (auto a: *vertexes) {
		if (a->inDegree != a->outDegree) {

			return false;
		}
	}
	return true;
}

void merge(list<int>* one, list<int>* two, list<int>::iterator it) {
	 
	//if (one->empty()) { *one = *two; }else{

	//while (*it != *two->begin()) {
	//	it++;
	//
	
	one->splice(it, *two);
	if(it != one->end()){
	one->erase(it);
	}
	
}

int main(int argc, char const* argv[]) {
	t1 = std::chrono::high_resolution_clock::now();
	//ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	

	ifstream reader(argv[1]);
	ofstream writer(argv[2]);
	int numOfVertex;
	int totalEdges = 0;
	vector<Vertex*> vertexes;
	list<int> one;
	list<int> two;
	reader >> numOfVertex;

	for (int i = 0; i < numOfVertex; i++)
	{

		vertexes.push_back(new Vertex(i));

	}

	int id;
	int numOfedge;
	int to;
	for (int i = 0; i < numOfVertex; i++) {
		reader >> id;
		reader >> numOfedge;
		vertexes[id]->usedEdges = numOfedge;

		for (int i = 0; i < numOfedge; i++) {
			reader >> to;
			vertexes[id]->edgeList.push_back(new Edge(to));
			totalEdges++;
			vertexes[id]->outDegree++;
			vertexes[to]->inDegree++;

		}


	}


	int startingIndex;
	bool stuck = false;
	reader >> startingIndex;
	


	
	if (!checkEuler(&vertexes)) {
		writer << "no path";
		t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	 	cout << duration << endl;
		return 0;
	}
	//t2 = std::chrono::high_resolution_clock::now();
	list<int>::iterator it = one.begin();
	vector<Edge*>::iterator it2;
	//t1 = std::chrono::high_resolution_clock::now();
	while (one.size() != totalEdges+1)
	{
		
		Vertex* x = vertexes[startingIndex];
		two.push_back(startingIndex);
		it2 = x->edgeList.begin();
		if(x->edgeList.size()==0){stuck = true;}
		for (auto a : x->edgeList)
		{
			if(it2 != x->edgeList.begin()){
				it2++;            

			}
			
			
			if (a->valid)
			{
				x->usedEdges--;
				
				a->valid = false;
				stuck = false;
				startingIndex = a->to;
				x->edgeList.erase(it2);
				
				break;
				
			}
			

		}
		


		if (stuck)
		{
			
			merge(&one, &two, it);
			
			it = one.begin();
			two.clear();
			for (auto a : one) {
				it++;
				if (vertexes[a]->usedEdges != 0) {
					it--;
					startingIndex = a;
					break;
				}
			}
			stuck = false;
		}

	}
	


	
	for(auto a: one){
		writer << a << " ";
	}
	t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	 cout << duration << endl;

	return 0;
}