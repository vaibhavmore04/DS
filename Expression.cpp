#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

class ExpressionTree {
private:
    Node* root;

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    void inorderRec(Node* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    void preorderRec(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    void postorderRec(Node* node) {
        if (node == nullptr) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

public:
    ExpressionTree() {
        root = nullptr;
    }

    void constructTree(string prefix) {
        stack<Node*> st;

        for (int i = prefix.length() - 1; i >= 0; i--) {
            char c = prefix[i];

            if (!isOperator(c)) {
                Node* newNode = new Node(c);
                st.push(newNode);
            } else {
                Node* newNode = new Node(c);

                Node* leftNode = st.top();
                st.pop();
                Node* rightNode = st.top();
                st.pop();

                newNode->left = leftNode;
                newNode->right = rightNode;

                st.push(newNode);
            }
        }

        root = st.top();
        st.pop();
        cout << "\nExpression tree constructed successfully!\n";
    }

    void inorder() {
        cout << "\nInorder (Recursive): ";
        inorderRec(root);
        cout << endl;
    }

    void preorder() {
        cout << "\nPreorder (Recursive): ";
        preorderRec(root);
        cout << endl;
    }

    void postorder() {
        cout << "\nPostorder (Recursive): ";
        postorderRec(root);
        cout << endl;
    }

    void inorderNonRec() {
        cout << "\nInorder (Non-Recursive): ";
        stack<Node*> st;
        Node* curr = root;

        while (curr != nullptr || !st.empty()) {
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top();
            st.pop();
            cout << curr->data << " ";
            curr = curr->right;
        }
        cout << endl;
    }

    void preorderNonRec() {
        cout << "\nPreorder (Non-Recursive): ";
        if (root == nullptr) return;

        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            Node* curr = st.top();
            st.pop();
            cout << curr->data << " ";

            if (curr->right) st.push(curr->right);
            if (curr->left) st.push(curr->left);
        }
        cout << endl;
    }

    void postorderNonRec() {
        cout << "\nPostorder (Non-Recursive): ";
        if (root == nullptr) return;

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* curr = s1.top();
            s1.pop();
            s2.push(curr);

            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }

        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << endl;
    }

    void mirror(Node* node) {
        if (node == nullptr) return;

        // Swap children
        Node* temp = node->left;
        node->left = node->right;
        node->right = temp;

        mirror(node->left);
        mirror(node->right);
    }

    void mirrorTree() {
        mirror(root);
        cout << "\nTree has been mirrored successfully!\n";
    }
};

int main() {
    ExpressionTree tree;
    string prefix;
    int choice;

    cout << "Enter prefix expression (e.g. +--a*bc/def): ";
    cin >> prefix;
    tree.constructTree(prefix);

    do {
        cout << "\n==== Expression Tree Menu ====\n";
        cout << "1. Inorder Traversal (Recursive & Non-Recursive)\n";
        cout << "2. Preorder Traversal (Recursive & Non-Recursive)\n";
        cout << "3. Postorder Traversal (Recursive & Non-Recursive)\n";
        cout << "4. Mirror (Swap Left & Right)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tree.inorder();
            tree.inorderNonRec();
            break;

        case 2:
            tree.preorder();
            tree.preorderNonRec();
            break;

        case 3:
            tree.postorder();
            tree.postorderNonRec();
            break;

        case 4:
            tree.mirrorTree();
            break;

        case 5:
            cout << "\nExiting program...\n";
            break;

        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

/*Enter prefix expression (e.g. +--a*bc/def): +--a*bc/def*/
