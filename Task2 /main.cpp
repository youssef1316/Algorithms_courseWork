#include <iostream>
#include <deque>
#include <chrono>
using namespace std;

deque<deque<string>> towers;
string emptySpot;
int n, numSteps = 0;
void setup(int n) {
    towers.clear();
    int maxWidth = 2 * n - 1;

    string empty_peg_str = string((maxWidth - 1) / 2, ' ') + "." + string((maxWidth - 1) / 2, ' ');
    emptySpot = empty_peg_str;
    for (int i = 0; i < n; i++) {
        deque<string> temp_level;


        int num_hashes = 2 * i + 1;

        int padding = (maxWidth - num_hashes) / 2;
        string disk_str = string(padding, ' ') + string(num_hashes, '#') + string(padding, ' ');


        temp_level.push_back(disk_str);
        temp_level.push_back(empty_peg_str);
        temp_level.push_back(empty_peg_str);

        towers.push_back(temp_level);
    }
}
void print() {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < 3; j++) {
            cout << towers[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "---------------------\n";
}
void p(int start, int end) {
    cout << start << " -> " << end <<'\n';
    string t;
    for (int i = 0; i < n; i++) {
        if (towers[i][start - 1] != emptySpot) {
            t = towers[i][start - 1];
            towers[i][start - 1] = emptySpot;
            numSteps++;
            for (int j = n - 1; j >= 0; j--) {
                if (towers[j][end - 1] == emptySpot) {
                    towers[j][end - 1] = t;
                    break;
                }
            }
            break;
        }
    }
    print();
}

void h (int n, int start, int end) {
    int m = 2;
    if (n == 1) {
        p(start, m);
        p(m, end);
        return;
    }
    h(n - 1, start, end);
    p(start, m);
    h(n - 1, end, start);
    p(m, end);
    h(n - 1, start, end);
}

int main() {
    cout << "Enter number of disks: ";
    cin >> n;
    setup(n);
    cout << "Original Tower: \n";
    print();
    h(n, 1, 3);
    cout << "Numer of steps taken: "<< numSteps<< '\n';

    return 0;
}