#pragma once

#include <iostream>
#include "Edge.h"

class EdgeHeap{
public:

	EdgeHeap() {
		heap_length = 0;
		rootPointer = nullptr;
	};
	~EdgeHeap() {
		delete[] rootPointer;
	};

	void display();
	void push(Edge* e);
	Edge* pop();

	int heap_length;

private:
	Edge** rootPointer;

	void heapifyUp(int i);
	void heapifyDown(int i);
	void display(std::string sp, std::string sn, int from);
};