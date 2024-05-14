#include "priority_queue_heap.h"
#include <iostream>

void priority_queue_heap::swap(node& x, node& y) //Zamiana zawartosci dwoch wezlow
{
	node temp = x;
	x = y;
	y = temp;
}

void priority_queue_heap::double_heap_size() //Podwojenie rozmiaru tablicy kopca
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

void priority_queue_heap::heapify_up(int index)
{
	int parent_index = (index - 1) / 2;
	while (index > 0 && heap_array[parent_index].priori < heap_array[index].priori) {
		swap(heap_array[parent_index], heap_array[index]);
		index = parent_index;
		parent_index = (index - 1) / 2;
	}
}

void priority_queue_heap::heapify_down(int index)
{
	int left_child = 2 * index + 1;
	int right_child = 2 * index + 2;
	int largest = index;

	if (left_child<size && heap_array[right_child].priori>heap_array[largest].priori) {
		largest = left_child;
	}
	if (right_child<size && heap_array[right_child].priori>heap_array[largest].priori) {
		largest = right_child;
	}
	if (largest != index) {
		swap(heap_array[index], heap_array[largest]);
		heapify_down(largest);
	}
}

void priority_queue_heap::insert(int elem, int priori)
{
	if (size == capacity) {
		double_heap_size();
	}
	heap_array[size].elem = elem;
	heap_array[size].priori = priori;
	heapify_up(size);
	size++;
}

int priority_queue_heap::extract_max()
{
	if (size <= 0) {
		std::cout << "Heap underflow!" << std::endl;
		return -1;
	}
	node max = heap_array[0];
	heap_array[0] = heap_array[size - 1];
	size--;
	heapify_down(0);
	return max.elem;
}

int priority_queue_heap::peek() const
{
	if (size <= 0) {
		std::cout << "Heap underflow!" << std::endl;
		return -1;
	}
	return heap_array[0].elem;
}

void priority_queue_heap::modify_key(int elem, int new_priori)
{
	int index = -1;
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
	if (new_priori > old_priori) { heapify_up(index); }
	else if (new_priori < old_priori) { heapify_down(index); }
}

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

bool priority_queue_heap::is_empty() const
{
	return size==0;
}
