#include <iostream>
#include<vector>

using namespace std;

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    n += n;
    vector<char> row(n);
    for (int i = 0; i < n; i++) {
       row[i] = (i % 2 != 0) ? 'L' : 'D';
    }
    int l = 0, r = n - 1;
    while (l < r) {
        swap(row[l], row[r]);
        while (row[l] != 'D') l++;
        while (row[r] != 'L') r--;

    }
    for (auto i : row) cout << i << " ";
    return 0;
}