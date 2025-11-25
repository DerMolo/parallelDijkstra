// dijkstraAlgo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
//implementing my "Guess" of how dijkstra's algo works 
/* 

*/
class node; 
namespace std {
    template<>
    struct hash<node> {
        size_t operator()(pair<node*, node*>& p) {
            uintptr_t a = (uintptr_t)p.first;
            uintptr_t b = (uintptr_t)p.second;

            size_t h1 = hash<uintptr_t>{}(a);
            size_t h2 = hash<uintptr_t>{}(b);
            return h1 ^ (h2 << 1);
        }
        bool operator()(pair<node*, node*>& a, pair<node*, node*>& b) {
            return a.first == b.first && a.second == b.second;
    };
    };
}
class node {
public: 
    int ID; 
    double weight;
    //hashmap that stores the distances of a node's adjacent members 
    //unordered_map<node*, double> nodeDistances;
    //dijkstra algo should handle distance calculations
    vector<node*> adjacentNodes{};
    /*
    *     node(vector <node*>neighbours, double weight) {
        this->weight = weight;
        adjacentNodes = neighbours; 
        //calculating node distance per weight 
        for (auto i = adjacentNodes.begin(); i < adjacentNodes.end(); i++) {
            node* accessedNeighbour = *i; 
            nodeDistances[accessedNeighbour] = weight - accessedNeighbour->weight;
        }
    }

    void setDistances() {
        for (auto i = adjacentNodes.begin(); i < adjacentNodes.end(); i++) {
            node* accessedNeighbour = *i;
            nodeDistances[accessedNeighbour] = this->weight - accessedNeighbour->weight;
        }
    }
    */

    node(double weight, int ID) { this->weight = weight; this->ID = ID; }

    void setNeighbours(vector<node*>neighbours) { this->adjacentNodes = neighbours; }

    //establishes a symmetric connection between nodes
    //nodeA -> nodeB && nodeB -> nodeA 
    void setPair(node* a, node* b) {
        a->adjacentNodes.push_back(b);
        b->adjacentNodes.push_back(a);
    }

    ~node() {
        adjacentNodes.erase(adjacentNodes.begin() + adjacentNodes.size());
        //nodeDistances.clear();
    }
};

vector<node> shortestPath(node& source, node& destination, int graphSize) {
    vector<node> establishedNodes = { source };
    /*
    * For a given source node:
    1) visit all unknown neighbouring nodes
    2) establish a temporary memory of distances corresponding to each node
    3) choose the node with the minimal distance
    4) repeat the previous steps for the chosen node
    5) return a list of visited nodes
    */
    node target = source;
    vector<node> visitedNodes = { source };

    while (true) {
        double min = target.weight;
        node minNode = target;
        int neighbourCount = source.adjacentNodes.size();
        unordered_map<node*, int> tempVisitedNodes;

        for (int i = 0; i < neighbourCount; i++) {
            node* neighbour = target.adjacentNodes[i];
            double distance = abs(target.weight - neighbour->weight);
            tempVisitedNodes[neighbour] += 1;
            if (distance < min) {
                minNode = *neighbour;
                min = distance;
            }
            target = minNode;
            establishedNodes.push_back(minNode);
            if (tempVisitedNodes.size() == graphSize)
                return establishedNodes;
        }
    }
}
double randDouble(){return (double)rand() / (double)RAND_MAX;}
int main()
{
    srand(NULL);
    int graphSize = 10; 
    vector<node*> nodeGraph;
    //initializing graph of nodes  
    for (int i = 0; i < graphSize; i++) {
        double randomWeight = randDouble();
        //node* tempNode = new node(randomWeight,i);
        nodeGraph.push_back(new node(randomWeight, i));
    }
    for (auto temp : nodeGraph)
        cout << "ID: " << temp->ID << " WEIGHT: " << temp -> weight << endl;

    //populating nodeGraph with randomly connected neighbours 
    for (int i = 0; i < graphSize; i++) {
        int randomNeighbourCount = 1 + (int)rand() % graphSize;
        cout << "i: "<<i << " randomNeighbourCount: " << randomNeighbourCount << endl;
        //unordered_map<int, int> histogram;

        //unordered_map<node*, node*> connectedPairs;
        unordered_map<std::pair<node*, node*>, bool> connectedPairs;//hash_map used for checking the existence of a pair
        for (int x = 0; x < randomNeighbourCount; x++) {
            cout << "\tx: " << x << endl;
            /*
            Rules: 
            reject duplicates, self-connecting nodes, and already-formed pairs
            */
            //hash map ensuring duplicate values are not included
            int randomIndex = (int)rand() % graphSize;

            //cout << "randomIndex: " << randomIndex << endl;
            //histogram[randomIndex] += 1;
            //if (histogram[randomIndex] > 1) //ignores duplicate values 
            //    continue; 
            if ( connectedPairs[{nodeGraph[i],nodeGraph[randomIndex]}] && connectedPairs[{nodeGraph[randomIndex], nodeGraph[i]}]){  //<A,B> == <B,A> 
                cout << "PAIR ALREADY EXIST: " << randomIndex << ", " << i << endl;
                continue;
            }
            if (randomIndex == i) {
                cout << "SKIPPING SELF-REFERENCE" << endl;
                continue;
            } //ignores self-references

            cout << "\trandomIndex: " << randomIndex << endl;//" histogram: " << histogram[randomIndex] << endl;
            //connectedPairs[nodeGraph[randomIndex]] = nodeGraph[i];
            //connectedPairs[nodeGraph[i]]
            connectedPairs[{nodeGraph[i], nodeGraph[randomIndex]}] = true;
            connectedPairs[{nodeGraph[randomIndex], nodeGraph[i]}] = true;
;           nodeGraph[i]->setPair(nodeGraph[i], nodeGraph[randomIndex]); 

            //nodeGraph[i]->adjacentNodes.push_back(nodeGraph[randomIndex]);
            //nodeGraph[randomIndex]->adjacentNodes.push_back(nodeGraph[i]);
        }
		//distances are set after neighbours are populated
        // shortestRoute() will handle this 
        //nodeGraph[i]->setDistances();
    }
    cout << "PRINTING ENTIRE GRAPH: " << endl;
    for (auto i = nodeGraph.begin(); i < nodeGraph.end(); i++) {
        node temp = **i;
        cout << "NODE ID: " << temp.ID << endl;
        for (auto x = temp.adjacentNodes.begin(); x < temp.adjacentNodes.end(); x++) {
            node subTemp = **x;
            cout << "\t NODE ID: " << subTemp.ID << "  WEIGHTS: "<< subTemp.weight << endl;
        }
    }
    int source = 1 + (int)rand() % graphSize;
    int dest = 1 + (int)rand() % graphSize;
    cout << "source: " << source << " : " << nodeGraph[source]->weight << " \ndest: " << dest << " : " << nodeGraph[dest]->weight << endl;

    vector<node> estNodes = shortestPath(*nodeGraph[source], *nodeGraph[dest], graphSize);
    cout << "FOUND SHORTEST PATH: \n";
    int ind = 0;
    for (auto i = estNodes.begin(); i < estNodes.end(); i++) {
        cout << "i: " << ind << " WEIGHT: " << i->weight << endl;
        ind++;
    }
}

