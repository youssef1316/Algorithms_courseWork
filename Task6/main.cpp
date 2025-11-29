#include <iostream>

using namespace std;

int main() {
    int c1,c2,c3;
    cout << "Enter the weigh of the three coins:\n";
    cin >> c1 >> c2 >> c3;
    if (c1 == c2 && c2 != c3) cout << "The third coin is fake\n";
    else if (c1 == c3 && c3 != c2) cout << "The second coin is fake\n";
    else cout << "The first coin is fake\n";
    return 0;
}