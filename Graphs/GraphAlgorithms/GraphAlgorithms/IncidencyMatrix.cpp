#include "IncidencyMatrix.h"
#include "VerticeHeap.h"



void IncidencyMatrix::display()
{
	std::cout << "Graf w reprezentacji macierzowej: \n";
	for (int i = 0; i < graph_order; i++) {
		std::cout << i;
		for (int j = 0; j < graph_size; j++) {
			std::cout << "  " << pad(std::to_string(incMatrix[i][j]));
		}
		std::cout << "\n";
	}
}
std::string IncidencyMatrix::pad(std::string string) {
	std::string padding = " ";
	std::string result = string;
	int size = 3 - string.length();
	if (size < 0)
	{
		return "  ";
	}
	for (int i = 0; i < size; i++)
	{
		result = padding + result;
	}
	return result;
}

void IncidencyMatrix::allocate(int size, int order)
{
	deallocate();

	graph_size = size;
	graph_order = order;

	incMatrix = new int* [graph_order];
	for (int i = 0; i < graph_order; i++) {
		incMatrix[i] = new int[graph_size];
		for (int j = 0; j < graph_size; j++) {
			incMatrix[i][j] = 0;
		}
	}
}
void IncidencyMatrix::deallocate()
{
	for (int i = 0; i < graph_order; i++) {
		delete[] incMatrix[i];
	}
	delete[] incMatrix;

	graph_size = 0;
	graph_order = 0;
	last_edge = 0;
}

void IncidencyMatrix::addEdge(int v1, int v2, int weight, int directed)
{
	incMatrix[v1][last_edge] = weight;
	incMatrix[v2][last_edge++] = directed ? -weight : weight;
}

List* IncidencyMatrix::mst_kruskal()
{
	List* result = new List();

	//utworzenie kolejki priorytetowej krawêdzi
	EdgeHeap* minEdgeHeap = new EdgeHeap();
	Edge* e;
	bool first_added;	//flaga oznaczaj¹ca, czy ju¿ zosta³ dodany pierwszy wierzcho³ek
	for (int i = 0; i < graph_size; i++) {
		e = new Edge;
		first_added = false;
		for (int j = 0; j < graph_order; j++) {
			//jeœli w danej komórce nie ma '0' to dodaj wierzcho³ek
			if (e->weight = incMatrix[j][i]) {
				if (first_added) {
					e->v2 = j;
					break;		//jeœli zosta³y dodane oba wierzcho³ki mo¿na przejœæ do kolejnej krawêdzi
				}
				e->v1 = j;
				first_added = true;
			}
		}
		minEdgeHeap->push(e);
	}

	//zbiór roz³¹czny do "kolorowania" odwiedzonych wierzcho³ków
	DisjointSets* sets = new DisjointSets(graph_order);


	while (minEdgeHeap->heap_length > 0) {
		e = minEdgeHeap->pop();
		if (!sets->isOneSet(e->v1, e->v2)) {
			result->push(e);
			sets->unionSets(e->v1, e->v2);
		}
	}

	return result;
}

List* IncidencyMatrix::mst_prim()
{
	List* result = new List();

	//tablica pamiêtaj¹ca odwiedzone wierzcho³ki;
	bool* visited = new bool[graph_order];
	for (int i = 0; i < graph_order; i++) {
		visited[i] = false;
	}

	int currentNode = 0;	//wierzcho³ek pocz¹tkowy 0 !

	EdgeHeap* minEdgeHeap = new EdgeHeap();
	Edge* e = new Edge(0, 0, 0);
	do {
		if (!visited[currentNode]) {
			result->push(e);	//dodanie krawêdzi, któr¹ doszliœmy do currentNode do rozwi¹zania (krawêdzie o wadze 0 s¹ ignorowanê przez metodê List::push)
			for (int i = 0; i < graph_size; i++) {	//przejœcie po macierzy w poszukiwaniu krawêdzi incydentnych z currentNode
				if (incMatrix[currentNode][i] > 0) {
					for (int j = 0; j < graph_order; j++) {	//znalezienie drugiego wierzcho³ka
						if (j != currentNode && incMatrix[j][i] > 0) {
							e = new Edge;
							e->v1 = currentNode;
							e->v2 = j;
							e->weight = incMatrix[j][i];
							minEdgeHeap->push(e);
							break;
						}
					}
				}
			}
			visited[currentNode] = true;
		}

		e = minEdgeHeap->pop();
		currentNode = e->v2;

	} while (minEdgeHeap->heap_length > 0);

	return result;
}

std::string IncidencyMatrix::spp_dijkstra(int vp, int vk)
{
	VerticeHeap* minDistanceHeap = new VerticeHeap();
	Vertice** vertice = new Vertice * [graph_order];

	Vertice* v;
	for (int i = 0; i < graph_order; i++) {
		v = new Vertice;
		v->id = i;
		v->previous = nullptr;
		v->distance = i == vp ? 0 : 9999;	//odleg³oœæ pocz¹tkowego to 0, reszty "du¿a wartoœæ"
		minDistanceHeap->push(v);
		vertice[i] = v;
	}

	int old_dist, new_dist;
	while (minDistanceHeap->heap_length > 0) {
		v = minDistanceHeap->pop();

		for (int i = 0; i < graph_size; i++) {	//przejœcie po macierzy w poszukiwaniu krawêdzi wychodz¹cych z v
			if (incMatrix[v->id][i] > 0) {
				for (int j = 0; j < graph_order; j++) {	//znalezienie drugiego wierzcho³ka
					if (j != v->id && incMatrix[j][i] < 0) {

						old_dist = vertice[j]->distance;
						new_dist = v->distance + incMatrix[v->id][i];

						if (new_dist < old_dist) {	//jeœli nowa trasa jest krótsza nastêpuje relaksacja
							vertice[j]->distance = new_dist;
							vertice[j]->previous = v;
						}

						break;
					}
				}
			}
		}
		minDistanceHeap->heapifyDown(0);
	}

	v = vertice[vk];
	std::string result;
	do {
		result = "[" + std::to_string(v->id) + "] " + result;
		v = v->previous;
	} while (v != nullptr);

	v = vertice[vk];
	result += "\n Calkowity koszt sciezki: " + std::to_string(v->distance);

	return result;
}
