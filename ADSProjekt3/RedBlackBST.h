#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

/**
 * @class RedBlackBST
 * @brief A red-black binary search tree implementation based on Robert Sedgewick's algorithms.
 *
 * Internally, the tree simulates a 2-3-4 tree using red-black balancing.
 */
class RedBlackBST
{
private:
    Node *root;

    bool isRED(Node *h);        // s. Sedgewick: S. 464
    Node *rotateLeft(Node *h);  // s. Sedgewick: S. 465
    Node *rotateRight(Node *h); // s. Sedgewick: S. 465
    void flipColors(Node *h);   // s. Sedgewick: S. 468
    int size(Node *h);

    Node *insert(Node *h, int key);

public:
    RedBlackBST();
    Node *getRoot()
    {
        return this->root;
    }
    bool insert(int key);
    int size();
    void print(); // Ausgabe des Baumes als 2-3-4-Baum
};
