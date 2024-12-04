#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Function to implement the Bellman-Ford algorithm
void bellmanFord(int V, int E, vector<Edge> &edges, int src) {
    vector<int> distance(V, INT_MAX);
    distance[src] = 0;


    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (int j = 0; j < E; ++j) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative-weight cycle" << endl;
            return;
        }
    }

    // Print the shortest distances from the source
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        if (distance[i] == INT_MAX) {
            cout << i << "\t\t" << "INF" << endl;
        } else {
            cout << i << "\t\t" << distance[i] << endl;
        }
    }
}

int main() {
    int V = 5; // Num of vertices 
    int E = 8; // Num of edges
    vector<Edge> edges = {
        {0, 1, 1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, 3}
    };

    int src = 0; // Source vertex
    bellmanFord(V, E, edges, src);

    return 0;
}

