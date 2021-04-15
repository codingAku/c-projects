#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <limits>
#include <chrono>



using namespace std;



typedef pair<int, int> Edge;

class Vertex {
public:
    int id;
    unordered_map<int, Edge> adjacencyMap;

    Vertex(int id = -1) {
        this->id = id;
    }

    void addEdge(int id, int capacity, int cost) {
        Edge x(capacity, cost);
        adjacencyMap[id] = x;
    }

};


class AugmentingPath {
public:
    int amount;
    int cost;
    stack <int> path;

    AugmentingPath() {
        this->amount = -1;
    }

    AugmentingPath(int amount, stack<int> path) {
        this->amount = amount;
        this->path = path;
    }
};
int k;
void fordFulkerson(vector<Vertex*>& residualGraph, int* cost) {

    for (auto& a : residualGraph) {
        
        if (a->id >= k) {
            continue;
        }
        int cost2 = a->adjacencyMap[a->id + k].second;
        *cost += cost2;
        residualGraph[a->id]->adjacencyMap.erase(a->id + k);
        residualGraph[a->id + k]->adjacencyMap[a->id] = Edge(1, -1 * cost2);
    }

}

deque<int> trace(vector<int>& pre, int v) {
    stack<int> keep;
    vector<bool> bo(600, false);
    deque<int> cycle;

    while (!bo[v]) {
        keep.push(v);
        bo[v] = true;
        v = pre[v];

    }

    cycle.push_back(v);

    while (keep.top() != v) {
        cycle.push_back(keep.top());
        keep.pop();
    }
    cycle.push_back(v);
    return cycle;

}

bool visited[1000], on_stack[1000];
int n;
bool detect_cycle(vector<int>& pre, deque<int>& cyc)
{
    vector<int> vec;
    fill(on_stack, on_stack + n, false);
    fill(visited, visited + n, false);
    for (int i = 0; i < n; ++i)
        if (!visited[i])
        {

            for (int j = i; j != -1; j = pre[j]) {
                if (!visited[j])
                {
                    visited[j] = true;
                    vec.push_back(j);
                    on_stack[j] = true;
                }
                else
                {
                    if (on_stack[j]) {
                        cyc = trace(pre, j);
                        return true;
                    }
                    break;
                }
            }
            for (int j : vec)
                on_stack[j] = false;
            vec.clear();
        }
    return false;

}

bool SPFA(vector<Vertex*>& graph,  deque<int>& trac) {
    
    deque<Vertex*> q;
    vector<bool>qcheck;
    vector<int> dis;
    vector<int> pre;

    for(int i=0; i<graph.size(); i++){
        q.push_back(graph[i]);
        dis.push_back(0);
        pre.push_back(-1);
        qcheck.push_back(true);
    }
    

    int iter = 0;
  

    while (!q.empty()) {
        Vertex*u = q.front();
        q.pop_front();
        qcheck[u->id] = false;
        for (auto& b : u->adjacencyMap) {
            if (dis[u->id] + b.second.second < dis[b.first]) {

                pre[b.first] = u->id;
                dis[b.first] = dis[u->id] + b.second.second;
                iter++;
                if (iter == graph.size()) {
                    iter = 0;
                    if (detect_cycle(pre, trac)) {

                        return true;
                    }
                }
                if (!qcheck[b.first]) {
                    q.push_back(graph[b.first]);
                    qcheck[b.first] = true;
                }

            }
        }

    }
   
    if (detect_cycle(pre, trac)) {
        return true;
    }
    
    return false;


}


void updateGraph(vector<Vertex*>& graph, deque<int>& trace, int* cost) {

    while (trace.size() != 1) {
        int from = trace.front();
        trace.pop_front();
        int to = trace.front();
        *cost += graph[from]->adjacencyMap[to].second;

        int cost2 = graph[from]->adjacencyMap[to].second;
        graph[from]->adjacencyMap.erase(to);
        graph[to]->adjacencyMap[from] = Edge(1, -1 * cost2);

    }
    trace.pop_back();

}



int main(int argc, char* argv[]) {


    ifstream reader(argv[1]);
    ofstream writer(argv[2]);
    int numberOfMatrices, cost, vertex, total;



    reader >> numberOfMatrices;

    for (int i = 0; i < numberOfMatrices; i++) {
        reader >> vertex;
        n = vertex * 2;
        k = vertex;
        vector<Vertex*> graph;
        deque<int> trace;
        int cost2 = 0;



        for (int i = 0; i < vertex * 2; i++) {
            graph.push_back(new Vertex(i));

        }

        for (int i = 0; i < vertex; i++) {
            for (int k = 0; k < vertex; k++) {
                reader >> cost;
                graph[i]->addEdge(k + vertex, 1, -1 * cost);
            }
        }
        fordFulkerson(graph, &cost2);
        

        unordered_map<int, int> pre;
        bool cycle = true;
        while (cycle) {
    
            cycle = SPFA(graph, trace);
            
            if (cycle) {
                updateGraph(graph, trace, &cost2);
            }else{
                break;
            }

        }   
         writer << -1 * cost2 << endl;


    }
    
    return 0;
}