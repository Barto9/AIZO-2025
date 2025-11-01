#pragma once

#include "EdgeHeap.h"
#include "List.h"
#include "DisjointSets.h"
#include <string>

class IncidencyMatrix
{
public:
	IncidencyMatrix() {
		graph_order = 0;
		graph_size = 0;
		incMatrix = nullptr;
		last_edge = 0;
	};

	~IncidencyMatrix() {
		deallocate();
	};

	void display();
	void allocate(int size, int order);
	void addEdge(int v1, int v2, int weight, int directed);

	List* mst_kruskal();
	List* mst_prim();

	std::string spp_dijkstra(int vp, int vk);

private:
	int graph_order;
	int graph_size;

	int** incMatrix;

	int last_edge;

	void deallocate();

	std::string pad(std::string string);
};

