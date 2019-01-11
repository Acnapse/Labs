#include "TListItem.hpp"
#include <iostream>

template <class T> TListItem<T>::TListItem(std::shared_ptr<T> item, std::recursive_mutex                     *parent) {
    _value = std::shared_ptr<T> (item);
    _next = nullptr;
    _prev = nullptr;
    list_mutex = parent;
}

template <class T>
std::shared_ptr<TListItem<T>> TListItem<T>::SetNext(std::shared_ptr<TListItem<T>> &next) {
    std::unique_lock<std::recursive_mutex> lock(*list_mutex);
    std::shared_ptr<TListItem<T>> old = _next;
    _next = next;
    return old;
}

template <class T>
std::shared_ptr<TListItem<T>> TListItem<T>::SetPrev(std::shared_ptr<TListItem<T>> &prev) {
    std::unique_lock<std::recursive_mutex> lock(*list_mutex);
    std::shared_ptr<TListItem<T>> old = _prev;
    _prev = prev;
    return old;
}

template <class T>
std::shared_ptr<T> TListItem<T>::GetValue() const {
    std::unique_lock<std::recursive_mutex> lock(*list_mutex);
    return _value;
}

template <class T> std::shared_ptr<TListItem<T>> TListItem<T>::GetNext() {
    std::unique_lock<std::recursive_mutex> lock(*list_mutex);
    return _next;
}

template <class T>
std::shared_ptr<TListItem<T>> TListItem<T>::GetPrev() {
    std::unique_lock<std::recursive_mutex> lock(*list_mutex);
    return _prev;
}

template <class A>
std::ostream& operator<<(std::ostream& os, const TListItem<A>& obj) {
    std::unique_lock<std::recursive_mutex> lock(*obj.list_mutex);
    os << *obj._value << std::endl;
    return os;
}

template <class T> TListItem<T>::~TListItem() {
    std::cout << "List item: deleted" << std::endl;
}

#include "Triangle.hpp"
#include <functional>
template class TListItem<Triangle>;
template class TListItem<std::function<void(void)>>;
template std::ostream& operator<<(std::ostream& os, const TListItem<Triangle>& obj);
