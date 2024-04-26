#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int value;
    Node *left, *right;
};
Node *root;
void insert(int val)
{
    Node *newNode = new Node;
    newNode->value = val;
    newNode->left = nullptr;
    newNode->right = nullptr;

    if (root == nullptr)
    {
        root = newNode;
        return;
    }

    Node *parent, *son;
    son = root;
    parent = nullptr;
    do {
        parent = son;
        if (val < parent->value)
            son = parent->left;
        else
            son = parent->right;
    } while (son != nullptr);

    if (val < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;
}
void preOrder(Node *starting = root)
{
    cout << starting->value << " ";
    if (starting->left != nullptr)
        preOrder(starting->left);
    if (starting->right != nullptr)
        preOrder(starting->right);
}
void inOrder(Node *starting = root)
{
    if (starting->left != nullptr)
        inOrder(starting->left);
    cout << starting->value << " ";
    if (starting->right != nullptr)
        inOrder(starting->right);
}
void postOrder(Node *starting = root)
{
    if (starting->left != nullptr)
        postOrder(starting->left);
    if (starting->right != nullptr)
        postOrder(starting->right);
    cout << starting->value << " ";
}

int main()
{

}