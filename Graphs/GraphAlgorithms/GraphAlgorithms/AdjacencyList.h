#pragma once

#include <iostream>
#include <string>
#include "EdgeHeap.h"
#include "DisjointSets.h"
#include "List.h"
#include "VerticeHeap.h"

class List;

class AdjacencyList
{
public:
	struct ListNode {
		int id;	//nr wierzcho³ka
		int weight;		//waga krawêdzi prowadz¹cej do tego wierzcho³ka 
		ListNode* next;
	};

	AdjacencyList() {
		graph_order = 0;
		adjList = nullptr;
	};

	~AdjacencyList() {
		deallocate();
	};

	void display();
	void allocate(int order);
	void addEdge(int v1, int v2, int weight, bool directed);

	List* mst_kruskal();
	List* mst_prim();

	std::string spp_dijkstra(int vp, int vk);

private:
	int graph_order;
	ListNode** adjList;

	void deallocate();

	std::string pad(std::string string, int length);
};

