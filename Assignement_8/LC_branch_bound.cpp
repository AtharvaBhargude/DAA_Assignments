#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// Structure to represent a node in the state space tree
struct Node {
    vector<int> path;  // Stores the cities visited so far
    int cost;          // Total cost of the current path
    int city;          // Current city
    int visited;       // Bitmask to track visited cities
};

// Comparator for Least Cost (LC) Branch and Bound
// The node with the minimum cost gets the highest priority
struct Compare {
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
};

int main() {
    int n;

    // Read the number of cities
    cout << "Enter number of cities: ";
    cin >> n;

    // Create the cost adjacency matrix
    vector<vector<int>> cost(n, vector<int>(n));

    // Read the cost matrix
    // 0 indicates no route between different cities
    cout << "Enter cost matrix (0 for same city):\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    // Min-priority queue to select the least-cost node
    priority_queue<Node, vector<Node>, Compare> pq;

    // Create the starting node at city 0
    Node start;
    start.path.push_back(0); // Start from city 0
    start.cost = 0;          // Initial cost is zero
    start.city = 0;          // Current city is 0
    start.visited = 1;       // Mark city 0 as visited

    // Insert the starting node into the priority queue
    pq.push(start);

    // Store the minimum tour cost and the corresponding path
    int minCost = INT_MAX;
    vector<int> bestPath;

    // Process nodes until the priority queue becomes empty
    while (!pq.empty()) {

        // Remove the node with the least accumulated cost
        Node current = pq.top();
        pq.pop();

        // Prune the node if its cost cannot improve the best solution
        if (current.cost >= minCost)
            continue;

        // Check whether all cities have been visited
        if (current.visited == (1 << n) - 1) {

            // Calculate the cost of returning to the starting city
            int returnCost = cost[current.city][0];

            // Update the optimal solution if a valid, cheaper tour exists
            if (returnCost > 0 &&
                current.cost + returnCost < minCost) {

                minCost = current.cost + returnCost;

                // Save the best path found so far
                bestPath = current.path;

                // Add city 0 to complete the tour
                bestPath.push_back(0);
            }

            continue;
        }

        // Generate child nodes for every unvisited city
        for (int next = 0; next < n; next++) {

            // Check whether the next city is unvisited
            // and a valid route exists to it
            if (!(current.visited & (1 << next)) &&
                cost[current.city][next] > 0) {

                // Create a child node
                Node child;

                // Copy the current path and add the next city
                child.path = current.path;
                child.path.push_back(next);

                // Update the current city
                child.city = next;

                // Mark the next city as visited
                child.visited = current.visited | (1 << next);

                // Calculate the accumulated path cost
                child.cost = current.cost +
                             cost[current.city][next];

                // Insert the child if it may improve the best solution
                if (child.cost < minCost)
                    pq.push(child);
            }
        }
    }

    // Display the result
    if (minCost == INT_MAX) {
        cout << "No complete delivery route exists.\n";
    } else {
        cout << "\nOptimal delivery route: ";

        // Print the optimal route
        for (int city : bestPath)
            cout << city << " ";

        cout << "\nMinimum delivery cost: "
             << minCost << endl;
    }

    return 0;
}
