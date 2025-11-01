#pragma once
class DisjointSets
{
public:
	DisjointSets(int n) {
		set_size = n;
		parent = new int[set_size];
		rank = new int[set_size];

		for (int i = 0; i < set_size; i++) {
			makeOwnSet(i);
		}
	};

	~DisjointSets() {
		delete[] parent;
		delete[] rank;
	};

	bool isOneSet(int x, int y);
	void unionSets(int x, int y);

private:
	//zbiory rozpoznawane s¹ przez wierzcho³ek, od którego siê zacz¹³ dany zbiór (root)
	int* parent;	//zbiór do którego nale¿y wierzcho³ek
	int* rank;		//wielkoœæ zbioru w którym siê znajduje wierzcho³ek
	int set_size;

	void makeOwnSet(int x);
	int findSetRoot(int x);
};

