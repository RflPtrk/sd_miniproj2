#pragma once
#include "priority_queue.h"
#include "node.h"

class priority_queue_list : public priority_queue {
private:
	node* front;
	int size;

public:
	priority_queue_list() : front(nullptr), size(0) {}
	~priority_queue_list();
	void insert(int elem, int priori)override;
	int extract_max()override;
	int peek()const override;
	void modify_key(int elem, int new_priori)override;
	int return_size()const override { return size; }
	void print() const override;
	int peek_priori();
};
