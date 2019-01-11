#include "TList.hpp"
#include <exception>

template <class T> TList<T>::TList() : head(nullptr), last(nullptr), count(0) {}

template <class T>
void TList<T>::push(std::shared_ptr<T> item) {
    std::lock_guard<std::recursive_mutex> lock(list_mutex);
    std::shared_ptr<TListItem<T>> new_element (new TListItem<T>(item,&list_mutex));
    if (empty()) last = head = new_element;
    else {
        last->SetNext(new_element);
        new_element->SetPrev(last);
        last = new_element;
    }
    count++;
}

template <class T> std::shared_ptr<T> TList<T>::operator[](size_t i) {
    std::lock_guard<std::recursive_mutex> lock(list_mutex);
    if (i > Size() - 1) throw std::invalid_argument("index greater then list size");
    size_t j = 0;
    
    for (std::shared_ptr<T> a : * this) {
        if (j == i) return a;
        j++;
    }
    
    return std::shared_ptr<T>(nullptr);
}

template <class T>
bool TList<T>::empty() {
    std::lock_guard<std::recursive_mutex> lock(list_mutex);
    return head == nullptr;
}

template<class T>
std::shared_ptr<T> TList<T>::pop() {
    std::lock_guard<std::recursive_mutex> lock(list_mutex);
    std::shared_ptr<T> result;
    if (head != nullptr){
        result = head->GetValue();
        head = head->GetNext();
    }
    count--;
    return result;
}

template <class T>
size_t TList<T>::Size() {
    std::lock_guard<std::recursive_mutex> lock(list_mutex);
    return count;
}

template <class T>
TIterator<TListItem<T>, T> TList<T>::begin() const{
    return TIterator<TListItem<T>, T>(head);
}

template <class T>
TIterator<TListItem<T>, T> TList<T>::end() const{
    return TIterator<TListItem<T>, T>(nullptr);
}

template <class T>
TList<T>::~TList() {}

template <class T>
std::ostream& operator<<(std::ostream& os, const TList<T>& list) {
    for (auto i:list) std::cout << *i << std::endl;
    return os;
}

#include "Triangle.hpp"
#include <functional>
template class TList<std::function<void(void)>>;
template std::ostream& operator<<(std::ostream& os, const TList<Triangle>& list);
