#include <iostream>
#include <queue>
#include <vector>
#include "RedBlackBST.h"
using namespace std;

RedBlackBST::RedBlackBST()
{
    root = nullptr;
}

bool RedBlackBST::isRED(Node *x)
{
    if (x == nullptr)
        return false;
    return x->color == RED;
}

Node *RedBlackBST::rotateLeft(Node *h)
{
    Node *h2 = h->right;
    h->right = h2->left;
    h2->left = h;
    h2->color = h->color;
    h->color = RED;

    h2->N = h->N;
    h->N = size(h->left) + size(h->right) + 1;

    return h2;
}

Node *RedBlackBST::rotateRight(Node *h)
{
    Node *h2 = h->left;
    h->left = h2->right;
    h2->right = h;
    h2->color = h->color;
    h->color = RED;

    h2->N = h->N;
    h->N = size(h->left) + size(h->right) + 1;

    return h2;
}

void RedBlackBST::flipColors(Node *h)
{
    h->color = RED;
    if (h->left != nullptr)
    {
        h->left->color = BLACK;
    }
    if (h->right != nullptr)
    {
        h->right->color = BLACK;
    }
}

bool RedBlackBST::insert(int key)
{
    root = insert(root, key);

    if (root != nullptr)
    {
        root->color = BLACK;
        return true;
    }
    return false;
}
Node *RedBlackBST::insert(Node *h, int key)
{
    if (h == nullptr)
    {
        return new Node(key, key, 1, RED);
    }

    if (isRED(h->left) && isRED(h->right))
    {
        flipColors(h);
    }

    if (key < h->key)
    {
        h->left = insert(h->left, key);
    }
    else if (key > h->key)
    {
        h->right = insert(h->right, key);
    }

    if (isRED(h->right) && !isRED(h->left) && isRED(h))
    {
        h = rotateLeft(h);
    }

    if (isRED(h->right) && isRED(h->right->left))
    {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
    }

    if (isRED(h->left) && isRED(h->left->left))
    {
        h = rotateRight(h);
    }

    if (isRED(h->right) && isRED(h->right->right))
    {
        h = rotateLeft(h);
    }

    h->N = size(h->left) + size(h->right) + 1;
    return h;
}

int RedBlackBST::size()
{
    return size(root);
}

int RedBlackBST::size(Node *h)
{
    if (h == nullptr)
        return 0;
    else
        return h->N;
}

void RedBlackBST::print()
{

    if (root == nullptr)
    {
        return;
    }
    queue<Node *> SchwarzBaum;
    queue<Node *> nodeQueue;
    queue<int> levelQueue;

    nodeQueue.push(root);
    levelQueue.push(0);

    while (!nodeQueue.empty())
    {
        Node *current = nodeQueue.front();
        nodeQueue.pop();

        int level = levelQueue.front();

        if (current->color == BLACK)
        {
            SchwarzBaum.push(current);
        }
        if (current->left != nullptr)
        {
            nodeQueue.push(current->left);
            levelQueue.push(level + 1);
        }
        if (current->right != nullptr)
        {
            nodeQueue.push(current->right);
            levelQueue.push(level + 1);
        }
    }

    int currentLevel = -1;
    while (!SchwarzBaum.empty())
    {
        int level = levelQueue.front();
        levelQueue.pop();

        if (level != currentLevel)
        {
            cout << endl;
            cout << "Level " << level << ": ";
            currentLevel = level;
        }

        Node *current = SchwarzBaum.front();
        SchwarzBaum.pop();
        cout << "(";
        if (current->left != nullptr && isRED(current->left))
        {
            cout << current->left->key << ",";
        }
        cout << current->key;
        if (current->right != nullptr && isRED(current->right))
        {
            cout << "," << current->right->key;
        }
        cout << ") ";
    }
    cout << endl;
}