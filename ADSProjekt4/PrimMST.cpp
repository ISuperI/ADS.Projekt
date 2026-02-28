#include "PrimMST.h"

/**
 * Konstruktor: Erstellt einen MST für den gegebenen Graphen G mit dem Prim-Algorithmus ab Startknoten s
 *
 * @param[in] G Kantengewichteter Graph
 * @param[in] s Startknoten
 */
PrimMST::PrimMST(EdgeWeightedGraph G, int s)
{
	int n = G.getV();		 // Anzahl der Knoten im Graphen
	marked.assign(n, false); // Alle Knoten als unmarkiert initialisieren
	mst.clear();			 // MST-Kantenliste leeren
	while (!pq.empty())
		pq.pop(); // Priority Queue leeren

	visit(G, s); // Startknoten besuchen
	while (!pq.empty() && mst.size() < n - 1)
	{
		Edge e = pq.top();	// Kante mit kleinstem Gewicht holen
		pq.pop();			// Kante aus der Queue entfernen
		int v = e.either(); // Ein Endpunkt der Kante
		int w = e.other(v); // Anderer Endpunkt der Kante
		if (marked[v] && marked[w])
			continue;	  // Beide Enden schon im MST -> überspringen
		mst.push_back(e); // Kante zum MST hinzufügen
		if (!marked[v])
			visit(G, v); // Noch nicht besuchter Knoten besuchen
		if (!marked[w])
			visit(G, w);
	}
}

/**
 * Markiert Knoten v im Graphen G als besucht und fügt alle angrenzenden Kanten, die zu unbesuchten Knoten führen, zur Priority Queue hinzu
 *
 * @param[in] G Kantengewichteter Graph
 * @param[in] v Knoten im Graphen G
 */
void PrimMST::visit(EdgeWeightedGraph G, int v)
{
	marked[v] = true; // Knoten als besucht markieren
	for (const Edge &e : G.getAdj(v))
	{
		int w = e.other(v); // Nachbarknoten bestimmen
		if (!marked[w])
		{
			pq.push(e); // Kante zur Queue hinzufügen, falls Nachbar unbesucht
		}
	}
}

/**
 * Gibt alle Kanten des berechneten MST zurück
 *
 * @return Vektor mit den Kanten des MST
 */
std::vector<Edge> PrimMST::edges() const
{
	return mst;
}

/**
 * Berechnet die Summe aller Kantengewichte im MST
 *
 * @return Summe der Gewichte im MST
 */
double PrimMST::weight() const
{
	double sum = 0.0;
	for (const Edge &e : mst)
	{
		sum += e.weight(); // Gewicht der Kante zum Gesamtergebnis addieren
	}
	return sum;
}
