// dijkstraAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
//implementing my "Guess" of how dijkstra's algo works 
/* 

*/


class node {
public: 
    double weight;
    //hashmap that stores the distances of a node's adjacent members 
    unordered_map<node*, double> nodeDistances;
    vector<node*> connectedNodes{};
    node(vector <node*>neighbours, double weight) {
        this->weight = weight;
        connectedNodes = neighbours; 
        //calculating node distance per weight 
        for (auto i = connectedNodes.begin(); i < connectedNodes.end(); i++) {
            node* accessedNeighbour = *i; 
            nodeDistances[accessedNeighbour] = weight - accessedNeighbour->weight;
        }
    }
    node(double weight) {this->weight = weight;}

    void setNeighbours(vector<node*>neighbours) { this->connectedNodes = neighbours; }

    void setDistances() {
        for (auto i = connectedNodes.begin(); i < connectedNodes.end(); i++) {
            node* accessedNeighbour = *i;
            nodeDistances[accessedNeighbour] = this->weight - accessedNeighbour->weight;
        }
    }
    ~node() {
        connectedNodes.erase(connectedNodes.begin() + connectedNodes.size());
        nodeDistances.clear();
    }
};

vector<node> dijkstra(const node& source) {

}
double randDouble() {return (double)rand() / (double)RAND_MAX;}
int main()
{
    srand(NULL);
    int nodeCount = 10; 
    vector<node*> nodeGraph(nodeCount);
    //initializing graph of nodes  
    for (int i = 0; i < nodeCount; i++) {
        double randomWeight = randDouble();
        nodeGraph.push_back(new node(randomWeight));
    }
    //populating nodeGraph with randomly connected neighbours 
    for (int i = 0; i < nodeCount; i++) {
        int randomNeighbourCount = 1 + (int)rand() % nodeCount;
        for (int x = 0; x < randomNeighbourCount; x++) {
            /*
            Rules: 
            no duplicate & self-connecting nodes 
            */
            //hash map ensuring duplicate values are not included
            unordered_map<int, int> histogram;
            int randomIndex = (int)rand() % nodeCount;
            histogram[randomIndex] += 1;
            if (histogram[randomIndex] > 0)
                continue; 
            if (randomIndex == i)
                continue; 
            nodeGraph[i]->connectedNodes.push_back(nodeGraph[randomIndex]);
        }
        nodeGraph[i]->setDistances()
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
