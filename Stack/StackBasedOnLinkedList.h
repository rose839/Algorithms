#ifndef STACK_BASED_LINKED_LIST_H
#define STACK_BASED_LINKED_LIST_H

template <typename T>
class LinkedListStack {
public:
	LinkedListStack();
	~LinkedListStack();

	void push(T &data);
	T pop();
	T peek();
	int size() const;

private:
	int count;
	struct LinkedNode {
		T data;
		LinkedNode *next;
	};
	LinkedNode *head;
};

#endif