#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class node {
public:
    int id;
    string name;
    node* left;
    node* right;

    node(int id, string name) {
        this->id = id;
        this->name = name;
        left = right = NULL;
    }
};

class BST {
public:
    node* root;

    BST() {
        root = NULL;
    }

    // Non-recursive insert
    void insert(int id, string name) {
        node* newnode = new node(id, name);
        
        if(root == NULL) {
            root = newnode;
            return;
        }
        
        node* current = root;
        while(true) {
            if(id < current->id) {
                if(current->left == NULL) {
                    current->left = newnode;
                    break;
                }
                current = current->left;
            }
            else {
                if(current->right == NULL) {
                    current->right = newnode;
                    break;
                }
                current = current->right;
            }
        }
    }

    // Non-recursive search
    bool search(int id) {
        node* current = root;
        
        while(current != NULL) {
            if(current->id == id)
                return true;
            else if(id < current->id)
                current = current->left;
            else
                current = current->right;
        }
        return false;
    }

    // Non-recursive inorder using stack
    void inorder() {
        if(root == NULL) return;
        
        stack<node*> s;
        node* current = root;
        
        while(current != NULL || !s.empty()) {
            while(current != NULL) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << "ID: " << current->id << "  Name: " << current->name << endl;
            current = current->right;
        }
    }

    int minID() {
        if(root == NULL) return -1;
        node* current = root;
        while(current->left != NULL)
            current = current->left;
        return current->id;
    }

    int maxID() {
        if(root == NULL) return -1;
        node* current = root;
        while(current->right != NULL)
            current = current->right;
        return current->id;
    }

    // Non-recursive height using level order
    int height() {
        if(root == NULL) return 0;
        
        queue<node*> q;
        q.push(root);
        int h = 0;
        
        while(!q.empty()) {
            int size = q.size();
            h++;
            for(int i = 0; i < size; i++) {
                node* current = q.front();
                q.pop();
                if(current->left != NULL)
                    q.push(current->left);
                if(current->right != NULL)
                    q.push(current->right);
            }
        }
        return h;
    }

    // Non-recursive count nodes using queue
    int countNodes() {
        if(root == NULL) return 0;
        
        queue<node*> q;
        q.push(root);
        int count = 0;
        
        while(!q.empty()) {
            node* current = q.front();
            q.pop();
            count++;
            if(current->left != NULL)
                q.push(current->left);
            if(current->right != NULL)
                q.push(current->right);
        }
        return count;
    }

    // Non-recursive count leaf nodes using queue
    int countLeaf() {
        if(root == NULL) return 0;
        
        queue<node*> q;
        q.push(root);
        int count = 0;
        
        while(!q.empty()) {
            node* current = q.front();
            q.pop();
            if(current->left == NULL && current->right == NULL)
                count++;
            if(current->left != NULL)
                q.push(current->left);
            if(current->right != NULL)
                q.push(current->right);
        }
        return count;
    }
};

int main() {
    BST tree;
    int choice, id;
    string name;

    do {
        cout << "\n--- PATIENT RECORD MENU ---\n";
        cout << "1. Insert Patient Record\n";
        cout << "2. Search Patient by ID\n";
        cout << "3. Display All Patients (Sorted)\n";
        cout << "4. Find Minimum and Maximum Patient ID\n";
        cout << "5. Display Total Nodes, Leaf Nodes, and Height\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Patient Name: ";
                cin >> name;
                tree.insert(id, name);
                break;

            case 2:
                cout << "Enter Patient ID to Search: ";
                cin >> id;
                if(tree.search(id))
                    cout << "Patient Found.\n";
                else
                    cout << "Patient NOT Found.\n";
                break;

            case 3:
                cout << "\nPatient Records (Sorted by ID):\n";
                tree.inorder();
                break;

            case 4:
                cout << "Minimum Patient ID = " << tree.minID() << endl;
                cout << "Maximum Patient ID = " << tree.maxID() << endl;
                break;

            case 5:
                cout << "Total Patients = " << tree.countNodes() << endl;
                cout << "Leaf Patients = " << tree.countLeaf() << endl;
                cout << "Height of Tree = " << tree.height() << endl;
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while(choice != 6);

    return 0;
}

/*--- PATIENT RECORD MENU ---
1. Insert Patient Record
2. Search Patient by ID
3. Display All Patients (Sorted)
4. Find Minimum and Maximum Patient ID
5. Display Total Nodes, Leaf Nodes, and Height
6. Exit
Enter choice: 1
Enter Patient ID: 101
Enter Patient Name: Vaibhav

Enter choice: 1
Enter Patient ID: 55
Enter Patient Name: Sumit

Enter choice: 1
Enter Patient ID: 150
Enter Patient Name: Ramesh

Enter choice: 3

Patient Records (Sorted by ID):
ID: 55  Name: Sumit
ID: 101 Name: Vaibhav
ID: 150 Name: Ramesh

Enter choice: 2
Enter Patient ID to Search: 101
Patient Found.

Enter choice: 4
Minimum Patient ID = 55
Maximum Patient ID = 150

Enter choice: 5
Total Patients = 3
Leaf Patients = 2
Height of Tree = 2

Enter choice: 6
Exiting...
*/