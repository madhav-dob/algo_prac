#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Function to create a graph with V vertices and E edges
Graph createGraph(int V, int E) {
    Graph graph;
    graph.V = V;
    graph.E = E;
    return graph;
}

// Find function for Disjoint Set
int find(vector<int> &parent, int i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

// Union function for Disjoint Set
void unionSets(vector<int> &parent, vector<int> &rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

// Comparator function to sort edges by weight
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to find the Minimum Spanning Tree using Kruskal's Algorithm
void kruskalMST(Graph &graph) {
    int V = graph.V;
    vector<Edge> result; // Store the resultant MST
    vector<int> parent(V);
    vector<int> rank(V, 0);

    // Initialize disjoint sets
    for (int v = 0; v < V; ++v) {
        parent[v] = v;
    }

    // Sort edges by weight
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    int e = 0; // Number of edges in the MST
    int i = 0; // Index used to pick next edge

    // Pick the smallest edge and add it to the result if it doesn't form a cycle
    while (e < V - 1 && i < graph.E) {
        Edge nextEdge = graph.edges[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result.push_back(nextEdge);
            unionSets(parent, rank, x, y);
            e++;
        }
    }

    // Print the edges of the Minimum Spanning Tree
    cout << "Edges in the Minimum Spanning Tree:\n";
    for (auto &edge : result) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << "\n";
    }
}

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    Graph graph = createGraph(V, E);

    // Add edges to the graph
    graph.edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Find and print the Minimum Spanning Tree
    kruskalMST(graph);

    return 0;
}
