
#include <iostream>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[100], value[100];

    cout << "Enter weight and utility value of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }

    cout << "Enter truck capacity: ";
    cin >> W;

    int dp[101][1001] = {0};

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum utility value: " << dp[n][W] << endl;

    // Find selected items
    cout << "Selected items: ";
    int w = W;

    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << i << " ";
            w -= weight[i - 1];
        }
    }

    cout << endl;
    return 0;
}
