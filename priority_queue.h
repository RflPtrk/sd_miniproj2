#pragma once
class priority_queue {
public:
	virtual ~priority_queue() {}

	virtual void insert(int elem, int priori) = 0;
	virtual int extract_max() = 0;
	virtual int peek() const = 0;
	virtual void modify_key(int elem, int new_priori) = 0;
	virtual int return_size() const = 0;

	virtual void print() const = 0;
	virtual bool is_empty() const = 0;
	virtual int peek_priori()const = 0;
};
