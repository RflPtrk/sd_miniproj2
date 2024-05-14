#include "priority_queue_heap.h"
#include <iostream>

//Zamiana zawartosci dwoch wezlow
void priority_queue_heap::swap(node& x, node& y)
{
	node temp = x;
	x = y;
	y = temp;
}

//Podwojenie pojemnosci tablicy kopca
void priority_queue_heap::double_heap_size()
{
	int new_capac = capacity * 2;
	node* new_heap_array = new node[new_capac];
	for (int i = 0; i < size; ++i) {
		new_heap_array[i] = heap_array[i];
	}
	delete[] heap_array;
	heap_array = new_heap_array;
	capacity = new_capac;
}

//Przywracanie własności kopca od wybranego indexu w góre
void priority_queue_heap::heapify_up(int index)
{
	int parent_index = (index - 1) / 2;		//wyznaczenie indeksu rodzica
	//przejscie przez petle do momentu dotarcia do korzenia kopca lub priorytet elementu biezacego jest mniejszy lub rowny priorytetowi rodzica
	while (index > 0 && heap_array[parent_index].priori < heap_array[index].priori) {
		swap(heap_array[parent_index], heap_array[index]);	//zamiana miejscami biezacego elementu z rodzicem
		index = parent_index;	//zmiana indeksu elementu biezacego na indeks rodzica
		parent_index = (index - 1) / 2;	//wyznaczenie nowego indeksu rodzica
	}
}

//Przywracanie własności kopca od wybranego indexu w dół
void priority_queue_heap::heapify_down(int index)
{
	int left_child = 2 * index + 1;
	int right_child = 2 * index + 2;
	int largest = index;	//tytul "largest" dla elementu o najwiekszym priorytecie (domyslnie rodzic)

	//jesli lewe dziecko istnieje i jego priorytet jest wiekszy niz rodzica to otrzymuje tytul "largest"
	if (left_child<size && heap_array[right_child].priori>heap_array[largest].priori) {
		largest = left_child;
	}
	//jesli prawe dziecko istnieje i jego priorytet jest wiekszy niz rodzica to otrzymuje tytul "largest"
	if (right_child<size && heap_array[right_child].priori>heap_array[largest].priori) {
		largest = right_child;
	}
	//jesli rodzic nie ma tytulu "largest" to zamienia sie miejscem z dzieckiem, ktore ma 
	if (largest != index) {
		swap(heap_array[index], heap_array[largest]);
		heapify_down(largest);	//rekurencyjne wywolanie funkcji, aby przywrocic wlasciwosc kopca w poddrzewie
	}
}

//Wstawienie nowego elementu do kolejki
void priority_queue_heap::insert(int elem, int priori)
{
	//podwojenie pojemnosci kopca jesli jest rowna rozmiarowi
	if (size == capacity) {
		double_heap_size();
	}
	//dodanie nowego elementu na ostatnie miejsce w kolejce
	heap_array[size].elem = elem;
	heap_array[size].priori = priori;
	heapify_up(size);	//wywolanie funkcji pomocniczej przywracajacej wlasnosci kopca
	size++;
}

//Usuniecie elementu o najwiekszym priorytecie
int priority_queue_heap::extract_max()
{
	if (size <= 0) {
		std::cout << "Heap underflow!" << std::endl;
		return -1;
	}
	node max = heap_array[0];	//zapisanie elementu o najwiekszym priorytecie, aby moc go zwrocic pod koniec metody
	heap_array[0] = heap_array[size - 1];	//nadpisanie pierwszego elementu kolejki ostatnim
	size--;	//usuniecie ostatniego elementu
	heapify_down(0);	//wywolanie funkcji pomocniczej przywracajacej wlasnosci kopca
	return max.elem;
}

//Podejrzenie elementu o najwiekszym priorytecie
int priority_queue_heap::peek() const
{
	if (size <= 0) {
		std::cout << "Heap underflow!" << std::endl;
		return -1;
	}
	return heap_array[0].elem;
}

//Zmiana priorytetu wybranego elementu
void priority_queue_heap::modify_key(int elem, int new_priori)
{
	int index = -1;
	//petla znajdujaca zadany element
	for (int i = 0; i < size; ++i) {
		if (heap_array[i].elem == elem) {
			index = i;
			break;
		}
	}
	if (index == -1) {
		std::cout << "Chosen element not found." << std::endl;
		return;
	}
	int old_priori = heap_array[index].priori;
	heap_array[index].priori = new_priori;
	//przywracanie wlasnosci kopca w odpowiednia strone w zaleznosci od tego co nowy priorytet jest wiekszy czy mniejszy od starego
	if (new_priori > old_priori) { heapify_up(index); }
	else if (new_priori < old_priori) { heapify_down(index); }
}

//Wypisanie kolejki
void priority_queue_heap::print() const
{
	if (size == 0) {
		std::cout << "Heap is empty." << std::endl;
		return;
	}
	std::cout << "Heap elements: " << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << "Value: " << heap_array[i].elem << ", Priority: " << heap_array[i].priori << std::endl;
	}
}

//Sprawdzenie czy kolejka jest pusta
bool priority_queue_heap::is_empty() const
{
	return size==0;
}

//Podejrzenie najwyzszego priorytetu (pomocnicze)
int priority_queue_heap::peek_priori() const
{
	if (size <= 0) {
		std::cout << "Heap underflow!" << std::endl;
		return -1;
	}
	return heap_array[0].priori;
}
