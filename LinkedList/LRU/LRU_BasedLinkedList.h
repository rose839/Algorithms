#ifndef LRU_BASEDLINKEDLIST_H
#define LRU_BASEDLINKEDLIST_H

typedef int DataType;

class SNode {
public:
	DataType data;
	SNode *next;
};

class SList {
public:
	SList();
	SList(int MaxSize);
	~SList();
	void insert_elem_at_begin(DataType x);
	bool find_elem(DataType x);
	void delete_elem_at_end();
	bool delete_elem(DataType x);
	bool is_empty();
	bool is_full();

private:
	int MaxSize;
	int length;
	SNode *head;
};

#endif
