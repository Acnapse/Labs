#include "LinkedList.h"

template<class T>
TLinkedList<T>::TLinkedList() : head(nullptr), last(nullptr), count(0) {}

template<class T>
std::ostream& operator<< (std::ostream& os, const TLinkedList<T>& list) {

	std::shared_ptr<TLinkedListItem<T>> item = list.head;

	while(item != nullptr) {
		os << *item;
		item = item->GetNext();
	}

	return os;
}

template<class T>
bool TLinkedList<T>::empty() {
	return head == nullptr;
}

template<class T>
size_t TLinkedList<T>::Size() {
    return count;
}

template<class T>
void TLinkedList<T>::popFront() {
	if (head != nullptr){
        auto *tmp = head;
		head = head->GetNext();
        delete tmp;
        --count;
	}
    return;
}

template<class T>
T TLinkedList<T>::popBack() {
    T result;
    if (!empty()) {
        result = last -> GetFigure();
        if (head != last) {
            last = last -> GetPrev();
            delete (last -> SetNext(nullptr));
            --count;
            return result;
        }
        delete head;
        last = head = nullptr;
        --count;
    }
    return result;
}


template<class T>
void TLinkedList<T>::push_back(const T &figure) {
    TLinkedListItem<T> *new_element (new TLinkedListItem<T>(figure));
    if (empty()) last = head = new_element;
    else {
        last->SetNext(new_element);
        new_element -> SetPrev(last);
        last = new_element;
    }
    count++;
}

template<class T>
TLinkedList<T>::~TLinkedList(){
    delete head;
}

template class TLinkedList<void *>;







