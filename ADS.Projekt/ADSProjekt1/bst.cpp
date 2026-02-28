// ADS Praktikum 1.2 BST
// Name: Niklas Haug
#include <queue>
#include <iostream>
#include "bst.h"

using namespace std;

/**
 * Start-Funktion zur Suche eines Integer-Zahlenwertes im Baum
 *
 * @param value Integer-Zahlenwert, der gesucht werden soll
 * 
 *   erstellt den aktuellen Knoten mit dem Wert der Wurzel
 * * Das Programm durchsucht den Baum von der Wurzel aus 
 * * Vergleicht den Wert mit dem aktuellen Knoten und geht dann weiter
 * . Wenn der Wert kleiner ist, wird der linke Kindknoten aufgerufen
 * . Wenn der Wert größer ist, wird der rechte Kindknoten aufgerufen
 * * Gibt den Wert wenn er Gefunden wurde aus
 * . Falls er nicht gefunden wurd wird der nullptr zurrückgegeben
 *
 */
node *bst::find(int value)

{
	node *current = root;

	while (current)
	{
		if (value == current->data)
			return current;

		else if (value < current->data)
			current = current->left;
		else
			current = current->right;
	}

	return nullptr;
}

/**
 * Funktion zum Einfuegen eines Integer-Zahlenwertes in den Baum
 *
 * @param value Integer-Zahlenwert, der eingefuegt werden soll
 * 
 * * setzt den Knoten als Wurzel, wenn der Baum leer ist
 * * sonst wird die Funktion insert_ausfuehrung aufgerufen
 */
void bst::insert(int value)
{
	if (root == nullptr)
		root = new node{value, 0, nullptr, nullptr};
	else
		insert_ausfuehrung(root, value);
}

/**
 * Rekursive Funktion zum Einfuegen eines Integer-Zahlenwertes im Baum
 *
 * @param current Knoten, hinter den eingefuegt werden soll
 * @param value Integer-Zahlenwert, der eingefuegt werden soll
 * 
 * * Vergleicht den Wert mit dem Knoten um zu entscheiden, wo der Knoten eingefügt werden soll
 *   schaut ob der Wert kleiner oder größer als der aktuelle Knoten ist
 *   wenn kleiner, wird der linke Kindknoten aufgerufen
 *   wenn größer, wird der rechte Kindknoten aufgerufen
 * . geht rekursiv durch den Baum bis ein Nullptr gefunden wird und fügt den Knoten dadurch an der richtigen Stelle ein
 *   Der Knoten beseitzt die Attribute: value, höhe und Kindknoten links und rechts
 * * Die Höhe wird aktualisiert
 *
 */
void bst::insert_ausfuehrung(node *current, int value)
{
	if (value < current->data)
	{
		if (current->left == nullptr)
			current->left = new node{value, 0, nullptr, nullptr};
		else
			insert_ausfuehrung(current->left, value);
	}
	else
	{
		if (current->right == nullptr)
			current->right = new node{value, 0, nullptr, nullptr};
		else
			insert_ausfuehrung(current->right, value);
	}

	updateHeight(current);
}
/**
 * Funktion zum Ausgeben des Baumes in Inorder
 * 
 * * ruft die Funktion printInorder_ausfuehrung auf
 * 
 */

void bst::printInorder()
{
	cout << "Inorder: ";
	printInorder_ausfuehrung(root);
	cout << endl;
}

/**
 * Rekursive Funktion zum Ausgeben des Baumes in Inorder
 * 
 * . Eigentliche Funktion zum Ausgeben des Baumes in Inorder
 * * Ausgabe: links → Wurzel → rechts
*/

void bst::printInorder_ausfuehrung(node *current)
{
	if (current == nullptr)
		return;

	printInorder_ausfuehrung(current->left);
	cout << current->data << " ";
	printInorder_ausfuehrung(current->right);
}

/**
 * Funktion zum Ausgeben des Baumes in Preorder
 * 
 * * ruft die Funktion printPreorder_ausfuehrung auf
 * 
*/

void bst::printPreorder()
{
	cout << "Preorder: ";
	printPreorder_ausfuehrung(root);
	cout << endl;
}

/**
 * Rekursive Funktion zum Ausgeben des Baumes in Preorder
 * 
 * . Eigentliche Funktion zum Ausgeben des Baumes in Preorder
 * * Ausgabe: Wurzel → links → rechts
*/

void bst::printPreorder_ausfuehrung(node *current)
{
	if (current == nullptr)
		return;

	cout << current->data << " " ;
	printPreorder_ausfuehrung(current->left);
	printPreorder_ausfuehrung(current->right);
}

/**
 * Funktion zum Ausgeben des Baumes in Postorder
 * 
 * * ruft die Funktion printPostorder_ausfuehrung auf
 * 
*/

void bst::printPostorder()
{
	cout << "Postorder: ";
	printPostorder_ausfuehrung(root);
	cout << endl;
}

/**
 * Rekursive Funktion zum Ausgeben des Baumes in Postorder
 * 
 * . Eigentliche Funktion zum Ausgeben des Baumes in Postorder
 * * Ausgabe: links → rechts → Wurzel
*/

void bst::printPostorder_ausfuehrung(node *current)
{
	if (current == nullptr)
		return;

	printPostorder_ausfuehrung(current->left);
	printPostorder_ausfuehrung(current->right);
	cout << current->data << " ";
}

/**
 * Funktion zum Ausgeben des Baumes in Levelorder
 * 
 * * ruft die Funktion printLevelorder_ausfuehrung auf
 * 
*/

void bst::printLevelorder()
{
	cout << "Levelorder: ";
	printLevelorder_ausfuehrung(root);
	cout << endl;
}

/**
 * Rekursive Funktion zum Ausgeben des Baumes in Levelorder
 * 
 * . Eigentliche Funktion zum Ausgeben des Baumes in Levelorder
 * * Es wird eine Queue erstellt, die Level für Level durchlaufen wird
 * . Fügt die Kindesknoten rekusiv in die Queue hinzu um sie in Levelorder auszugeben
 *  Die Queue wird solange durchlaufen, bis sie leer ist
*/

void bst::printLevelorder_ausfuehrung(node *current)
{
	if (current == nullptr)
		return;

	queue<node *> queue;
	queue.push(current);

	while (!queue.empty())
	{
		node *current = queue.front();
		queue.pop();

		cout << current->data << " ";

		if (current->left)
			queue.push(current->left);
		if (current->right)
			queue.push(current->right);
	}
	cout << endl;
}

/**
 *  Funktion zum Aktualisieren der Höhe eines Knotens
 * 
 * Wenn der Knoten leer ist, wird -1 zurückgegeben
 * * Die Höhe des linken und rechten Kindknotens wird ermittelt
 * * Die Höhe des aktuellen Knotens wird auf die größere Höhe der Kindesknoten + 1 gesetzt
 * Kein Kindesknoten hat eine Höhe von -1
 * Falls der Knoten keine Kindsknoten hat, wird die Höhe also auf 0 gesetzt
 * . Die Höhe des Knotens wird zurückgegeben
*/

int bst::updateHeight(node *current)
{
	if (current == nullptr)
		return -1;
	int left_Height = current->left ? current->left->height : -1;
	int right_Height = current->right ? current->right->height : -1;

	if (left_Height > right_Height)
		current->height = left_Height + 1;
	else
		current->height = right_Height + 1;

	return current->height;
}

/**
 * Funktion zum Löschen eines Knotens
 * 
 * * Ruft die Funktion delete_ausfuehrung auf
*/
   
void bst::deleteValue(int value)
{
	root = delete_ausfuehrung(root, value);
}

/**
 * Rekursive Funktion zum Löschen eines Knotens
 * 
 *  Wenn der Knoten leer ist, wird nullptr zurückgegeben
 * 
 * * Sucht den Knoten mit dem Wert, der gelöscht werden soll
 * . Es wird geschaut ob der Wert kleiner oder größer als der aktuelle Knoten ist und dem entsprechend wird der linke oder rechte Kindknoten aufgerufen
 *   Also wenn er kleiner ist, wird der linke Kindknoten aufgerufen
 * 	 wenn er größer ist, wird der rechte Kindknoten aufgerufen
 * 
 * * sobald der Knoten gefunden wurde, wird geschaut ob er keine Kindknoten hat, einen oder zwei und die entsprechenden Funktion wird ausgeführt
 * . Wenn er keine Kindknoten hat, wird der Knoten gelöscht und nullptr zurückgegeben
 * . Wenn er einen Kindknoten hat, wird der Knoten gelöscht und der Kindknoten wird zurückgegeben
 * . Wenn er zwei Kindknoten hat, wird der Knoten gelöscht und der kleinsten Wert asu dem rechten Teilbaum wird zurückgegeben
 *   Bei einem und Zwei Kindesknoten ersetzt der Kindesknoten den Knoten
 * * Höhe wird aktualisiert
 * */

node *bst::delete_ausfuehrung(node *current, int value)
{
	if (current == nullptr)
		return nullptr;

	if (value < current->data)
		current->left = delete_ausfuehrung(current->left, value);

	else if (value > current->data)
		current->right = delete_ausfuehrung(current->right, value);
	else
	{
		if (current->left == nullptr && current->right == nullptr)
		{
			delete current;
			return nullptr;
		}
		else if (current->left == nullptr)
		{
			node *temp = current->right;
			delete current;
			return temp;
		}
		else if (current->right == nullptr)
		{
			node *temp = current->left;
			delete current;
			return temp;
		}
		else
		{
			node *parent = current;
			node *temp = current->right;

			while (temp->left != nullptr)
			{
				parent = temp;
				temp = temp->left;
			}
			current->data = temp->data;

			if (parent->left == temp)
			{
				parent->left = temp->right;
			}
			else
			{
				parent->right = temp->right;
			}

			delete temp;
		}
	}

	updateHeight(current);

	return current;
}

// TEST
void bst::startTest()
{
	cout << "Test Start" << endl;

	int values[] = {46, 83, 95, 22, 17, 68, 11, 82, 21, 31, 54, 99, 74};
	for (int i = 0; i < 13; i++)
	{
		insert(values[i]);
	}

	cout << "Eingabe:";
	for (int i = 0; i < 13; i++)
	{
		cout << " " << values[i];
	}
	cout << endl;

	cout << "Baum in ";
	printInorder();

	cout << "Suche nach 17: ";
	node *n1 = find(17);
	if (n1)
		cout << "Gefunden: " << n1->data << endl;
	else
		cout << "Nicht gefunden!";

	cout << "Suche nach 11: ";
	node *n2 = find(11);
	if (n2)
		cout << "Gefunden: " << n2->data << endl;
	else
		cout << "Nicht gefunden!";

	cout << "Loesche 68, 21, 17, 95...";
	deleteValue(68);
	deleteValue(21);
	deleteValue(17);
	deleteValue(95);
	cout << endl;

	cout << "Suche nach 17: ";
	node *n3 = find(17);
	if (n3)
		cout << "Gefunden: " << n3->data << endl;
	else
		cout << "Nicht gefunden!" << endl;

	cout << "Suche nach 11: ";
	node *n4 = find(11);
	if (n4)
		cout << "Gefunden: " << n4->data << endl;
	else
		cout << "Nicht gefunden!" << endl;

	cout << "Baum in ";
	printInorder();

	cout << "Baum in ";
	printPreorder();

	cout << "Baum in ";
	printPostorder();

	cout << "Baum in ";
	printLevelorder();

	cout << "Test Ende" << endl;
	clear();
}

// TEST
void bst::clear()
{
	cout << "Moechtest du den Baum leeren? (j): ";
	char eingabe;
	cin >> eingabe;
	if (eingabe == 'j' || eingabe == 'J')
	{
		clear_ausfuehrung(root);
		root = nullptr;
		cout << "Baum geleert" << endl;
	}
	else
	{
		cout << "Baum nicht geleert" << endl;
	}
}

void bst::clear_ausfuehrung(node *current)
{
	if (current == nullptr)
		return;
	clear_ausfuehrung(current->left);
	clear_ausfuehrung(current->right);
	delete current;
}