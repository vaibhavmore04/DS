#include <iostream>
#include <string.h>
using namespace std;

class AVLnode {
public:
    int id;                  // Employee ID
    char name[30];           // Employee Name
    AVLnode *left, *right;
    int ht;
};

class AVLtree {
public:
    AVLnode *root;
    AVLtree() { root = NULL; }

    int height(AVLnode *T) {
        if (!T) return 0;
        return max(height(T->left), height(T->right)) + 1;
    }

    int BF(AVLnode *T) {
        if (!T) return 0;
        return height(T->left) - height(T->right);
    }

    AVLnode* rotate_right(AVLnode *x) {
        AVLnode *y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    AVLnode* rotate_left(AVLnode *x) {
        AVLnode *y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Insert Employee
    AVLnode* insert(AVLnode *root, int id, char name[]) {
        if (!root) {
            AVLnode *n = new AVLnode();
            n->id = id;
            strcpy(n->name, name);
            n->left = n->right = NULL;
            n->ht = 1;
            return n;
        }

        if (id < root->id)
            root->left = insert(root->left, id, name);
        else if (id > root->id)
            root->right = insert(root->right, id, name);
        else {
            cout << "\nDuplicate Employee ID!\n";
            return root;
        }

        root->ht = height(root);

        int balance = BF(root);

        if (balance > 1 && id < root->left->id)
            return rotate_right(root);

        if (balance < -1 && id > root->right->id)
            return rotate_left(root);

        if (balance > 1 && id > root->left->id) {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }

        if (balance < -1 && id < root->right->id) {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }

        return root;
    }

    // Search Employee with comparison count
    AVLnode* search(AVLnode *root, int id, int &cmp) {
        while (root) {
            cmp++;
            if (id == root->id) return root;
            else if (id < root->id) root = root->left;
            else root = root->right;
        }
        return NULL;
    }

    // Find minimum
    AVLnode* minValueNode(AVLnode *node) {
        AVLnode* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    // Delete Employee
    AVLnode* deleteNode(AVLnode* root, int id) {
        if (!root) return root;

        if (id < root->id)
            root->left = deleteNode(root->left, id);
        else if (id > root->id)
            root->right = deleteNode(root->right, id);
        else {
            if (!root->left || !root->right) {
                AVLnode* temp = root->left ? root->left : root->right;
                if (!temp) return NULL;
                *root = *temp;
            } else {
                AVLnode* temp = minValueNode(root->right);
                root->id = temp->id;
                strcpy(root->name, temp->name);
                root->right = deleteNode(root->right, temp->id);
            }
        }

        root->ht = height(root);
        int balance = BF(root);

        if (balance > 1 && BF(root->left) >= 0)
            return rotate_right(root);

        if (balance > 1 && BF(root->left) < 0) {
            root->left = rotate_left(root->left);
            return rotate_right(root);
        }

        if (balance < -1 && BF(root->right) <= 0)
            return rotate_left(root);

        if (balance < -1 && BF(root->right) > 0) {
            root->right = rotate_right(root->right);
            return rotate_left(root);
        }
        return root;
    }

    // Inorder for Ascending
    void inorderAsc(AVLnode *root) {
        if (root) {
            inorderAsc(root->left);
            cout << root->id << " - " << root->name << endl;
            inorderAsc(root->right);
        }
    }

    // Reverse Inorder for Descending
    void inorderDesc(AVLnode *root) {
        if (root) {
            inorderDesc(root->right);
            cout << root->id << " - " << root->name << endl;
            inorderDesc(root->left);
        }
    }
};

int main() {
    AVLtree t;
    int choice, id, cmp;
    char name[30];

    do {
        cout << "\n--- Employee AVL Directory ---\n";
        cout << "1. Insert Employee\n2. Search Employee\n3. Delete Employee\n";
        cout << "4. Display Ascending\n5. Display Descending\n";
        cout << "6. Display Height\n7. Max Comparisons for Search\n8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

        case 1:
            cout << "Enter Employee ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            t.root = t.insert(t.root, id, name);
            break;

        case 2:
            cmp = 0;
            cout << "Enter Employee ID to Search: ";
            cin >> id;
            if(t.search(t.root, id, cmp))
                cout << "Employee Found! Comparisons = " << cmp << endl;
            else
                cout << "Not Found. Comparisons = " << cmp << endl;
            break;

        case 3:
            cout << "Enter Employee ID to Delete: ";
            cin >> id;
            t.root = t.deleteNode(t.root, id);
            break;

        case 4:
            cout << "\nAscending Order:\n";
            t.inorderAsc(t.root);
            break;

        case 5:
            cout << "\nDescending Order:\n";
            t.inorderDesc(t.root);
            break;

        case 6:
            cout << "Height of Tree: " << t.height(t.root) << endl;
            break;

        case 7:
            cout << "Maximum Comparisons = Height of Tree = " << t.height(t.root) << endl;
            break;

        case 8:
            cout << "Exit...\n";
        }
    } while(choice != 8);

    return 0;
}
/*
Headers and namespace
#include <iostream>
#include <string.h>
using namespace std;



#include <iostream>: lets us use cout, cin.


#include <string.h>: C string utilities like strcmp, strcpy.


using namespace std;: so we can write cout instead of std::cout.



Node definition
class AVLnode {
public:
    char keyword[20], meaning[20];
    AVLnode *left, *right;
    int ht;
};



Defines one node of the AVL tree.


keyword and meaning: store a word and its meaning (C-style strings, max 19 chars + '\0').


left, right: pointers to left and right child.


ht: cached height of this node (used for balancing).



Tree wrapper
class AVLtree {
public:
    AVLnode *root;
    AVLtree() { root = NULL; }



A class to manage the whole tree.


root: pointer to the tree’s root.


Constructor sets the tree initially empty.


Function declarations
    AVLnode *rotate_left(AVLnode *x);
    AVLnode *rotate_right(AVLnode *x);
    AVLnode *LL(AVLnode *x);
    AVLnode *RR(AVLnode *x);
    AVLnode *LR(AVLnode *x);
    AVLnode *RL(AVLnode *x);
    int height(AVLnode *T);
    int BF(AVLnode *T);
    AVLnode *insert(AVLnode *root, char newkey[20], char mean[20]);
    void inorder(AVLnode *root);
};



Declares all helpers:


basic rotations (rotate_left/right)


combined rotations (LL, RR, LR, RL)


height of a node and BF (balance factor)


insert to add a (keyword, meaning)


inorder to print sorted dictionary





Rotations
Right rotation:
AVLnode *AVLtree::rotate_right(AVLnode *x) {
    AVLnode *y = x->left;   // y becomes new root of this subtree
    x->left = y->right;     // move y's right subtree to x's left
    y->right = x;           // put x as right child of y
    x->ht = height(x);      // recompute heights after change
    y->ht = height(y);
    return y;               // return new subtree root
}

Left rotation:
AVLnode *AVLtree::rotate_left(AVLnode *x) {
    AVLnode *y = x->right;  // y becomes new root of this subtree
    x->right = y->left;     // move y's left subtree to x's right
    y->left = x;            // put x as left child of y
    x->ht = height(x);      // update heights
    y->ht = height(y);
    return y;               // return new subtree root
}

Convenience wrappers (print which case happened, then call basic rotations):
AVLnode *AVLtree::LL(AVLnode *T) {
    cout << "\nIn LL rotation\n";
    T = rotate_right(T);    // Left-Left ⇒ single right rotation
    return T;
}

AVLnode *AVLtree::RR(AVLnode *T) {
    cout << "\nIn RR rotation\n";
    T = rotate_left(T);     // Right-Right ⇒ single left rotation
    return T;
}

AVLnode *AVLtree::LR(AVLnode *T) {
    cout << "\nIn LR rotation\n";
    T->left = rotate_left(T->left); // first left on left child
    T = rotate_right(T);            // then right on T
    return T;
}

AVLnode *AVLtree::RL(AVLnode *T) {
    cout << "\nIn RL rotation\n";
    T->right = rotate_right(T->right); // first right on right child
    T = rotate_left(T);                // then left on T
    return T;
}


Height and Balance Factor
int AVLtree::height(AVLnode *T) {
    int hl, hr;
    if (T == NULL)
        return 0;                          // empty subtree has height 0
    hl = height(T->left);                  // height of left subtree
    hr = height(T->right);                 // height of right subtree
    return max(hl, hr) + 1;                // node height = 1 + max child
}

int AVLtree::BF(AVLnode *T) {
    int hl, hr;
    if (T == NULL) {
        return 0;                          // balance factor of empty is 0
    } else {
        if (T->left == NULL)
            hl = 0;
        else
            hl = 1 + T->left->ht;          // uses stored child heights

        if (T->right == NULL)
            hr = 0;
        else
            hr = 1 + T->right->ht;
    }
    return (hl - hr);                      // BF = left height − right height
}



Positive BF: heavier on left; negative: heavier on right.


AVL requires BF ∈ {−1, 0, +1}. If it becomes ±2, we rotate.



Insert (with rebalancing)
AVLnode *AVLtree::insert(AVLnode *root, char newkey[20], char mean[20]) {
    AVLnode *curr;
    if (root == NULL) {                     // insert position found
        curr = new AVLnode();
        strcpy(curr->keyword, newkey);      // copy strings into node
        strcpy(curr->meaning, mean);
        curr->ht = 0;
        curr->left = curr->right = NULL;
        root = curr;
        cout << "\nInserted: " << root->keyword << endl;
    } else {
        if (strcmp(newkey, root->keyword) < 0) {   // go left
            root->left = insert(root->left, newkey, mean);
            if (BF(root) == 2) {                   // too heavy on left
                if (strcmp(newkey, root->left->keyword) < 0)
                    root = LL(root);               // LL case
                else
                    root = LR(root);               // LR case
            }
        } else if (strcmp(newkey, root->keyword) > 0) { // go right
            root->right = insert(root->right, newkey, mean);
            if (BF(root) == -2) {                       // too heavy on right
                if (strcmp(newkey, root->right->keyword) > 0)
                    root = RR(root);                    // RR case
                else
                    root = RL(root);                    // RL case
            }
        } else {
            cout << "\nDuplicate Keyword!\n";          // equal keys ignored
        }
    }

    root->ht = height(root);                            // refresh height
    return root;                                        // return new subtree root
}


Inorder traversal (sorted print)
void AVLtree::inorder(AVLnode *root) {
    if (root != NULL) {
        inorder(root->left);                            // left subtree
        cout << "Keyword: " << root->keyword
             << " | Meaning: " << root->meaning
             << " | BF: " << BF(root) << endl;         // visit node
        inorder(root->right);                           // right subtree
    }
}



In BST/AVL, inorder prints keys in ascending alphabetical order (because strcmp decides left/right).



Main (menu)
int main() {
    AVLtree tree;                 // create tree object
    int choice;
    char newkey[20], mean[20];

    do {
        cout << "\n--- AVL Dictionary Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;



Prints menu and reads user choice.


        switch (choice) {
        case 1:
            cout << "Enter keyword: ";
            cin >> newkey;
            cout << "Enter meaning: ";
            cin >> mean;
            tree.root = tree.insert(tree.root, newkey, mean); // add & balance
            break;



Option 1: read a keyword and meaning, call insert, and update tree.root with (possibly rotated) new root.


        case 2:
            cout << "\nInorder Traversal:\n";
            tree.inorder(tree.root);                    // print sorted list
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}



Loop until user chooses 3.



TL;DR (What the program does)


Maintains a self-balancing dictionary where each entry is (keyword → meaning).


Insertion keeps the tree balanced using AVL rotations so that searches stay fast (O(log n)).


Inorder shows the dictionary in sorted order of keywords along with each node’s balance factor.


If you want, I can extend this with search, update meaning, or delete keyword for the complete “Employee Directory / Dictionary” style assignment.
*/