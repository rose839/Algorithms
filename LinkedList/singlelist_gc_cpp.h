#ifndef SINGLELIST_GC_CPP_H
#define SINGLELIST_GC_CPP_H

#include <memory>

template <typename T>
struct Node {
	using ptr_t = std::shared_ptr<Node<T>>;

	T data;
	ptr_t next;

	Node(T data_) : data(data_), next(nullptr) {}
	Node() : next(nullptr) {}
};

/* traverse single list */
template <typename T, typename UnaryFunc>
void traverse(typename Node<T>::ptr_t head, UnaryFunc do_traverse) {
	auto sentry = std::make_shared<Node<T>>();

	sentry->next = head;
	decltype(sentry)work = sentry;
	while (work = work->next) {
		do_traverse(work);
	}
}

/* reverse single list */
template <typename T>
typename Node<T>::ptr_t reverse(typename Node<T>::ptr_t head) {
	if (nullptr == head || nullptr == head->next) {
		return head;
	}

	decltype(head) prev = nullptr, curr = head; next = head->next;
	while (nullptr != next) {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = curr->next;
    }
    curr->next = prev;
    return curr;
}

template <typename T>
bool check_circle(typename Node<T>::ptr_t head) {
	if (nullptr == head or nullptr == head->next) {
        return false;
    }

	decltype(head) slow = head, fast = head;
    while (nullptr != fast and nullptr != fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

/* delete the last k element */
template <typename T>
typename Node<T>::ptr_t deleth_last_Kth(typename Node<T>::ptr_t head,
                                                         size_t n) {
    decltype(head) sentry = std::make_shared<Node<T>>();
    sentry->next = head;
    decltype(head) prev = sentry, curr = sentry->next, fast = sentry->next;
    for (size_t i = 0; i != n; ++i) {
        if (nullptr != fast) {
            fast = fast->next;
        } else {
            return sentry->next;
        }
    }
    while (nullptr != fast) {
        prev = curr;
        curr = curr->next;
        fast = fast->next;
    }
    prev->next = curr->next;
    return sentry->next;
}

template <typename T>
typename Node<T>::ptr_t find_middle_node(typename Node<T>::ptr_t head) {
    if (nullptr == head or nullptr == head->next) {
        return head;
    }
    decltype(head) slow = head, fast = head;
    while (nullptr != fast and nullptr != fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return nullptr;
        }
    }
    return slow;
}

#endif