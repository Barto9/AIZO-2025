#include "DisjointSets.h"

void DisjointSets::makeOwnSet(int x)
{
	parent[x] = x;
	rank[x] = 1;
}

int DisjointSets::findSetRoot(int x)
{
	//gdy zbiór nie pochodzi od tego wiercho³ka
	if (x != parent[x]) {
		//rekurencyjne wyszukanie rodzica
		parent[x] =  findSetRoot(parent[x]);	
		//przypisuje rodzica zbioru wierzcho³kom od x w kolejnoœci odwrotnej do do³¹czania
		//wierzcho³ki do³¹czone do x maj¹ pa rent[] = x, dlatego przy ka¿dej operacji nale¿y wywo³aæ tê funkcjê
	}
	return parent[x];
}

void DisjointSets::unionSets(int x, int y) 
{
	int setX = findSetRoot(x);	//x
	int setY = findSetRoot(y);	//x

	if(setX == setY) {	//elementy nale¿¹ do jednego zbioru
		return;
	}

	if (rank[setX] > rank[setY]) {	//wybór wiêkszego zbioru
		parent[setY] = setX;	//przepisanie ca³ego zbioru X do zbioru Y, poprzez zmianê rodzica wierzcho³ka od którego pochodzi zbiór
		rank[setX]++;
		rank[setY] = 0;
	}
	else {
		parent[setX] = setY;
		rank[setY]++;
		rank[setX] = 0;
	}
}

bool DisjointSets::isOneSet(int x, int y)
{
	return findSetRoot(x) == findSetRoot(y);
}


