#include <iostream>
#include <vector>
#include <algorithm> // For std::max
using namespace std;

// Function to solve 0-1 Knapsack problem using Dynamic Programming
int knapsackDP(int W, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a 2D DP array where dp[i][w] represents the maximum value of items that can be achieved with the first i items and weight limit w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (weights[i - 1] <= w) {
                // Take the maximum of including the item or not including it
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                // If the item cannot be included due to weight constraints
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    // cout << "DP Table:" << endl;
    // for (int i = 0; i <= n; ++i) {
    //     for (int w = 0; w <= W; ++w) {
    //         cout << dp[i][w] << " ";
    //     }
    //     cout << endl;
    // }

    // The result is in the bottom-right cell of the table
    return dp[n][W];
}

int main() {
    int W; // Capacity of the knapsack
    int n; // Number of items

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weights(n), values(n);

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    int maxValue = knapsackDP(W, weights, values, n);
    cout << "The maximum value that can be achieved is: " << maxValue << endl;

    return 0;
}