#include <iostream>
#include <string>
using namespace std;

struct Node {
    int f;          // f = g + h
    int order;      // insertion timestamp
    string state;   // state string
    int priority;   // here: priority = order (min-heap property)
    Node* left;
    Node* right;
    Node(int f, int order, const string &state)
        : f(f), order(order), state(state), priority(order), left(nullptr), right(nullptr) {}
};

// Right rotation (min-heap treap)
Node* rotateRight(Node* root) {
    Node* pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;
    return pivot;
}

// Left rotation (min-heap treap)
Node* rotateLeft(Node* root) {
    Node* pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;
    return pivot;
}

// Insert a node into the treap
Node* insert(Node* root, Node* node) {
    if (!root)
        return node;
    
    // Use lexicographical order of (f, order)
    if (node->f < root->f || (node->f == root->f && node->order < root->order)) {
        root->left = insert(root->left, node);
        // For a min-heap on priority, parent's priority should be <= child's priority.
        // If not, perform a right rotation.
        if (root->left && root->left->priority < root->priority)
            root = rotateRight(root);
    } else {
        root->right = insert(root->right, node);
        if (root->right && root->right->priority < root->priority)
            root = rotateLeft(root);
    }
    return root;
}

// Remove a node with key (f, order) from the treap
Node* remove(Node* root, int f, int order) {
    if (!root)
        return root;
    
    if (f < root->f || (f == root->f && order < root->order))
        root->left = remove(root->left, f, order);
    else if (f > root->f || (f == root->f && order > root->order))
        root->right = remove(root->right, f, order);
    else {
        // Found the node to remove
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            // Both children exist.
            // To maintain the min-heap property, rotate up the child with the lower priority.
            if (root->left->priority < root->right->priority) {
                root = rotateRight(root);
                root->right = remove(root->right, f, order);
            } else {
                root = rotateLeft(root);
                root->left = remove(root->left, f, order);
            }
        }
    }
    return root;
}

// Find the node with minimum key (leftmost node in BST order)
Node* findMin(Node* root) {
    if (!root)
        return nullptr;
    while (root->left)
        root = root->left;
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    Node* root = nullptr;
    int orderCounter = 0;
    
    while(n--) {
        string op;
        cin >> op;
        if (op == "enqueue") {
            string state;
            int g, h;
            cin >> state >> g >> h;
            int f = g + h;
            // Create a new node with priority equal to the insertion order
            Node* newNode = new Node(f, orderCounter++, state);
            root = insert(root, newNode);
            cout << "Insert OK!" << "\n";
        } else if (op == "dequeue") {
            if (!root) {
                cout << "Queue is empty!!" << "\n";
            } else {
                // The leftmost node is the one with the smallest (f, order)
                Node* minNode = findMin(root);
                cout << "Got " << minNode->state << "\n";
                root = remove(root, minNode->f, minNode->order);
            }
        }
    }
    
    return 0;
}
