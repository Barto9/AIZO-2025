#include "List.h"
#include <string>

void List::push(Edge* e){

	if (e->weight == 0) {	//waga 0 oznacza brak krawêdzi
		return;
	}

	ListElement* newElement = new ListElement;
		newElement->edge = e;
		newElement->next = nullptr;

	if (headPointer == nullptr) {	//gdy lista jest pusta
		headPointer = newElement;
		headPointer->previous = nullptr;
		tailPointer = headPointer;
	}
	else {
		//przypisanie wskaŸników i przeniesienie tailPointer na dodany element
		tailPointer->next = newElement;
		newElement->previous = tailPointer;
		tailPointer = newElement;
	}
}

Edge* List::get() {		//zwraca jeszcze nie zwrócony element nie usuwaj¹c go z listy

	if (iterator = nullptr) {		//przejœcie ca³ej listy powoduje zwrócenie nullptr
		iterator = headPointer;		//wówczas iterator zaczyna od nowa
	}
	else {
		iterator = iterator->next;
	}
	return iterator->edge;
}

void List::deleteAll() {

	if (headPointer != nullptr) {

		ListElement* holder;

		while(headPointer->next != nullptr) {
			holder = headPointer->next;
			delete headPointer;
			headPointer = holder;
		}
		delete headPointer;
	}
}

std::string List::toString() {

	if (headPointer != nullptr) {
	
		ListElement* holder = headPointer;
		std::string result = "";

		do {
			result += 
				" [" + std::to_string(holder->edge->v1) + "-" + std::to_string(holder->edge->v2) +  "] "
				+ std::to_string(holder->edge->weight) + " ,";
			holder = holder->next;
		} while (holder != nullptr);

		return result;
	}
	return "Lista jest pusta";
}

int List::sumWeight() {
	int weight = 0;
	ListElement* holder = headPointer;

	while (holder != nullptr) {
		weight += holder->edge->weight;
		holder = holder->next;
	}

	return weight;
}