#pragma once
#include "IncidencyMatrix.h"
#include "AdjacencyList.h"
#include "EdgeHeap.h"
#include "List.h"
#include <iostream>
#include <fstream>
#include "Edge.h"

class Graph
{
public:
	Graph() {
		matrix_rep = new IncidencyMatrix();
		list_rep = new AdjacencyList();
		graph = nullptr;
		size = 0;
		order = 0;
	};
	~Graph() {
		delete matrix_rep;
		delete list_rep;

		for (int i = 0; i < order; i++) {
			delete graph[i];
		}
		delete graph;
	};

	const int MAX_WEIGHT = 97;

	void display();
	
	void generateRandomGraph(int graph_order, int graph_density, bool directed);
	void loadFromFile(std::string filename);
	void init(bool directed);
	int minDensity(int graph_order, bool directed);

	void mst_kruskal();
	void mst_prim();
	void spp_dijkstra(int vp, int vk);

	// Methods for benchmarking - run algorithms on specific representation only
	void mst_prim_matrix();  // Prim's on matrix representation only
	void mst_prim_list();    // Prim's on list representation only
	void mst_kruskal_matrix(); // Kruskal's on matrix representation only
	void mst_kruskal_list();   // Kruskal's on list representation only
	void spp_dijkstra_matrix(int vp, int vk); // Dijkstra's on matrix representation only
	void spp_dijkstra_list(int vp, int vk);  // Dijkstra's on list representation only

	// Getters
	int getSize() const { return size; }
	int getOrder() const { return order; }

	IncidencyMatrix* matrix_rep;
	AdjacencyList* list_rep;

private:

	int size;
	int order;

	Edge** graph;

	void add_edge(int pos, int v1, int v2, int weight);

};

