#include <iostream>

using namespace std;

typedef int DataType;

struct TreeNode {
	DataType data;
	TreeNode *left = nullptr;
	TreeNode *right = nullptr;
};

class BinarySearchTree {
private:
	TreeNode *root;
	int num;

public:
	BinarySearchTree() : num(0) {
		root        = new TreeNode;
		root->left  = nullptr;
		root->right = nullptr
	}

	bool find(DataType it, TreeNode *root) {
		if (nullptr == root) {
			return false;
		}
		if (it == root->data) {
			return true;
		} else if (it > root->data) {
			return find(it, root->right);
		} else {
			return find(it, root->left);
		}
	}

	DataType get_max() {
		if (nullptr == root) {
			return -1;
		}
		
		TreeNode *tmp = root;
		while (tmp->right != nullptr) {
			tmp = tmp->right;
		}
		return tmp->data;
	}

	DataType get_min() {
		if (nullptr == root) {
			return -1;
		}
		
		TreeNode *tmp = root;
		while (tmp->left != nullptr) {
			tmp = tmp->left;
		}
		return tmp->data;
	}

	void insert_data(DataType it) {
		if (0 == num) {
			root->data = it;
			num++;
			return;
		}

		TreeNode *p = root;
		while (p != nullptr) {
			if (it < p->data) {
				if (nullptr == p->left) {
					p->left = new TreeNode;
					p->left->data = it;
					num++;
					return;
				}
				p = p->left;
			} else {
				if (nullptr == p->right) {
					p->right = new TreeNode;
					p->right->data = it;
					num++;
					return;
				}
				p = p->right;
			}
		}
	}

	DataType get_prenode(DataType it)
    {
        if (nullptr == root)
            return NULL;
        if (it == root->data)
            return NULL;
        TreeNode *p = root;
        TreeNode *pp = nullptr;
        while (p != nullptr) {
            if (p->data < it) {
                pp = p; 
                p = p->right;

            } else if (p->data > it) {
                pp = p; 
                p = p->left;
            } else {

                break;
            }
        }
        return ((nullptr == p) ? NULL : pp->data);
    }

    DataType get_postnode(DataType it)
    {
        if (nullptr == root)
            return -1;
        TreeNode *p = root;
        while (p != nullptr) {
            if (p->data < it) {
                p = p->right;
            } else if (p->data > it) {
                p = p->left;
            } else {
                break;
            }
        }
        if (nullptr == p) {
            return -1;
        } else if (p->left != nullptr) {
            return p->left->data;
        } else if (p->right != nullptr) {
            return p->right->data;
        } else {
            return NULL;
        }
    }

    void mid_order(TreeNode *rt)
    {
        if (nullptr == rt)
            return;
        mid_order(rt->left);
        cout << rt->data << '\t';
        mid_order(rt->right);
    }

    void order()
    {
        if (nullptr == root)
            return;
        return mid_order(root);
    }

    int get_high(TreeNode *rt)
    {
        int lhigh = 0;
        int rhigh = 0;
        if (nullptr == rt)
            return 0;
        lhigh = get_high(rt->left);
        rhigh = get_high(rt->right);
        return ((lhigh > rhigh) ? (lhigh + 1) : (rhigh + 1));
    }

    int high()
    {
        if (nullptr == root)
            return 1;
        return get_high(root);
    }

    void delet(DataType it)
    {
        if (NULL == root)
            return;
        TreeNode *p = root;
        TreeNode *pp = NULL;
        while (p != NULL && p->data != it) {
            pp = p;
            if (it > p->data)
                p = p->right;
            else
                p = p->left;
        }
        if (p == NULL)
            return; 
        
        if (p->left != NULL && p->right != NULL) {
            TreeNode *minP = p->right;
            TreeNode *minPP = p;       
            while (minP->left != NULL)
            {
                minPP = minP;
                minP = minP->left;
            }
            
            p->data = minP->data; 
            p = minP;
            pp = minPP;
        }

        TreeNode *child;
        if (p->left != NULL)
            child = p->left;
        else if (p->right != NULL)
            child = p->right;
        else
            child = NULL;

        if (NULL == pp)
            root = child;
        else if (p == pp->left)
            pp->left = child;
        else
            pp->right = child;
    }
};
