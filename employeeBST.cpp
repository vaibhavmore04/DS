#include <iostream>
using namespace std;

class node {
public:
    int data;            // This can be Roll No or Employee ID
    node* left;
    node* right;

    node() {
        left = NULL;
        right = NULL;
    }
};

class bst {
public:
    node* root;

    bst() {
        root = NULL;
    }

    node* insert(node* root, int val) {
        if (root == NULL) {
            node* newnode = new node();
            newnode->data = val;
            return newnode;
        }
        if (val < root->data)
            root->left = insert(root->left, val);
        else
            root->right = insert(root->right, val);

        return root;
    }
};

// Inorder → Ascending
void inorder(node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// Reverse Inorder → Descending
void descending(node* root) {
    if (root) {
        descending(root->right);
        cout << root->data << " ";
        descending(root->left);
    }
}

// Height of BST
int height(node* root) {
    if (!root) return 0;
    return max(height(root->left), height(root->right)) + 1;
}

// Minimum value
int minValue(node* root) {
    if (!root) return -1;
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

// Search node
bool search(node* root, int val) {
    if (!root) return false;
    if (root->data == val) return true;
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}

// Count total nodes
int countNodes(node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeaf(node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int main() {
    bst tree;
    int choice, val;

    do {
        cout << "\n--- BST MENU (Student/Employee Records) ---\n";
        cout << "1. Insert Record\n";
        cout << "2. Display Height of BST\n";
        cout << "3. Display Minimum Record Value\n";
        cout << "4. Search Record\n";
        cout << "5. Display Records in Ascending Order\n";
        cout << "6. Display Records in Descending Order\n";
        cout << "7. Display Total Number of Records\n";
        cout << "8. Display Number of Leaf Nodes\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Record Value (roll no / employee id): ";
            cin >> val;
            tree.root = tree.insert(tree.root, val);
            break;

        case 2:
            cout << "Height of BST: " << height(tree.root) << endl;
            break;

        case 3:
            cout << "Minimum Value in BST: " << minValue(tree.root) << endl;
            break;

        case 4:
            cout << "Enter value to search: ";
            cin >> val;
            if (search(tree.root, val))
                cout << "Record FOUND.\n";
            else
                cout << "Record NOT found.\n";
            break;

        case 5:
            cout << "Records in Ascending Order: ";
            inorder(tree.root);
            cout << endl;
            break;

        case 6:
            cout << "Records in Descending Order: ";
            descending(tree.root);
            cout << endl;
            break;

        case 7:
            cout << "Total Records: " << countNodes(tree.root) << endl;
            break;

        case 8:
            cout << "Leaf Nodes: " << countLeaf(tree.root) << endl;
            break;

        case 9:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice.\n";
        }

    } while (choice != 9);

    return 0;
}
/*

*/