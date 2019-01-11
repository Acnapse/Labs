#include "LinkedListItem.h"
#include <iostream>

template <class T> 
TLinkedListItem<T>::TLinkedListItem(const T &it) {
    this->item = (it);
    this->next = nullptr;
}

template<class T>
T TLinkedListItem<T>::GetFigure(){
    return this->item;
}

template <class T> 
TLinkedListItem<T>* TLinkedListItem<T>::SetNext(TLinkedListItem<T>* nxt) {
    TLinkedListItem <T> *old = this->next;
    this->next = nxt;
    return old;
}

template <class T> 
TLinkedListItem<T>* TLinkedListItem<T>::GetNext(){
    return this->next;
}

template <class T>
TLinkedListItem<T>* TLinkedListItem<T>::GetPrev() {
    return this -> prev;
}

template <class T>
void TLinkedListItem<T>::SetPrev(TLinkedListItem<T>* prev) {
    this -> prev = prev;
    return;
}


template <class T> 
TLinkedListItem<T>::~TLinkedListItem() {
    delete next;
}

template <class A> 
std::ostream& operator<<(std::ostream& os, const TLinkedListItem<A>& obj) {
    os << "[" << obj.item << "]" << std::endl;
    return os;
}

template class TLinkedListItem<void *>;
