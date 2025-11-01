#pragma once

struct Edge {
	int v1, v2, weight;
	Edge() {};
	Edge(int v1, int v2, int weight) : v1(v1), v2(v2), weight(weight) {};
};