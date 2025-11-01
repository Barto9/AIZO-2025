#pragma once

#include <iostream>
#include "Vertice.h"

class VerticeHeap {
public:

	VerticeHeap() {
		heap_length = 0;
		rootPointer = nullptr;
	};
	~VerticeHeap() {
		delete[] rootPointer;
	};

	void display();
	void push(Vertice* e);
	Vertice* pop();
	void heapifyDown(int i);

	int heap_length;

private:
	Vertice** rootPointer;

	void heapifyUp(int i);
	void display(std::string sp, std::string sn, int from);
};

