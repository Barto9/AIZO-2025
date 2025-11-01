#include "VerticeHeap.h"

//dodawanie nowego wierzcho³ka do kopca
void VerticeHeap::push(Vertice * v) {

    Vertice** newPointer = new Vertice * [heap_length + 1];

    for (int i = 0; i < heap_length; i++) {
        newPointer[i] = rootPointer[i];
    }

    newPointer[heap_length] = v;
    heap_length++;

    delete[] rootPointer;
    rootPointer = newPointer;

    heapifyUp(floor((heap_length - 2) / 2));
}

//usuwanie korzenia kopca
Vertice* VerticeHeap::pop() {

    Vertice* holder = rootPointer[0];

    rootPointer[0] = rootPointer[heap_length - 1];
    heap_length--;

    heapifyDown(0);

    return holder;
}

void VerticeHeap::heapifyUp(int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest;

    if (l < heap_length) {

        //sprawdzenie czy lewy potomek jest mniejszy od swojego ojca
        if (rootPointer[l]->distance < rootPointer[i]->distance) {
            smallest = l;
        }
        else {
            smallest = i;
        }

        //sprawdzenie czy prawy potomek jest mniejszy od ojca lub lewego potomka
        if (r < heap_length && rootPointer[r]->distance < rootPointer[smallest]->distance) {
            smallest = r;
        }

        //zamiana wartoœci miejscami
        if (smallest != i) {
            Vertice* holder;

            holder = rootPointer[i];
            rootPointer[i] = rootPointer[smallest];
            rootPointer[smallest] = holder;
        }
    }

    //metoda zostaje wywo³ana rekurencyjnie w kierunku korzenia, jeœli element 'i' nie by³ nim
    if (i > 0) { heapifyUp((i - 1) >> 1); }
}

void VerticeHeap::heapifyDown(int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l > 0 && l < heap_length) {

        //sprawdzenie czy lewy potomek jest mniejszy od swojego ojca
        if (rootPointer[l]->distance < rootPointer[i]->distance) {
            smallest = l;
        }

        if (heap_length > 2) {
            //sprawdzenie czy prawy potomek jest wiêkszy od swojego ojca
            if (r < heap_length && rootPointer[r]->distance < rootPointer[smallest]->distance) {
                smallest = r;
            }
        }

        //zamiana wartoœci miejscami
        if (smallest != i) {
            Vertice* holder;

            holder = rootPointer[i];
            rootPointer[i] = rootPointer[smallest];
            rootPointer[smallest] = holder;

            //metoda zostaje wywo³ana rekurencyjnie, gdy¿ zamiana pozycji mog³a spowodowaæ 
            //zaburzenie w³asnoœci kopca w danym poddrzewie
            heapifyDown(smallest);
        }
    }
}

void VerticeHeap::display()
{
    if (rootPointer != nullptr) {
        display("", "", 0);     //metoda rysuj¹ca kopiec

        std::cout << std::endl;

        //for (int i = 0; i < heap_length; i++) {     //wypisanie tablicowe kopca
        //    std::cout << rootPointer[i]->distance << ", ";
        //}
    }
    else {
        std::cout << "Kopiec jest pusty." << std::endl;
    }
}

void VerticeHeap::display(std::string sp, std::string sn, int from)
{
    std::string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;
    std::string s;

    if (from < heap_length)
    {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        display(s + cp, cr, 2 * from + 2);

        s = s.substr(0, sp.length() - 2);

        std::cout << s << sn << rootPointer[from]->distance << "\n";

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        display(s + cp, cl, 2 * from + 1);
    }
}