
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> path;
    int cost;
    int city;
    int visited;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.cost > b.cost;
    }
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "Enter cost matrix (0 for same city):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    priority_queue<Node, vector<Node>, Compare> pq;

    Node start;
    start.path.push_back(0);
    start.cost = 0;
    start.city = 0;
    start.visited = 1;

    pq.push(start);

    int minCost = INT_MAX;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.cost >= minCost)
            continue;

        if (current.visited == (1 << n) - 1) {
            int returnCost = cost[current.city][0];

            if (returnCost > 0 &&
                current.cost + returnCost < minCost) {
                minCost = current.cost + returnCost;
                bestPath = current.path;
                bestPath.push_back(0);
            }
            continue;
        }

        for (int next = 0; next < n; next++) {
            if (!(current.visited & (1 << next)) &&
                cost[current.city][next] > 0) {

                Node child;
                child.path = current.path;
                child.path.push_back(next);
                child.city = next;
                child.visited =
                    current.visited | (1 << next);
                child.cost =
                    current.cost + cost[current.city][next];

                if (child.cost < minCost)
                    pq.push(child);
            }
        }
    }

    if (minCost == INT_MAX) {
        cout << "No complete delivery route exists.\n";
    } else {
        cout << "\nOptimal delivery route: ";
        for (int city : bestPath)
            cout << city << " ";

        cout << "\nMinimum delivery cost: " << minCost << endl;
    }

    return 0;
}
