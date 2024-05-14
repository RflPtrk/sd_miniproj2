#pragma once
class node {
public:
	int value;
	int priority;
	node* next;

	node(int val, int priori) :value(val), priority(priori), next(nullptr) {}
};