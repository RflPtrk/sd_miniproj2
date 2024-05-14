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

//Wstawienie nowego elementu do kolejki
void priority_queue_list::insert(int elem, int priori)
{
	node* new_node = new node(elem, priori);

	// Jeśli kolejka jest pusta lub nowy element ma większy priorytet niż front, wstawiamy go na początek
	if (front == nullptr || priori > front->priority) {
		new_node->next = front;
		front = new_node;
	}
	else {
		node* current = front;
		// Szukamy odpowiedniego miejsca w kolejce, gdzie nowy element będzie miał mniejszy priorytet niż następny element
		while (current->next != nullptr && current->next->priority >= priori) {
			current = current->next;
		}
		// Wstawiamy nowy element pomiędzy obecnego i jego następnika
		new_node->next = current->next;
		current->next = new_node;
	}
	size++;
}

//Usuniecie elementu o najwiekszym priorytecie
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

//Podejrzenie elementu o najwiekszym priorytecie
int priority_queue_list::peek() const
{
	if (front == nullptr) {
		std::cerr << "The queue is empty." << std::endl;
		return -1;
	}
	return front->value;
}

//Zmiana priorytetu wybranego elementu
void priority_queue_list::modify_key(int elem, int new_priori)
{
	if (front == nullptr) {
		std::cout << "The queue is empty." << std::endl;
		return;
	}
	node* current = front;	//Utworzenie wezla iteratora
	//Przejscie przez kolejki do momentu odnalezienia danego wezla lub do konca kolejki
	while (current != nullptr) {
		if (current->value == elem) {
			current->priority = new_priori;	//Nadanie nowego priorytetu
			return;
		}
		current = current->next;
	}
	std::cout << "The element of inputted value doesn't exist in this queue." << std::endl;
}

//Wypisanie kolejki
void priority_queue_list::print() const
{
	if (front == nullptr) {
		std::cout << "The queue is empty." << std::endl;
		return;
	}
	node* current = front; //Utworzenie wezla iteratora
	std::cout << "The queue's contents: ";
	while (current != nullptr) {
		std::cout << "(" << current->value << ", " << current->priority << ") "; //Wypisanie danych obecnego wezla
		current = current->next;	//Przejscie do nastepnego wezla
	}
	std::cout << std::endl;
}

//Sprawdzenie czy kolejka jest pusta
bool priority_queue_list::is_empty() const
{
	return front==nullptr;
}

//Podejrzenie najwyzszego priorytetu (pomocnicze)
int priority_queue_list::peek_priori() const
{
	if (front == nullptr) {
		std::cerr << "The queue is empty." << std::endl;
		return -1;
	}
	return front->priority;
}
