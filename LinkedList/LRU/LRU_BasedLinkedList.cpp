#include <iostream>
#include "LRU_BasedLinkedList.h"

using namespace std;

SList::SList() {
	head = new SNode;
	head->next = NULL;
	this->MaxSize = 10;
	this->length = 0;
}

SList:: SList(int MaxSize) {
	head = new SNode;
	head->next = NULL;
	this->MaxSize = MaxSize;
	this->length = 0;
}

SList::~ SList() {
	SNode *ptr, *temp;

	ptr = head;
	while(ptr->next != NULL) {
		temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
	}
	delete head;

	head = NULL;
	this->head = NULL;
	this->length = 0;
}

void SList::insert_elem_at_begin(DataType x) {
	SNode *ptr = new SNode;

	ptr->data = x;

	ptr->next = head->next;
	head->next = ptr;

	this->length++;
}

bool SList::find_elem(DataType x) {
	SNode *ptr;

	ptr = head;
	while (ptr->next != NULL) {
		if (ptr->next->data == x) {
			return true;
		}
		ptr = ptr->next;
	}
	return 0;
}

void SList::delete_elem_at_end() {
	SNode *ptr, *temp;

	ptr = head;
	while (ptr->next != NULL && ptr->next->next != NULL) {
		ptr = ptr->next;
	}

	temp = ptr->next;
	ptr->next = temp->next;
	this->length--;
	delete temp;

	return;
}

bool SList::delete_elem(DataType x) {
	SNode *ptr, *temp;

	ptr = head;
	while(ptr->next != NULL ) {
		if (ptr->next->data == x) {
			temp = ptr->next;
			ptr->next = temp->next;

			delete temp;
			this->length--;
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

bool SList::is_empty() {
	if (this->length == 0) {
		return true;
	} else {
		return false;
	}
}

bool SList::is_full() {
	if (this->length == this->MaxSize) {
		return true;
	} else {
		return false;
	}
}
