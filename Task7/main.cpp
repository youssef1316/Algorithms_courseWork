#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
vector <int> v;
vector <int> taken;

int greedyKnapsac (int n, int mx) {
    //sorting to select the cheapest items
    sort(v.begin(), v.end());
    int p = 0;
    for (int i = 0; i < n; i++) {
        if (v[i] <= mx) {
            taken.push_back(v[i]);
            mx -= v[i];
            p ++;
        }
        if (mx == 0) return p;
    }
    return p;
}

int dynamicKnapsack (int n, int mx) {
    //initialization of the table
    vector<vector<int>> dp(n + 1, vector<int>(mx + 1, 0));
    for (int i = 1; i <= n; i++) {
        //selecting a price
        int p = v[i - 1];
        for (int w = 0; w <= mx; w++) {
            if (p <= w) {
                //calculating the best choice for the current options
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - p] + 1);
            }
            else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    int ans = dp[n][mx];
    int w = mx;
    //backtracking to select the best choice
    for (int i = n; i > 0 && ans > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            taken.push_back(v[i-1]);
            ans--;
            w-= v[i-1];
        }
    }
    //the actual max taken
    return dp[n][mx];
}
int main() {
    int n, mx;
    cin >> n >> mx;
    for (int i = 0 ; i < n; i++) {
        int price;
        cin >> price;
        v.push_back(price);
    }
    cout << "The number of items taken using dynamic knapsack is: "<< dynamicKnapsack(n,mx) << '\n';
    cout << "The price of taken items are: \n";
    for (auto i : taken) cout << i <<'\n';

    //emptying the taken vector
    taken.clear();

    cout << "The number of items taken using greedy knapsack is: "<< greedyKnapsac(n,mx) << '\n';
    cout << "The price of taken items are: \n";
    for (auto i : taken) cout << i <<'\n';

    //difference in outputs because:
    //greedy selects the cheapest price
    //dp explores all combinations and selects the last valid choice as it backtrack
}


