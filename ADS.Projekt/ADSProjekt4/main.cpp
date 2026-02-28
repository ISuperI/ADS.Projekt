#include <iostream>
#include <limits>
#include <functional>
#include <algorithm>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"

using namespace std;

void runTests();

void showMenu()
{
    cout << endl
         << "Praktikum 4: Graphenalgorithmen:" << endl
         << "1) Graph einlesen" << endl
         << "2) Tiefensuche" << endl
         << "3) Breitensuche" << endl
         << "4) MST nach Prim (Eingabe: Startknoten)" << endl
         << "5) MST nach Kruskal" << endl
         << "6) Kuerzeste Wege nach Dijkstra (Eingabe: Startknoten)" << endl
         << "7) Ausgabe der Adjazenzliste" << endl
         << "8) Kante loeschen" << endl
         << "9) Kante hinzufuegen" << endl
         << "10) Programm beenden" << endl
         << "Weiter mit beliebiger Eingabe ..." << endl;
}

// Funktion fuer die Fehlerbehandlung bei Benutzereingaben
void printInputError(const string &msg)
{
    cin.clear();
    cin.ignore(999, '\n');
    cout << msg;
}

// Funktion fuer das Einlesen eines Beispielgraphen
void menuGraphEinlesen(EdgeWeightedGraph *&G, string graphFiles[], bool &eingelsen)
{
    do
    {
        cout << "Welchen Beispielgraphen einlesen? (1, 2 oder 3): ";
        int Auswahl_G;
        cin >> Auswahl_G;
        if (cin.fail() || Auswahl_G < 1 || Auswahl_G > 3)
        {
            printInputError("Bitte eine Zahl zwischen 1 und 3 eingeben!\n> ");
            continue;
        }
        G = new EdgeWeightedGraph(graphFiles[Auswahl_G - 1]);
        cout << "Graph " << graphFiles[Auswahl_G - 1] << " wurde eingelesen\n";
        eingelsen = true;
        break;
    } while (true);
}

// Gibt den Namen für einen Knoten zurück, z.B. A, B, ... oder A2, B2 bei mehr als 26 Knoten
string label(int idx)
{
    // Berechnet den Buchstaben für den Knoten (A-Z, dann A2, B2, ...)
    char c = 'A' + (idx % 26); // Nimmt den Rest bei Division durch 26, um im Alphabet zu bleiben
    int n = idx / 26 + 1;      // Ermittelt, ob wir schon über Z hinaus sind (dann n > 1)
    string s(1, c);            // Erstellt einen String mit dem Buchstaben
    if (n > 1)
        s += to_string(n); // Hängt die Nummer an, falls mehr als 26 Knoten
    return s;              // Gibt die Bezeichnung zurück
}

// Hilfsfunktion: Wandelt einen Buchstaben (A, B, ...) in einen Index um (A=0, B=1, ...)
int charToIndex(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= 'a' && c <= 'z')
        return c - 'a';
    return -1;
}

// Gibt ein Array (z.B. edgeTo) mit Knotenbezeichnungen und Startknoten aus
void printArray(const vector<int> &arr, const string &name, int start)
{
    cout << name << ":\n"; // Gibt den Namen des Arrays aus
    for (int i = 0; i < (int)arr.size(); ++i)
    {
        cout << label(i) << " -> "; // Gibt die Knotenbezeichnung aus
        if (arr[i] == -1)
            cout << "-1 (Startknoten)"; // -1 kennzeichnet den Startknoten
        else
            cout << label(arr[i]); // Gibt den Vorgängerknoten aus
        cout << endl;
    }
    cout << endl;
}
// Gibt das Markierungsarray aus, true/false ob besucht, und markiert den Startknoten
void printMarked(const vector<bool> &marked, int start)
{
    cout << "Marked_Array:\n"; // Überschrift für das Array
    for (int i = 0; i < (int)marked.size(); ++i)
    {
        cout << label(i) << " -> " << (marked[i] ? "true" : "false"); // Gibt aus, ob der Knoten besucht wurde
        if (i == start)
            cout << " (Startknoten)"; // Markiert den Startknoten
        cout << endl;
    }
    cout << endl;
}

// Führt eine Tiefensuche (DFS) durch, fragt nach Startknoten (Buchstabe) und gibt die Ergebnisse aus
void menuTiefensuche(EdgeWeightedGraph *G)
{
    int maxKnoten = G->getV(), start_Knoten;
    char startChar;
    do
    {
        cout << "Startknoten fuer Tiefensuche (A bis " << label(maxKnoten - 1) << "): ";
        cin >> startChar;
        start_Knoten = charToIndex(startChar);
        if (cin.fail() || start_Knoten < 0 || start_Knoten >= maxKnoten)
        {
            printInputError("Ungueltige Eingabe! Bitte gueltigen Buchstaben eingeben.\n");
            continue;
        }
        break;
    } while (true);
    vector<bool> marked(maxKnoten, false);
    vector<int> edgeTo(maxKnoten, -1);
    bool connected = Graphsearch::DFS(*G, start_Knoten, marked, edgeTo);
    vector<int> besuchsfolge;
    function<void(int)> dfs = [&](int v)
    {
        if (!marked[v])
            return;
        besuchsfolge.push_back(v);
        for (const Edge &e : G->getAdj(v))
        {
            int w = e.other(v);
            if (marked[w] && find(besuchsfolge.begin(), besuchsfolge.end(), w) == besuchsfolge.end())
                dfs(w);
        }
    };
    dfs(start_Knoten);
    cout << "Tiefensuche (Depth-First-Search (DFS)) - Startknoten: " << label(start_Knoten) << endl;
    cout << "Besuchsreihenfolge:\n";
    for (int i = 0; i < besuchsfolge.size(); ++i)
    {
        cout << label(besuchsfolge[i]);
        if (i + 1 < besuchsfolge.size())
            cout << " -> ";
    }
    cout << "\n\n";
    printArray(edgeTo, "EdgeTo_Array", start_Knoten);
    printMarked(marked, start_Knoten);
    cout << "Graph ist ";
    cout << (connected ? "zusammenhaengend" : "nicht zusammenhaengend") << "\n";
}

// Führt eine Breitensuche (BFS) durch, fragt nach Startknoten (Buchstabe) und gibt die Ergebnisse aus
void menuBreitensuche(EdgeWeightedGraph *G)
{
    int maxKnoten = G->getV(), start_Knoten;
    char startChar;
    do
    {
        cout << "Startknoten fuer Breitensuche (A bis " << label(maxKnoten - 1) << "): ";
        cin >> startChar;
        start_Knoten = charToIndex(startChar);
        if (cin.fail() || start_Knoten < 0 || start_Knoten >= maxKnoten)
        {
            printInputError("Ungueltige Eingabe! Bitte gueltigen Buchstaben eingeben.\n");
            continue;
        }
        break;
    } while (true);
    vector<bool> marked;
    vector<int> edgeTo;
    bool connected = Graphsearch::BFS(*G, start_Knoten, marked, edgeTo);
    vector<int> besuchsfolge;
    vector<bool> visited(marked.size(), false);
    queue<int> q;
    q.push(start_Knoten);
    visited[start_Knoten] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        besuchsfolge.push_back(v);
        for (const Edge &e : G->getAdj(v))
        {
            int w = e.other(v);
            if (!visited[w])
            {
                visited[w] = true;
                q.push(w);
            }
        }
    }
    cout << "Breitensuche (Breadth-First-Search (BFS)) - Startknoten: " << label(start_Knoten) << endl;
    cout << "Besuchsreihenfolge:\n";
    for (int i = 0; i < besuchsfolge.size(); ++i)
    {
        cout << label(besuchsfolge[i]);
        if (i + 1 < besuchsfolge.size())
            cout << " -> ";
    }
    cout << "\n\n";
    printArray(edgeTo, "EdgeTo_Array", start_Knoten);
    printMarked(marked, start_Knoten);
    cout << "Graph ist ";
    cout << (connected ? "zusammenhaengend" : "nicht zusammenhaengend") << endl;
}

// Menüfunktion für den Prim-Algorithmus (Minimaler Spannbaum), gibt das Ergebnis im gewünschten Format aus
// Gibt das Gewicht und die Adjazenzliste des berechneten MST aus
void menuPrim(EdgeWeightedGraph *G)
{
    int start_Knoten;
    char startChar;
    cout << "Startknoten fuer Prim (A bis " << label(G->getV() - 1) << "): ";
    cin >> startChar;
    start_Knoten = charToIndex(startChar);
    if (start_Knoten < 0 || start_Knoten >= G->getV())
    {
        cout << "Ungueltige Eingabe!" << endl;
        return;
    }
    PrimMST prim(*G, start_Knoten);
    cout << "Minimaler Spannbaum (MST) nach Prim:" << endl;
    cout << start_Knoten << " Gewicht: " << prim.weight() << endl;
    cout << "Adjazenzliste:" << endl;
    int n = G->getV();
    vector<vector<pair<int, double>>> mst_adj(n);
    for (const Edge &e : prim.edges())
    {
        int v = e.either();
        int w = e.other(v);
        double weight = e.weight();
        mst_adj[v].push_back({w, weight});
    }
    for (int i = 0; i < n; ++i)
    {
        if (!mst_adj[i].empty())
        {
            cout << label(i);
            for (const auto &p : mst_adj[i])
            {
                cout << " -> " << label(p.first) << " [" << p.second << "]";
            }
            cout << endl;
        }
    }
}

// Menüfunktion für den Kruskal-Algorithmus (Minimaler Spannbaum), gibt das Ergebnis im gewünschten Format aus
// Gibt das Gewicht und die Adjazenzliste des berechneten MST aus
void menuKruskal(EdgeWeightedGraph *G)
{
    KruskalMST kruskal(*G);
    cout << "Minimaler Spannbaum (MST) nach Kruskal:" << endl;
    cout << "Gewicht: " << kruskal.weight() << endl;
    cout << "Adjazenzliste:" << endl;
    int n = G->getV();
    vector<vector<pair<int, double>>> mst_adj(n);
    for (const Edge &e : kruskal.edges())
    {
        int v = e.either();
        int w = e.other(v);
        double weight = e.weight();
        mst_adj[v].push_back({w, weight});
    }
    for (int i = 0; i < n; ++i)
    {
        if (!mst_adj[i].empty())
        {
            cout << label(i);
            for (const auto &p : mst_adj[i])
            {
                cout << " -> " << label(p.first) << " [" << p.second << "]";
            }
            cout << endl;
        }
    }
}

void menuDijkstra(EdgeWeightedGraph *G)
{
    int maxKnoten = G->getV();
    char startChar, zielChar;
    int start_Knoten, ziel_Knoten;
    // Startknoten abfragen
    do
    {
        cout << "Startknoten fuer Dijkstra (A bis " << label(maxKnoten - 1) << "): ";
        cin >> startChar;
        start_Knoten = charToIndex(startChar);
        if (cin.fail() || start_Knoten < 0 || start_Knoten >= maxKnoten)
        {
            printInputError("Ungueltige Eingabe! Bitte gueltigen Buchstaben eingeben.\n");
            continue;
        }
        break;
    } while (true);
    // Zielknoten abfragen
    do
    {
        cout << "Zielknoten fuer Dijkstra (A bis " << label(maxKnoten - 1) << "): ";
        cin >> zielChar;
        ziel_Knoten = charToIndex(zielChar);
        if (cin.fail() || ziel_Knoten < 0 || ziel_Knoten >= maxKnoten)
        {
            printInputError("Ungueltige Eingabe! Bitte gueltigen Buchstaben eingeben.\n");
            continue;
        }
        break;
    } while (true);
    // Ungerichteten Graphen in gerichteten umwandeln
    EdgeWeightedDigraph digraph(maxKnoten);
    for (int v = 0; v < maxKnoten; ++v)
    {
        for (const Edge &e : G->getAdj(v))
        {
            int w = e.other(v);
            double weight = e.weight();
            digraph.add(DirectedEdge(v, w, weight));
        }
    }
    DijkstraSP dijkstra(digraph, start_Knoten);
    if (!dijkstra.hasPathTo(ziel_Knoten))
    {
        cout << "Kein Pfad von " << label(start_Knoten) << " nach " << label(ziel_Knoten) << " vorhanden!\n";
        return;
    }
    // Arrays für Ausgabe erzeugen
    std::vector<DirectedEdge> pfad = dijkstra.pathTo(ziel_Knoten);
    // Header
    cout << "Knoten i   | ";
    for (int i = 0; i < maxKnoten; ++i)
        cout << label(i) << (i + 1 < maxKnoten ? " " : "");
    cout << "\n-------------------------------\n";
    // edgeTo
    cout << "edgeTo[i]  | ";
    for (int i = 0; i < maxKnoten; ++i)
    {
        if (i == start_Knoten)
            cout << "-";
        else
        {
            // Vorgänger suchen
            std::vector<DirectedEdge> pfad_i = dijkstra.pathTo(i);
            if (pfad_i.empty())
                cout << "-";
            else
                cout << label(pfad_i.back().from());
        }
        cout << (i + 1 < maxKnoten ? " " : "");
    }
    cout << "\n-------------------------------\n";
    // distTo
    cout << "distTo[i]  | ";
    for (int i = 0; i < maxKnoten; ++i)
    {
        double d = dijkstra.distTo(i);
        if (d == std::numeric_limits<double>::infinity())
            cout << "-";
        else
            cout << (int)d;
        cout << (i + 1 < maxKnoten ? " " : "");
    }
    cout << "\n\nKürzester Weg (Dijkstra):\n";
    cout << "Start: " << label(start_Knoten) << "\n";
    cout << "Ziel: " << label(ziel_Knoten) << "\n";
    // Pfad als Knotenfolge
    cout << "Pfad: ";
    if (pfad.empty())
    {
        cout << label(start_Knoten);
    }
    else
    {
        cout << label(start_Knoten);
        int aktuellerKnoten = start_Knoten;
        for (const DirectedEdge &e : pfad)
        {
            int next = e.to();
            cout << " -> " << label(next);
            aktuellerKnoten = next;
        }
    }
    cout << "\n%Pfad: ";
    if (pfad.empty())
    {
        cout << label(start_Knoten);
    }
    else
    {
        cout << label(start_Knoten);
        int aktuellerKnoten = start_Knoten;
        for (const DirectedEdge &e : pfad)
        {
            int next = e.to();
            cout << " [" << (int)e.weight() << "] -> " << label(next);
            aktuellerKnoten = next;
        }
    }
    cout << "\nKosten: " << (int)dijkstra.distTo(ziel_Knoten) << "\n";
}

// Gibt die Adjazenzliste des Graphen aus, für jeden Knoten alle Nachbarn und deren Gewichte
void printAdjazenzliste(const EdgeWeightedGraph &G)
{
    int n = G.getV();           // Anzahl der Knoten im Graphen
    for (int i = 0; i < n; i++) // Für jeden Knoten
    {
        char nodeChar = ('A' + i);             // Buchstabenbezeichnung für den Knoten (A, B, ...)
        cout << nodeChar;                      // Knoten ausgeben
        const vector<Edge> &adj = G.getAdj(i); // Alle Nachbarkanten des Knotens holen
        for (int j = 0; j < (int)adj.size(); ++j)
        {
            const Edge &e = adj[j];                              // Kante zum Nachbarn
            int w = e.other(i);                                  // Nachbarknoten bestimmen
            char wChar = ('A' + w);                              // Buchstabenbezeichnung für Nachbarknoten
            cout << "-> " << wChar << "[" << e.weight() << "] "; // Nachbar und Gewicht ausgeben
        }
        cout << endl; // Zeilenumbruch nach jedem Knoten
    }
}

// Menüfunktion zum Löschen einer Kante, Benutzereingabe für Knoten und Gewicht
void menuKanteLoeschen(EdgeWeightedGraph *G)
{
    int v, w;                                            // Knoten v und w
    double weight;                                       // Gewicht der Kante
    cout << "Kante loeschen: Knoten1 Knoten2 Gewicht: "; // Benutzer nach Knoten und Gewicht fragen
    cin >> v >> w >> weight;                             // Einlesen der Werte
    if (G->del_Edge(Edge(v, w, weight)))                 // Kante löschen, falls vorhanden
        cout << "Kante geloescht!\n";
    else
        cout << "Kante nicht gefunden!\n";
}

// Menüfunktion zum Hinzufügen einer Kante, Benutzereingabe für Knoten und Gewicht
void menuKanteHinzufuegen(EdgeWeightedGraph *G)
{
    int v, w;                                               // Knoten v und w
    double weight;                                          // Gewicht der Kante
    cout << "Kante hinzufuegen: Knoten1 Knoten2 Gewicht: "; // Benutzer nach Knoten und Gewicht fragen
    cin >> v >> w >> weight;                                // Einlesen der Werte
    G->add(Edge(v, w, weight));                             // Kante hinzufügen
    cout << "Kante hinzugefuegt!\n";
}

// Hauptfunktion: Steuert das Menü und die Programmlogik
int main()
{
    bool eingelsen = false;
    runTests();
    EdgeWeightedGraph *G = nullptr;
    string graphFiles[3] = {"graph1.txt", "graph2.txt", "graph3.txt"};
    while (true)
    {
        int auswahl = 0;
        showMenu();
        // Benutzereingabe für Menüauswahl mit Validierung
        do
        {
            cin >> auswahl;
            if (cin.fail() || auswahl < 1 || auswahl > 10)
            {
                printInputError("Bitte eine Zahl zwischen 1 und 10 eingeben!\n> ");
                continue;
            }
            break;
        } while (true);
        if (auswahl == 1)
        {
            menuGraphEinlesen(G, graphFiles, eingelsen);
        }
        if (!eingelsen)
        {
            cout << "Bitte zuerst einen Graph einlesen!\n";
            continue;
        }
        if (auswahl == 2)
        {
            menuTiefensuche(G);
        }
        else if (auswahl == 3)
        {
            menuBreitensuche(G);
        }
        else if (auswahl == 4)
        {
            menuPrim(G);
        }
        else if (auswahl == 5)
        {
            menuKruskal(G);
        }
        else if (auswahl == 6)
        {
            menuDijkstra(G);
        }
        else if (auswahl == 7)
        {
            printAdjazenzliste(*G);
        }
        else if (auswahl == 8)
        {
            menuKanteLoeschen(G);
        }
        else if (auswahl == 9)
        {
            menuKanteHinzufuegen(G);
        }
        else if (auswahl == 10)
        {
            break;
        }
    }
    system("pause");
    return 0;
}