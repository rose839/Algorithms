#ifndef STACK_BASED_ON_ARRAY_H
#define STACK_BASED_ON_ARRAY_H

template <typename T>
class ArrayStack {
public:
	ArrayStack();
	ArrayStack(int count);
	~ArrayStack();

	void push(T data);
	T pop();
	T peek();
	int stackSize();
	int stackMaxSize();

private:
	int elem_count;
	int count;
	T *array;
};

#endif