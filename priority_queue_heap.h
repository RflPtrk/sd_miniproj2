#pragma once
#include "priority_queue.h"

class priority_queue_heap :public priority_queue {
private:
	struct node {
		int elem;
		int priori;
	};
	node* heap_array;
	int size;
	int capacity;

	void swap(node& x, node& y);
	void double_heap_size();
	void heapify_up(int index);
	void heapify_down(int index);

public:
	priority_queue_heap() :size(0), capacity(1) {
		heap_array = new node[capacity];
	}

	~priority_queue_heap() { delete[] heap_array; }

	void insert(int elem, int priori)override;
	int extract_max()override;
	int peek()const override;
	void modify_key(int elem, int new_priori)override;
	int return_size()const override { return size; }
	void print() const override;
	bool is_empty() const override;
	int peek_priori()const override;
};
