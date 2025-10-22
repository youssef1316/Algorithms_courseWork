#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;

//Main Array blank initially
int arr[30][30];

//Populating the array with sorted elements 1 -> 30

void sortedData () {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < i + 1; j++) {
            arr[i][j] = j + 1;
        }
    }
}

//reversing the order of elements
void reverseSorted () {
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < (i + 1) / 2; j++) {
            int t = arr[i][j];
            arr[i][j] = arr[i][i - j];
            arr[i][i - j] =  t;
        }
    }

}
//Random array
int randArr[30][30];

//Random Array populating
void randPopulating () {
    // range 100 - 1
    int range = 100;
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < i + 1; j++) {
            randArr[i][j] = rand() % range + 1;
        }
    }
}

//Bubble sort
int bubble_sort_count (int arr[], int n) {
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        bool swaped = false;
        for (int j = 0; j < n - i - 1; j++) {
            cnt ++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaped = true;
            }
        }
        if (!swaped) break;
    }
    return cnt;
}

int selection_sort_count(int arr[], int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            cnt++;
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
    return cnt;
}

int insertion_sort_count (int arr[], int n) {
    int cnt = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i] ;
        int j = i - 1;
        while (j >= 0) {
            cnt++;
            if (key < arr[j]) {

                arr[j + 1] = arr[j];
                j--;
            } else break;
        }
        arr[j + 1] = key;
    }
    return cnt;
}

void test_comparisons() {

    sortedData();
    cout << "Comparisons made using bubble sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout << bubble_sort_count(arr[i], n)<<'\n' ;
        auto stop = chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }
    reverseSorted();
    cout << "Comparisons made using bubble sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout << bubble_sort_count(arr[i], n)<<'\n' ;
        auto stop = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }
    randPopulating();
    cout << "Comparisons made using bubble sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout << bubble_sort_count(randArr[i], n) << '\n';
        auto stop = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }
    sortedData();
     cout << "Comparisons made using selection sort: \n";
     for (int i = 0 ;i < 30; i++) {
         int n = i + 1;
         auto start = chrono::high_resolution_clock::now();
         cout << selection_sort_count(arr[i], n) << '\n';
         auto stop = chrono::high_resolution_clock::now();
         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
         cout<< duration.count() << " milliseconds\n";
     }
    reverseSorted();
    cout << "Comparisons made using selection sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout<< selection_sort_count(arr[i], n) << '\n';
        auto stop = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }
    randPopulating();
    cout << "Comparisons made using selection sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout << selection_sort_count(randArr[i], n) << '\n';
        auto stop = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }

    sortedData();
     cout << "Comparisons made using insertion sort: \n";
     for (int i = 0 ;i < 30; i++) {
         int n = i + 1;
         auto start = chrono::high_resolution_clock::now();
         cout<< insertion_sort_count(arr[i], n) << '\n';
         auto stop = chrono::high_resolution_clock::now();
         auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
         cout<< duration.count() << " milliseconds\n";
     }

    reverseSorted();
    cout << "Comparisons made using insertion sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout << insertion_sort_count(arr[i], n) << '\n';
        auto stop = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }

    randPopulating();
    cout << "Comparisons made using insertion sort: \n";
    for (int i = 0 ;i < 30; i++) {
        int n = i + 1;
        auto start = chrono::high_resolution_clock::now();
        cout << insertion_sort_count(randArr[i], n) << '\n';
        auto stop = chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout<< duration.count() << " milliseconds\n";
    }
}

int main() {

    test_comparisons();

    return 0;
}