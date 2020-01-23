#ifndef LRU_BASEDLINKEDLIST_H
#define LRU_BASEDLINKEDLIST_H

typedef int DataType;

template <typename T>
class SNode {
public:
	DataType data;
	SNode *next;
}

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
	void print_all();

	void *find_elem_optim(DataType x);
	void delete_elem_optim(void *snode);

private:
	int MaxSize;
	int length;
	SNode *head;
}

#endif