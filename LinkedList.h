#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedListItem.h"
#include <memory>

template <class T> 
class TLinkedList{
public:

	TLinkedList();

	void push_back(const T &figure);
	bool empty();
    size_t Size();

	void popFront();
    T popBack();
	template <class A> friend std::ostream& operator<<(std::ostream& os, const TLinkedList<A>& list);
	virtual ~TLinkedList();

private:
	TLinkedListItem<T> *head;
    TLinkedListItem<T> *last;
	size_t count;
};

#endif
