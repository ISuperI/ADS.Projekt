#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>
#include <queue>

namespace Graphsearch
{

	/**
	 * Fuehrt eine rekursive Tiefensuche im Graphen G,
	 * ab dem Knoten v aus und markiert alle besuchten
	 * Knoten in marked.
	 * Alle besuchten Knoten werden ausgegeben.
	 *
	 * \param[in]	 G			Graph
	 * \param[in]	 v			Startknoten
	 * \param[in/out] marked		Bereits besuchte Knoten
	 * \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
	 */
	void DFS_recursive(const EdgeWeightedGraph &G, int v, std::vector<bool> &marked, std::vector<int> &edgeTo)
	{
		marked[v] = true;
		for (const Edge &e : G.getAdj(v))
		{
			int w = e.other(v);
			if (!marked[w])
			{
				edgeTo[w] = v;
				DFS_recursive(G, w, marked, edgeTo);
			}
		}
	}

	/**
	 * Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
	 * Alle besuchten Knoten werden ausgegeben.
	 * Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
	 *
	 * \param[in]  G			Graph
	 * \param[out] marked	Bereits besuchte Knoten
	 * \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
	 * \param[in]  v			Startknoten
	 * \return	  true		Graph ist zusammenhaengend
	 *			  false		Graph ist nicht zusammenhaengend
	 */

	bool DFS(const EdgeWeightedGraph &G, int v, std::vector<bool> &marked, std::vector<int> &edgeTo)
	{
		int n = G.getV();
		marked.assign(n, false);
		edgeTo.assign(n, -1);
		DFS_recursive(G, v, marked, edgeTo);
		// Prüfe, ob alle Knoten besucht wurden (zusammenhängend)
		for (bool m : marked)
		{
			if (!m)
				return false;
		}
		return true;
	}

	/**
	 * Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
	 * Alle besuchten Knoten werden ausgegeben.
	 *
	 * \param[in]  G			Graph
	 * \param[in]  v			Startknoten
	 * \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
	 * \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
	 * \return	  true		Graph ist zusammenhaengend
	 *			  false		Graph ist nicht zusammenhaengend
	 */
	bool BFS(const EdgeWeightedGraph &G, int v, std::vector<bool> &marked, std::vector<int> &edgeTo)
	{
		int n = G.getV();
		marked.assign(n, false);
		edgeTo.assign(n, -1);
		std::queue<int> q;
		marked[v] = true;
		q.push(v);
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			for (const Edge &e : G.getAdj(u))
			{
				int w = e.other(u);
				if (!marked[w])
				{
					marked[w] = true;
					edgeTo[w] = u;
					q.push(w);
				}
			}
		}
		// Prüfe, ob alle Knoten besucht wurden (zusammenhängend)
		for (bool m : marked)
		{
			if (!m)
				return false;
		}
		return true;
	}
}
