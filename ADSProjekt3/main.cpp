// ADS Praktikum 3
// Name: Niklas Haug
#include <iostream>
#include "RedBlackBST.h"
#define CATCH_CONFIG_RUNNER
#include "gip_mini_catch.h"

using namespace std;

void mainscreen_menu()
{
    std::cout << "----------------------------------------" << endl
              << "1) Datensatz einfuegen, manuell " << endl
              << "2) Datenstruktur anzeigen " << endl
              << "3) Programm beenden " << endl
              << "?>";
}

void mainscreen_addNode(RedBlackBST &ref)
{
    int key;

    std::cout << "+ Bitte geben Sie die den Schluessel ein:" << endl;
    std::cout << " Key ?> ";
    std::cin >> key;

    bool res = ref.insert(key);
    if (res)
    {
        std::cout << "+ Ihr Datensatz wurde eingefuegt" << endl;
    }
}

void mainscreen_printTree(RedBlackBST &ref)
{
    ref.print();
}

int main()
{
    Catch::Session().run();

    int numbers[] = {503, 502, 403, 1002, 2002, 3002};
    int N = sizeof(numbers) / sizeof(int);

    RedBlackBST tree2;
    for (int i = 0; i < N; i++)
    {
        tree2.insert(numbers[i]);
    }
    tree2.print();

    RedBlackBST tree;
    cout << endl
         << "Person Analyzer v19.84, by George Orwell" << endl;

    int menu_option = 0;
    while (true)
    {
        do
        {
            mainscreen_menu();
            cin >> menu_option;
        } while (menu_option < 1 || menu_option > 3);

        switch (menu_option)
        {
        case 1:
            mainscreen_addNode(tree);
            break;
        case 2:
            mainscreen_printTree(tree);
            break;
        case 3:
            return 0;
        }
    }

    system("PAUSE");

    return 0;
}