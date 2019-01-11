#include "BinaryTreeItem.h"
#include <iostream>

template <class T>
BinaryTreeItem<T>::BinaryTreeItem(const std::shared_ptr<T> &figure, size_t index) {
    this->index = index;
    this->figure = figure;
    //this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

template <class T>
BinaryTreeItem<T>::BinaryTreeItem(std::shared_ptr<BinaryTreeItem<T>> r) {
    this->index = r->index;
    this->figure = r->figure;
    //this->parent = r->parent;
    this->left = r->left;
    this->right = r->right;
}

template <class T>
std::shared_ptr<BinaryTreeItem<T>> BinaryTreeItem<T>::SetLeft(std::shared_ptr<BinaryTreeItem<T>> left){
    std::shared_ptr<BinaryTreeItem<T>> old = this->left;
    this->left = left;
    return old;
}

template <class T>
TAllocationBlock BinaryTreeItem<T>::treeitem_allocator(sizeof(BinaryTreeItem<T>), 100);

template <class T> void *  BinaryTreeItem<T>::operator new (size_t size) {
    return treeitem_allocator.allocate();
}


template <class T> void BinaryTreeItem<T>::operator delete(void *p) {
    treeitem_allocator.deallocate(p);
}

template <class T>
size_t BinaryTreeItem<T>::GetIndex() {
    return this->index;
}

template <class T>
std::shared_ptr<BinaryTreeItem<T>> BinaryTreeItem<T>::SetRight(std::shared_ptr<BinaryTreeItem<T>> right){
    std::shared_ptr<BinaryTreeItem<T>> old = this->right;
    this->right = right;
    return old;
}

//template <class T>
//std::shared_ptr<BinaryTreeItem<T>> BinaryTreeItem<T>::SetParent(std::shared_ptr<BinaryTreeItem<T>> parent){
//    std::shared_ptr<BinaryTreeItem<T>> old = this->parent;
//    this->parent = parent;
//    return old;
//}

template <class T>
std::shared_ptr<T> BinaryTreeItem<T>::GetFigure() const {
    return this->figure;
}

template <class T>
std::shared_ptr<BinaryTreeItem<T>> BinaryTreeItem<T>::GetLeft() {
    return this->left;
}

template <class T>
std::shared_ptr<BinaryTreeItem<T>> BinaryTreeItem<T>::GetRight() {
    return this->right;
}

template<class T>
BinaryTreeItem<T> BinaryTreeItem<T>::GetNext() {
//    if (right != nullptr) {
//        *this = GetRight();
//        while (left != nullptr)
//            *this = GetLeft();
//    }
//    else {
//        //std::shared_ptr<BinaryTreeItem<T>> tmp = parent;
//        while(tmp->right->index == index) {
//            *this = tmp;
//            tmp = tmp->parent;
//        }
//        if (right != tmp)
//            *this = tmp;
//    }
    return *this;
}

template <class A>
std::ostream& operator<<(std::ostream& os, const BinaryTreeItem<A>& obj) {
    os << "[" << *obj.figure << "]";
    return os;
}

#include "Figure.h"
template class BinaryTreeItem<Figure>;
template std::ostream& operator<<(std::ostream& out, const BinaryTreeItem<Figure>& figure);

