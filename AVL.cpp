#include <iostream>
#include <string>
using namespace std;
struct AVL
{
    string keyword, meaning;
    AVL *left;
    AVL *right;
    int ht, BF;
};
class AVLtree
{
public:
    AVL *root;
    AVLtree()
    {
        root = NULL;
    }
    AVL *insert(AVL *root, string newkey, string mean);
    AVL *rotate_left(AVL *x);
    AVL *rotate_right(AVL *x);
    AVL *LL(AVL *x);
    AVL *LR(AVL *x);
    AVL *RR(AVL *x);
    AVL *RL(AVL *x);
    int BF(AVL *root);
    int H(AVL *root);
    bool search(AVL *root, string key);
    void inorder(AVL *root);
};

AVL *AVLtree ::insert(AVL *root, string newkey, string mean)
{
    AVL *curr;
    if (root == NULL)
    {
        curr = new AVL;
        curr->keyword = newkey;
        curr->meaning = mean;
        curr->ht = 0;
        curr->left = NULL;
        curr->right = NULL;
        root = curr;
    }
    else
    {
        if (newkey < root->keyword)
        {
            root->left = insert(root->left, newkey, mean);
            cout << "\n BF:" << BF(root);
            if (BF(root) == 2)
            {
                if (newkey < root->left->keyword)
                {
                    root = LL(root);
                }
                else
                {
                    root = LR(root);
                }
            }
        }
        else
        {
            if (newkey > root->keyword)
            {
                root->right = insert(root->right, newkey, mean);
                cout << "\n BF:" << BF(root);
                if (BF(root) == -2)
                {
                    if (newkey > root->right->keyword)
                    {
                        root = RR(root);
                    }
                    else
                    {
                        root = RL(root);
                    }
                }
            }
            else
            {
                cout << " \n Equal";
            }
        }
    }
    root->ht = H(root);
    return root;
}
// BF : Balance Factor
int AVLtree::BF(AVL *root)
{
    int BF = H(root->left) - H(root->right);
    return (BF);
}

AVL *AVLtree::rotate_right(AVL *x)
{
    AVL *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = H(x);
    y->ht = H(y);
    return y;
}
// H : Height
int AVLtree::H(AVL *root)
{
    int HL, HR;
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        HL = H(root->left) + 1;
        HR = H(root->right) + 1;
        if (HL > HR)
        {
            return HL;
        }
        else
        {
            return HR;
        }
    }
}

AVL *AVLtree::rotate_left(AVL *x)
{
    AVL *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = H(x);
    y->ht = H(y);
    return y;
}
AVL *AVLtree::LL(AVL *T)
{
    T = rotate_right(T);
    return T;
}
AVL *AVLtree::RR(AVL *T)
{
    T = rotate_left(T);
    return T;
}
AVL *AVLtree::LR(AVL *T)
{
    T->left = rotate_left(T->left);
    T = rotate_right(T);
    return T;
}
AVL *AVLtree::RL(AVL *T)
{
    T->right = rotate_right(T->right);
    T = rotate_right(T);
    return T;
}

bool AVLtree::search(AVL *root, string key)
{
    if (root == NULL)
        return false;
    if (root->keyword == key)
    {
        cout << "\n " << root->keyword << " " << root->meaning;
        return true;
    }
    if (key < root->keyword)
        return search(root->left, key);
    return search(root->right, key);
};
void AVLtree ::inorder(AVL *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << "\n"<<root->keyword << " " << root->meaning;
        inorder(root->right);
    }
} 
int main()
{
    AVLtree T;
    int choice;
    string w, mn, key;
    do
    {
        cout << "\n1.insert";
        cout << "\n2.Display";
        cout << "\n3.Search";
        cout << "\n4.enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\n Enter New Word: ";
            cin >> w;
            cout << "Meaning: ";
            cin >> mn;
            T.root = T.insert(T.root, w, mn);
            break;
        case 2:
            T.inorder(T.root);
            break;
        case 3:
            cout << "Enter word to search: ";
            cin >> key;
            if (!T.search(T.root, key))
            {
                cout << "Word not found.\n";
            }
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 0);
    return 0;
}
