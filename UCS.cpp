
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include<bits/stdc++.h>

using namespace std;

// Function to perform Uniform Cost Search (UCS)
void uniformCostSearch(int start, int goal, const map<int, vector<pair<int, int>>>& graph) {
    // Priority queue to select the node with the minimum cost
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    map<int, int> distance;  // Store minimum distances from start node
    map<int, int> parent;    // Track the parent node for path reconstruction

    // Initialize distances with a high value (infinity)
    for (const auto& node : graph) {
        distance[node.first] = INT_MAX;
    }

    // Start from the initial node
    pq.push({0, start}); // {cost, node}
    distance[start] = 0;
    parent[start] = -1;   // Start node has no parent

    while (!pq.empty()) {
        int currentCost = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        // If we reached the goal node, stop the search
        if (currentNode == goal) {
            cout << "Goal reached with cost: " << currentCost << endl;
            break;
        }

        // Explore neighbors of the current node
        for (const auto& neighbor : graph.at(currentNode)) {
            int neighborNode = neighbor.first;
            int edgeCost = neighbor.second;
            int newCost = currentCost + edgeCost;

            // If a cheaper path to the neighbor is found, update and push to the queue
            if (newCost < distance[neighborNode]) {
                distance[neighborNode] = newCost;
                pq.push({newCost, neighborNode});
                parent[neighborNode] = currentNode;  // Update parent to reconstruct path
            }
        }
    }

    // Print the path from start to goal
    if (distance[goal] == INT_MAX) {
        cout << "No path found from " << start << " to " << goal << endl;
    } else {
        cout << "Path from " << start << " to " << goal << ": ";
        vector<int> path;
        for (int node = goal; node != -1; node = parent[node]) {
            path.push_back(node);
        }
        reverse(path.begin(), path.end());
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
}

int main() {
    // Graph represented as an adjacency list
    // Each node has a vector of pairs {neighbor, weight}
    map<int, vector<pair<int, int>>> graph;

    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter edges (format: node1 node2 weight):" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight}); // For undirected graph
    }

    int start, goal;
    cout << "Enter start and goal nodes: ";
    cin >> start >> goal;

    // Perform UCS
    uniformCostSearch(start, goal, graph);

    return 0;
}
