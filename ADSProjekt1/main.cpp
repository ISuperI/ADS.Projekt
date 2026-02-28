// ADS Praktikum 1.2 BST
// Name: Niklas Haug
#include "bst.h"
#include <iostream>

using namespace std;

int main()
{
	bst Baum;
	int befehl;
	do
	{
		cout << "Befehle: 1: Einfuegen, 2: Suchen, 3: Loeschen, 4: Inorder, 5: Preorder, 6: Postorder, 7: Levelorder, 0: Beenden" << endl;
		cout << "Gebe eine Zahl(Befehl) ein: " << endl;
		cin >> befehl;

		if (befehl == 1)
		{
			int eingabe;
			cout << "Gebe -1 ein, um das Einfuegen zu beenden." << endl;
			do
			{
				cout << "Geben Sie den Wert ein, den Sie einfuegen wollen: ";
				cin >> eingabe;
				if (eingabe == -1)
					break;
				Baum.insert(eingabe);
			} while (true);
		}

		else if (befehl == 2)
		{
			int eingabe;
			cout << "Gebe -1 ein, um das suchen zu beenden." << endl;
			do
			{
				cout << "Gebe  den Wert ein, den Sie suchen wollen: ";
				cin >> eingabe;
				if (eingabe == -1)
					break;
				node *result = Baum.find(eingabe);
				if (result)
					cout << "Wert gefunden: " << result->data << endl;
				else
					cout << "Wert nicht gefunden." << endl;
			} while (true);
		}
		else if (befehl == 3)
		{

			int eingabe;
			cout << "Gebe -1 ein, um das loeschen zu beenden." << endl;
			do
			{
				cout << "Geben Sie den Wert ein, den Sie loeschen wollen: ";
				cin >> eingabe;
				if (eingabe == -1)
					break;
				Baum.deleteValue(eingabe);
			} while (true);
		}

		else if (befehl == 4)
		{
			Baum.printInorder();
		}
		else if (befehl == 5)
		{
			Baum.printPreorder();
		}
		else if (befehl == 6)
		{
			Baum.printPostorder();
		}
		else if (befehl == 7)
		{
			Baum.printLevelorder();
		}
		else if (befehl == 0)
		{
			break;
		}
		//TEST
		else if (befehl == 99)
		{
			Baum.startTest();
		}
		else if (befehl == 44)
		{
			Baum.clear();
		}
		//TESTENDE
		else
		{
			cout << "Ungueltige Eingabe. Bitte versuchen Sie es erneut." << endl;
		}
	} while (true);

	system("pause");
	return 0;
}