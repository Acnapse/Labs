#include "TBinaryTreeItem.h"
#include <iostream>

template <class T> TBinaryTreeItem<T>::TBinaryTreeItem(T* item, size_t index) {
    this->item = std::shared_ptr<T>(item);
    this->left = nullptr;
    this->right = nullptr;
    this->index = index;
    this->parent = nullptr;
}

template <class T> TBinaryTreeItem<T>::TBinaryTreeItem(std::shared_ptr<T> item, size_t index) {
    this->item = item;
    this->left = nullptr;
    this->right = nullptr;
    this->index = index;
    this->parent = nullptr;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::SetLeft(std::shared_ptr<TBinaryTreeItem<T> > left) {
    std::shared_ptr<TBinaryTreeItem < T> > old = this->left;
    this->left = left;
    return old;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::SetRight(std::shared_ptr<TBinaryTreeItem<T> > right) {
    std::shared_ptr<TBinaryTreeItem < T> > old = this->right;
    this->right = right;
    return old;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::SetParent(std::shared_ptr<TBinaryTreeItem<T> > parent){
    std::shared_ptr<TBinaryTreeItem < T> > old = this->parent;
    this->parent = parent;
    return old;
}

template <class T> std::shared_ptr<T> TBinaryTreeItem<T>::GetValue() const {
    return this->item;
}

template <class T> size_t TBinaryTreeItem<T>::GetIndex() const {
    return this->index;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::GetLeft() {
    return this->left;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::GetRight() {
    return this->right;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::GetParent() {
    return this->parent;
}

template <class T> std::shared_ptr<TBinaryTreeItem<T> > TBinaryTreeItem<T>::GetNext(){
    return this->right;
}

template <class T> TBinaryTreeItem<T>::~TBinaryTreeItem() {}

template <class A> std::ostream& operator<<(std::ostream& os, const TBinaryTreeItem<A>& obj) {
    os << "[" << " ID = "<< obj.index << "    " <<  *obj.item << " ]" << std::endl;
    return os;
}


#include "Triangle.h"
template class TBinaryTreeItem<Triangle>;
template std::ostream& operator<<(std::ostream& os, const TBinaryTreeItem<Triangle>& obj);
