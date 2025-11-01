#pragma once

#include "EdgeHeap.h"
#include "Edge.h"

class List{
public:
	struct ListElement {
		Edge* edge;
		ListElement* next;
		ListElement* previous;
	};

	List() {
		headPointer = nullptr;
		tailPointer = nullptr;
	}
	~List() {
		
	}

	void push(Edge* e);
	Edge* get();
	void deleteAll();

	std::string toString();
	int sumWeight();

private:
	ListElement* headPointer;
	ListElement* tailPointer;
	ListElement* iterator;
};