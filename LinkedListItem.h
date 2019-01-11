#ifndef LINKEDLISTITEM_H
#define LINKEDLISTITEM_H

#include <memory>

template<class T>
class TLinkedListItem{
public:
    TLinkedListItem(const T &item);
    template<class A> friend std::ostream& operator<<(std::ostream& os, const TLinkedListItem<A>& obj);
    
    TLinkedListItem<T>* SetNext(TLinkedListItem<T>* next);
    TLinkedListItem<T>* GetNext();
    void SetPrev(TLinkedListItem<T>* prev);
    TLinkedListItem<T>* GetPrev();
    T GetFigure();
    
    virtual ~TLinkedListItem();
private:
    T item;
    TLinkedListItem<T> *next, *prev;
};

#endif
