#include <fstream>
#include <iostream>

using namespace std;

struct  Node {
    string key;
    Node* right;
    Node* left;
    int height;
};
//calculate the height of a node
int height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}
//calculate the balance factor
int getBalance (Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

//recalculates the height of a node after a rotation
void updateHeight (Node* node) {
    node -> height = 1 + max(height(node->left), height(node-> right));
}

//creating a new node
Node* newNode (const string& key){
    Node* node = new Node();
    node -> key = key;
    node -> right = node -> left = nullptr;
    node -> height = 1;
    return node;
}

//perform a left rotate around node x
Node* leftRotate(Node* x) {
    //right right imbalance
    Node * y = x-> right;
    Node * z = y-> left;
    y-> left = x;
    x->right = z;
    updateHeight(x);
    updateHeight(y);
    //new root
    return y;
}

//perform a right rotate around a node y
Node* rightRotate(Node* y) {
    //left left imbalance
    Node * x = y-> left;
    Node * z = x-> right;
    x->right = y;
    y-> left = z;
    updateHeight(y);
    updateHeight(x);
    //new root
    return x;
}

//the insertion function inside the tree
Node* insert(Node* node, const string& key){
    //recursive search for the empty location following the BST rules to insert in the correct place
    if (node == nullptr)
        return newNode(key);
    if (key < node -> key)
        node-> left = insert(node -> left, key);
    else if (key > node -> key)
        node -> right = insert(node-> right, key);
    else return node;

    updateHeight(node);
    //check if the tree is balanced
    int balance = getBalance(node);

    //ll case
    if (balance > 1 && key < node-> left -> key)
        return rightRotate(node);
    //rr case
    if (balance < -1 && key > node -> right -> key)
        return leftRotate(node);
    //Left Right case
    if (balance > 1 && key > node -> left -> key) {
        node ->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //Right Left case
    if (balance < -1 && key < node -> right -> key) {
        node -> right = rightRotate(node-> right);
        return leftRotate(node);
    }
    return node;
}

//searching for the closest string
void findPredSucc (Node* root, const string& key, Node*& pred, Node*& succ) {
    //pred and succ passed by reference to be edited directly without a return
    while (root != nullptr) {
        if (root-> key == key) {
            //exact match
            //pred is the max value in the left subtree
            if (root -> left) {
                Node * temp = root->left;
                while (temp->right) temp = temp->right;
                pred = temp;
            }
            //succ is the min value in the right subtree
            if (root-> right) {
                Node* temp = root->right;
                while (temp->left) temp = temp->left;
                succ = temp;
            }
            return;
        }
        if (key < root->key) {
            //curr node might be succ
            succ = root;
            root = root -> left;
        }
        else {
            //curr node might be pred
            pred = root;
            root = root -> right;
        }
    }
}

int findLexicographical (const string& a, const string& b) {
    int n = min(a.size(), b.size());
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return abs(a[i] - b[i]);
        //the difference in the first different char
    }
    return abs((int)a.size() - (int)b.size());
    // if both are the same size
}
Node* findClosest(Node* root, const string& target) {
    if (!root) return nullptr;
    Node* pred = nullptr; // the closest word before the target
    Node* succ = nullptr; // the closest word after the target
    findPredSucc(root, target, pred, succ);
    Node* curr = root;
    //loop to check if the target exists in the tree
    while (curr) {
        if (curr -> key == target) return curr;
        if (target < curr-> key) curr = curr -> left;
        else curr = curr -> right;
    }
    if (!pred && !succ) return nullptr;
    if (!pred) return succ; //there is no string smaller than the target
    if (!succ) return pred; //there is no string bigger than the target
    int diffpred = findLexicographical(pred-> key, target);
    int diffsucc = findLexicographical(succ-> key, target);

    return (diffpred <= diffsucc) ? pred : succ; // returning the closest one
}

int main() {
    Node* root = nullptr;
    ifstream file("dictionary.txt");
    string word;
    while (file >> word) root = insert(root, word);
    file.close();
    string input;
    cout << "Enter -1 to exit the program\n";
    while (true) {
        cout << "Enter a string: ";
        cin >> input;
        if (input == "-1") break;
        Node* result = findClosest(root, input);
        if (result) cout << "The closest match is: " << result-> key << '\n';
        else cout << "The tree is empty!\n";
    }

    return 0;
}