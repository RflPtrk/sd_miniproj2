#include "priority_queue_list.h"
#include <iostream>
priority_queue_list::~priority_queue_list()
{
	while (front != nullptr) {
		node* temp = front;
		front = front->next;
		delete temp;
	}
}

void priority_queue_list::insert(int elem, int priori)
{
	node* new_node = new node(elem, priori);

	// Jeœli kolejka jest pusta lub nowy element ma wiêkszy priorytet ni¿ front, wstawiamy go na pocz¹tek
	if (front == nullptr || priori > front->priority) {
		new_node->next = front;
		front = new_node;
	}
	else {
		node* current = front;
		// Szukamy odpowiedniego miejsca w kolejce, gdzie nowy element bêdzie mia³ mniejszy priorytet ni¿ nastêpny element
		while (current->next != nullptr && current->next->priority >= priori) {
			current = current->next;
		}
		// Wstawiamy nowy element pomiêdzy obecnego i jego nastêpnika
		new_node->next = current->next;
		current->next = new_node;
	}
	size++;
}

int priority_queue_list::extract_max()
{
	if (front == nullptr) {
		std::cout << "The queue is empty." << std::endl;
		return -1;
	}
	node* temp = front;
	int deleted_data = temp->value;
	front = front->next;
	delete temp;
	size--;
	return deleted_data;
}

int priority_queue_list::peek() const
{
	if (front == nullptr) {
		std::cerr << "The queue is empty." << std::endl;
		return -1;
	}
	return front->value;
}

void priority_queue_list::modify_key(int elem, int new_priori)
{
	if (front == nullptr) {
		std::cout << "The queue is empty." << std::endl;
		return;
	}
	node* current = front;
	while (current != nullptr) {
		if (current->value == elem) {
			current->priority = new_priori;
			return;
		}
		current = current->next;
	}
	std::cout << "The element of inputted value doesn't exist in this queue." << std::endl;
}

void priority_queue_list::print() const
{
	if (front == nullptr) {
		std::cout << "The queue is empty." << std::endl;
		return;
	}
	node* current = front;
	std::cout << "The queue's contents: ";
	while (current != nullptr) {
		std::cout << "(" << current->value << ", " << current->priority << ") ";
		current = current->next;
	}
	std::cout << std::endl;
}
