/*Write a menu-driven C++ program to construct a binary search tree by inserting the values in order. Give considering at beginning with an empty binary search tree after considering a binary tree. 
1.Insert new node, 
2.find number of node in the longest path from the root,
3.minimum data value found in the tree, 
4.search value,
5.print values in ascending and descending order.*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        root = createNode(value);
    } 
    else if (value < root->data) {
        root->left = insert(root->left, value);
    } 
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    return root;
}

int height(Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
    
}

int findMin(Node* root) {
    if (root == NULL)
        return -1;
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

bool search(Node* root, int value) {
    if (root == NULL)
        return false;
    if (value == root->data)
        return true;
    else if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

void printAscending(Node* root) {   // Inorder Traversal
    if (root != NULL) {
        printAscending(root->left);
        cout << root->data << " ";
        printAscending(root->right);
    }
}

void printDescending(Node* root) {
    if (root != NULL) {
        printDescending(root->right);
        cout << root->data << " ";
        printDescending(root->left);
    }
}

int main() {
    Node* root = NULL;
    int choice, value;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Insert node\n";
        cout << "2. Find longest path (Height)\n";
        cout << "3. Find minimum value\n";
        cout << "4. Search a value\n";
        cout << "5. Print ascending and descending order\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                root = insert(root, value);
                break;

            case 2:
                cout << "Height of the tree: " << height(root) << endl;
                break;

            case 3:
                cout << "Minimum value in BST: " << findMin(root) << endl;
                break;

            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value))
                    cout << "Value Found\n";
                else
                    cout << "Value Not Found\n";
                break;

            case 5:
                cout << "Ascending order: ";
                printAscending(root);
                cout << "\nDescending order: ";
                printDescending(root);
                cout << endl;
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid Choice! Try Again.\n";
        }
    } while (choice != 6);

    return 0;
}
