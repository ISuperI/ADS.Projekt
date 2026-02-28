// ADS Praktikum 1.2 BST
// Name: Niklas Haug
#pragma once

/**
 * Struktur zur Darstellung eines Knotens eines (Binaer-)Baumes
 *
 * @param data Zahlenwert der im Baum gespeichert wird
 * @param left Linkes Kind des Knotens
 * @param right Rechtes Kind des Knotens
 *
 */
struct node
{
	int data;
	int height;
	node *left, *right;
};

/**
 * Klasse zur Darstellung eines Binaerbaumes
 *
 * @param root Wurzelknoten des Baumes
 *
 */
class bst
{
	node *root = nullptr;

public:
	node *find(int value);
	void insert(int value);
	void deleteValue(int value);
	void printInorder();
	void printPreorder();
	void printPostorder();
	void printLevelorder();

	//TEST
	void startTest();
	void clear(); 

private:
	void insert_ausfuehrung(node *current, int value);
	void printInorder_ausfuehrung(node *current);
	void printPreorder_ausfuehrung(node *current);
	void printPostorder_ausfuehrung(node *current);
	void printLevelorder_ausfuehrung(node *current);
	node* delete_ausfuehrung(node* current, int value);
	int updateHeight(node *current);

	//TEST
	void clear_ausfuehrung(node* current);
};