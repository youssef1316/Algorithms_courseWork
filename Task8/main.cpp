#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <iomanip>

using namespace std;
const int EMPTY = 0;


// Represents a single move action
struct Move {
    int from;
    int to;
};

// Represents the state of the game at a specific moment
struct GameState {
    vector<vector<int>> stacks;
    int g; // Cost (moves made so far)
    int h; // Heuristic (estimated moves remaining)

    // Total score f = g + h
    int f() const { return g + h; }

    // Operator for Priority Queue (Min-Heap behavior)
    bool operator>(const GameState& other) const {
        return f() > other.f();
    }

    // Operator for Equality checks
    bool operator==(const GameState& other) const {
        return stacks == other.stacks;
    }
};

// hashing the data
struct StateHash {
    size_t operator()(const vector<vector<int>>& stacks) const {
        size_t seed = 0;
        for (const auto& stack : stacks) {
            for (int color : stack) {
                //hashing to check if a move is seen before in a single int to be mem. efficient
                seed ^= hash<int>{}(color) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            // Add a separator for stack boundaries
            seed ^= hash<int>{}(-1) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

class BallSortSolver {
    int num_stacks;
    int stack_capacity;

    //Mismatch penalty
    //counts the number of balls that are not on the same color
    int mismatch_heuristic(const vector<vector<int>>& stacks) {
        int penalty = 0;
        for (const auto& stack : stacks) {
            if (stack.empty()) continue;
            // Check balls from bottom to top
            for (size_t i = 0; i < stack.size(); ++i) {
                if (i == 0) continue;
                if (stack[i] != stack[i-1]) {
                    penalty++;
                }
            }
        }
        return penalty;
    }

    // Check if the game is solved
    //loops over all the stacks and checks if the colors are the same or not
    bool is_goal(const vector<vector<int>>& stacks) {
        // Keep track of colors we have already found in a completed stack
        set<int> completed_colors;

        for (const auto& stack : stacks) {
            if (stack.empty()) continue;

            int first_color = stack[0];

            // 1. Check if the stack is uniform (all same color)
            for (int color : stack) {
                if (color != first_color) return false;
            }
            if (completed_colors.count(first_color)) {
                return false;
            }

            // Mark this color as done
            completed_colors.insert(first_color);
        }
        return true;
    }

    // Helper to print stacks visually
    void print_visual(const vector<vector<int>>& current_stacks) {
        cout << "\n";
        // Iterate from the top of the capacity down to 0
        for (int h = stack_capacity - 1; h >= 0; --h) {
            for (int i = 0; i < num_stacks; ++i) {
                if (h < current_stacks[i].size()) {
                    cout << "| " << current_stacks[i][h] << " | ";
                } else {
                    cout << "|   | ";
                }
            }
            cout << "\n";
        }
        // Print the base line
        for (int i = 0; i < num_stacks; ++i) cout << "----- ";
        cout << "\n";
        // Print stack numbers
        for (int i = 0; i < num_stacks; ++i) cout << "  " << i + 1 << "   ";
        cout << "\n\n";
    }

public:
    BallSortSolver(int n, int cap) : num_stacks(n), stack_capacity(cap) {}

    // Main Solver Function
    void solve(vector<vector<int>> initial_stacks) {
        //stores the states in the form of vectors making the min on top (min-heap)
        priority_queue<GameState, vector<GameState>, greater<GameState>> pq;
        // Track visited states to prevent infinite loops
        set<size_t> visited_hashes;
        //traces the path till the current move
        map<vector<vector<int>>, pair<vector<vector<int>>, Move>> parent_map;
        GameState start_state;
        start_state.stacks = initial_stacks;
        start_state.g = 0; //no moves yett
        //calc the initial h
        start_state.h = mismatch_heuristic(initial_stacks);
        pq.push(start_state);
        visited_hashes.insert(StateHash{}(initial_stacks));

        // Used to mark the start of the path with dummy values because no past
        parent_map[initial_stacks] = { {}, {-1, -1} };

        //main loop
        while (!pq.empty()) {
            //pick the highest priority and pop
            GameState current = pq.top();
            pq.pop();

            //if it is a solution
            if (is_goal(current.stacks)) {
                print_solution(current.stacks, initial_stacks, parent_map);
                return;
            }

            // Generate Moves
            for (int i = 0; i < num_stacks; ++i) { // Source Stack
                if (current.stacks[i].empty()) continue; // Cannot move from empty

                for (int j = 0; j < num_stacks; ++j) { // Target Stack
                    if (i == j) continue; // skip the same stack

                    // Check Capacity
                    if (current.stacks[j].size() >= stack_capacity) continue; //no room!

                    // Check Color Rules
                    //can place || target top color is the same as the source
                    int ball_to_move = current.stacks[i].back();
                    bool can_place = false;
                    if (current.stacks[j].empty()) {
                        can_place = true;
                    } else {
                        if (current.stacks[j].back() == ball_to_move) {
                            can_place = true;
                        }
                    }

                    if (can_place) {
                        // Create New State
                        vector<vector<int>> new_stacks = current.stacks;
                        new_stacks[i].pop_back();
                        new_stacks[j].push_back(ball_to_move);

                        //temporary var of teh curr state
                        size_t new_hash = StateHash{}(new_stacks);


                        //check if the hash is in the visited if points to end then not found
                        if (visited_hashes.find(new_hash) == visited_hashes.end()) {
                            //insert the new id
                            visited_hashes.insert(new_hash);
                            GameState next_state;
                            next_state.stacks = new_stacks;
                            next_state.g = current.g + 1;
                            next_state.h = mismatch_heuristic(new_stacks);
                            //recalc f for the new stacks

                            pq.push(next_state);
                            parent_map[new_stacks] = {current.stacks, {i + 1, j + 1}}; // +1 for 1-based indexing
                        }
                    }
                }
            }
        }
        //queue is empty without reaching a return so unsolvable
        cout << "No solution found!\n";
    }

    void print_solution(vector<vector<int>> curr, vector<vector<int>> start,
                        map<vector<vector<int>>, pair<vector<vector<int>>, Move>> &parent_map) {

        vector<Move> path;
        // Backtrack from the goal to the start to get the moves
        while (curr != start) {
            pair<vector<vector<int>>, Move> p = parent_map[curr];
            path.push_back(p.second);
            curr = p.first;
        }
        //reverse bec its filled from end to start
        reverse(path.begin(), path.end());

        cout << "Solution Found! Total Moves: " << path.size() << "\n";
        cout << "========================================\n";

        // Use a temporary state to simulate the moves forward for printing
        vector<vector<int>> temp_stacks = start;

        cout << "Initial State:";
        print_visual(temp_stacks);

        int step = 1;
        for (const auto& m : path) {
            cout << "Step " << step++ << ": Move from Stack " << m.from << " to Stack " << m.to;

            // Apply logic to temp_stacks (converting 1-based Move back to 0-based index)
            int u = m.from - 1;
            int v = m.to - 1;

            int val = temp_stacks[u].back();
            temp_stacks[u].pop_back();
            temp_stacks[v].push_back(val);

            print_visual(temp_stacks);
        }
    }
};

int main() {
    int n, cap;
    cout << "Enter number of stacks: ";
    cin >> n;
    cout << "Enter max balls per stack: ";
    cin >> cap;

    vector<vector<int>> stacks(n);

    cout << "Enter the balls for each stack (Top to Bottom)." << endl;
    cout << "Use integers for colors (e.g., 1 for Red, 2 for Blue)." << endl;
    cout << "Enter 0 to stop entering balls for a stack." << endl;

    for (int i = 0; i < n; ++i) {
        cout << "Stack " << i + 1 << ": ";
        vector<int> temp_input;
        int color;
        //while loop to allow flexible ball entering
        while (true) {
            cin >> color;
            if (color == 0) break;
            temp_input.push_back(color);
        }
        reverse(temp_input.begin(), temp_input.end());

        if (temp_input.size() > cap) {
            cout << "Error: Too many balls! Max is " << cap << endl;
            return 1;
        }
        stacks[i] = temp_input;
    }
    //initializing the class
    BallSortSolver solver(n, cap);
    solver.solve(stacks);
    return 0;
}

//input sample
// 5
// 4
// 2 1 1 2 0
// 3 3 2 3 0
// 1 2 3 1 0
// 0
// 0