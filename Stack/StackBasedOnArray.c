#include <iostream>
#include "StackBasedOnArray.h"

using namespace std;

template <typename T>
ArrayStack<T>::ArrayStack() {
	this->cout = 10;
	this->elem_count = 0;
	this->array = new T[this->cout];
}

template<typename T>
ArrayStack<T>::ArrayStack(int count)
{
    this->count = count;
    this->elem_count = 0;
    this->array = new T[this->count];
}

template <typename T>
ArrayStack<T>::~ArrayStack(){
    this->count = 0;
    this->elem_count = 0;
    delete [] this->array;
} 

template<typename T> 
void ArrayStack<T>::push(T data) {
	if (this->elem_count == this->count) {
		this->count = int(1.5 * this->count);
		T *temp = new T[this->count];
		for (int i = 0; i < this->elem_count; i++) {
			temp[i] = this->array[i];
		}

		delete [] this->array;
		temp[this->elem_count] = data;
        this->elem_count ++;
        this->array = temp;
	} else {
		this->array [this->elem_count] = data;
        this->elem_count ++ ;
	}
}

template<typename T> 
T ArrayStack<T>::pop(){
    this->elem_count --;
    T temp = this->array[this->elem_count];
    return temp;
}

template<typename T> 
T ArrayStack<T>::peek(){
    T temp = this->array[this->elem_count - 1];
    return temp;
}

template<typename T> 
int ArrayStack<T>::stackSize(){
    return this->elem_count;
}

template<typename T> 
int ArrayStack<T>::stackMaxSize(){
    return this->count;
}

