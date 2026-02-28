#pragma once

const bool RED = true;
const bool BLACK = false;

class Node
{
public:
    int key;     // Schluessel
    int val;     // damit verbundene Daten
    Node* left;  // Referenz auf den linken Teilbaum
    Node* right; // Referenz auf den rechten Teilbaum
    int   N;     // Anzahl Knoten im Teilbaum
    bool  color; // Farbe der Referenz vom Elternknoten zu diesem Knoten

    Node(int key, int data, int N, bool color)
    {
        this->key   = key;
        this->val   = data;
        this->N     = N;
        this->color = color;
        this->left  = nullptr;
        this->right = nullptr;
    }
};
