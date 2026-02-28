#include <assert.h>
#include <limits>
#include "DijkstraSP.h"

/**
 * Entspannt alle ausgehenden Kanten vom Knoten v im Graphen G.
 * Aktualisiert die kürzesten Distanzen und Vorgängerkanten, falls ein besserer Pfad gefunden wird.
 *
 * @param[in] G Kantengewichteter gerichteter Graph
 * @param[in] v Knoten, von dem aus die Kanten entspannt werden
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
    // Für alle ausgehenden Kanten von v
    for (const DirectedEdge &e : G.getAdj(v))
    {
        int w = e.to();
        // Wenn ein kürzerer Pfad gefunden wurde
        if (distToVect[w] > distToVect[v] + e.weight())
        {
            distToVect[w] = distToVect[v] + e.weight();
            edgeTo[w] = e;
            pq.push(w, distToVect[w]);
        }
    }
}

/**
 * Konstruktor: Führt den Dijkstra-Algorithmus ab Startknoten s auf dem Graphen G aus.
 * Initialisiert alle Distanzen und Vorgängerkanten und berechnet die kürzesten Wege.
 *
 * @param[in] G Kantengewichteter gerichteter Graph
 * @param[in] s Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
    int n = G.getV();
    distToVect.assign(n, std::numeric_limits<double>::infinity());
    distToVect[s] = 0.0;
    edgeTo.clear();
    pq = Utils::PriorityQueue<int>();
    pq.push(s, 0.0);
    while (!pq.empty())
    {
        int v = pq.pop_top();
        relax(G, v);
    }
}

/**
 * Gibt die berechnete Distanz vom Startknoten s zum Knoten v zurück.
 *
 * @param[in] v Zielknoten
 * @return Kürzeste Distanz von s nach v, oder unendlich falls kein Pfad existiert
 */
double DijkstraSP::distTo(int v) const
{
    if (v < 0 || v >= (int)distToVect.size())
        return std::numeric_limits<double>::infinity();
    return distToVect[v];
}

/**
 * Prüft, ob ein Pfad vom Startknoten s zum Knoten v existiert.
 *
 * @param[in] v Zielknoten
 * @return true, wenn ein Pfad existiert, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
    if (v < 0 || v >= (int)distToVect.size())
        return false;
    return distToVect[v] < std::numeric_limits<double>::infinity();
}

/**
 * Gibt den kürzesten Pfad vom Startknoten s zum Knoten v als Vektor von Kanten zurück.
 *
 * @param[in] v Zielknoten
 * @return Vektor mit allen Kanten des Pfades von s nach v (leerer Vektor, falls kein Pfad existiert)
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
{
    std::vector<DirectedEdge> path;
    if (!hasPathTo(v))
        return path;
    for (int x = v; edgeTo.count(x); x = edgeTo[x].from())
    {
        path.insert(path.begin(), edgeTo[x]);
        if (edgeTo[x].from() == x)
            break;
    }
    return path;
}
