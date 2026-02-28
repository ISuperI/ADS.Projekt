#include "KruskalMST.h"
#include <algorithm>

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
    int n = G.getV(); // Anzahl der Knoten im Graphen
    treeID.resize(n); // Array für die Baum-IDs initialisieren (jeder Knoten bekommt eine eigene ID)
    for (int v = 0; v < n; ++v)
        treeID[v] = v;                   // Anfangs ist jeder Knoten sein eigener Baum
    mst.clear();                         // MST-Kantenliste leeren
    std::vector<Edge> edges = G.edges(); // Alle Kanten des Graphen holen
    std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
              { return a.weight() < b.weight(); }); // Kanten nach Gewicht sortieren (aufsteigend)
    for (int i = 0; i < edges.size(); ++i)          // Über alle Kanten der Reihe nach iterieren
    {
        const Edge &e = edges[i]; // Aktuelle Kante
        int v = e.either();       // Ersten Knoten der Kante holen
        int w = e.other(v);       // Zweiten Knoten der Kante holen
        if (treeID[v] != treeID[w])
        {                          // Prüfen, ob die Knoten in verschiedenen Bäumen liegen (kein Kreis)
            mst.push_back(e);      // Kante zum MST hinzufügen
            int oldID = treeID[w]; // Die alte Baum-ID, die ersetzt werden soll
            int newID = treeID[v]; // Die neue Baum-ID
            for (int j = 0; j < n; ++j)
            { // Alle Knoten, die zur alten Baum-ID gehören, bekommen die neue ID
                if (treeID[j] == oldID)
                    treeID[j] = newID;
            }
        }
        if (mst.size() == n - 1)
            break; // Wenn MST vollständig ist (n-1 Kanten), abbrechen
    }
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
    return mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
    double sum = 0.0;
    for (int i = 0; i < mst.size(); ++i) // Über alle Kanten im MST iterieren
        sum += mst[i].weight();          // Gewicht der Kante aufsummieren
    return sum;                          // Gesamtsumme zurückgeben
}
