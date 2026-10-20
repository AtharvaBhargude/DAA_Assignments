
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Item {
    string name;
    int weight;
    int utility;
};

int main() {
    int n, W;

    cout << "=== Disaster Relief Resource Allocation ===\n";
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "\nEnter item name: ";
        cin >> items[i].name;

        cout << "Enter weight (kg): ";
        cin >> items[i].weight;

        cout << "Enter utility value: ";
        cin >> items[i].utility;
    }

    cout << "\nEnter truck capacity (kg): ";
    cin >> W;

    vector<vector<int>> dp(
        n + 1, vector<int>(W + 1, 0)
    );

    // Dynamic Programming
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];

            if (items[i - 1].weight <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    items[i - 1].utility +
                    dp[i - 1][w - items[i - 1].weight]
                );
            }
        }
    }

    cout << "\nMaximum utility: " << dp[n][W] << endl;
    cout << "\nSelected items:\n";

    int w = W;
    int totalWeight = 0;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << items[i - 1].name
                 << " | Weight: " << items[i - 1].weight
                 << " kg | Utility: " << items[i - 1].utility
                 << endl;

            totalWeight += items[i - 1].weight;
            w -= items[i - 1].weight;
        }
    }

    cout << "\nTotal weight: " << totalWeight << " kg\n";

    return 0;
}
