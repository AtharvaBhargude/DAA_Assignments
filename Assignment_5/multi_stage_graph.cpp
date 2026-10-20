
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    int n;
    cout << "Enter number of stages: ";
    cin >> n;

    vector<vector<int>> stages(n);
    int totalCities = 0;

    // Enter cities stage by stage
    for (int i = 0; i < n; i++) {
        int count;
        cout << "Enter number of cities in Stage "
             << i + 1 << ": ";
        cin >> count;

        cout << "City IDs: ";
        for (int j = 0; j < count; j++) {
            stages[i].push_back(totalCities);
            cout << totalCities << " ";
            totalCities++;
        }
        cout << endl;
    }

    vector<vector<pair<int, int>>> graph(totalCities);

    int routes;
    cout << "\nEnter total number of routes: ";
    cin >> routes;

    cout << "Enter source ID, destination ID, cost\n";
    for (int i = 0; i < routes; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost});
    }

    int source = stages[0][0];
    int destination = stages[n - 1][0];

    vector<int> dp(totalCities, INT_MAX / 2);
    vector<int> parent(totalCities, -1);

    dp[source] = 0;

    // Dynamic Programming
    for (int i = 0; i < n; i++) {
        for (int u : stages[i]) {
            for (auto edge : graph[u]) {
                int v = edge.first;
                int cost = edge.second;

                if (dp[u] + cost < dp[v]) {
                    dp[v] = dp[u] + cost;
                    parent[v] = u;
                }
            }
        }
    }

    // Choose the cheapest final-stage city
    for (int v : stages[n - 1]) {
        if (dp[v] < dp[destination]) {
            destination = v;
        }
    }

    if (dp[destination] >= INT_MAX / 2) {
        cout << "\nNo route available!\n";
    } else {
        cout << "\nMinimum delivery cost: "
             << dp[destination] << endl;

        vector<int> path;
        for (int v = destination; v != -1;
             v = parent[v]) {
            path.push_back(v);
        }

        cout << "Best route: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}
