#include <iostream>
#include "StackBasedOnLinkedList.h"
using namespace std;

template <typename T>
LinkedListStack<T>::LinkedListStack() {
	this->count = 0;
	this->head = new LinkedNode;
	this->head->next = nullptr;
}

template <typename T>
LinkedListStack<T>::~LinkedListStack() {
	LinkedNode *ptr, *temp;

	ptr = head;
	while (nullptr != ptr->next) {
		temp = ptr->next;
		ptr->next = temp->next;
		delete temp;
	}

	delete head;
	this->head = nullptr;
	this->count = 0;
}

template <typename T>
void LinkedListStack<T>::push(const T &data) {
	LinkedNode *ptr = new LinkedNode;
	ptr->data = data;
	ptr->next = this->head->next;
	head->next = ptr;
	this->count++;
}

template<typename T> 
T LinkedListStack<T>::peek()
{
    if(this->count == 0 || this->head->next == NULL){
        return nullptr;
    }
    else{
        return this->head->next->data;
    }
}

template<typename T>
T LinkedListStack<T>::pop()
{
    if(this -> count == 0 || this -> head -> next == NULL){
        return nullptr;
    } else{
        LinkedNode * temp = this->head->next;
        this->head->next = temp->next;
        T data = temp -> data;
        delete temp;
        this -> count --;
        return  data;
    }

}

template<typename T>
int LinkedListStack<T>::size() const
{
    return this->count;
}  
