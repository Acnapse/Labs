#include "TTreeItem.hpp"

template <class T> TBinaryTreeItem<T>::TBinaryTreeItem(T* value) {
    _value = std::shared_ptr<T>(value);
    left = nullptr;
    right = nullptr;
    index = 1 + rand() % 200;
}

template <class T>
std::shared_ptr<T> TBinaryTreeItem<T>::GetValue() {
    return _value;
}

template <class T>
size_t TBinaryTreeItem<T>::GetIndex() {
    return index;
}

template <class T>
std::shared_ptr<TBinaryTreeItem<T>> TBinaryTreeItem<T>::GetLeft() {
    return left;
}

template <class T>
void TBinaryTreeItem<T>::SetRight(std::shared_ptr<TBinaryTreeItem> right) {
    this->right = right;
}

template <class T>
std::shared_ptr<TBinaryTreeItem<T>> TBinaryTreeItem<T>::GetRight() {
    return right;
}

template <class T>
std::shared_ptr<TBinaryTreeItem<T>> TBinaryTreeItem<T>::GetNext(){
    std::shared_ptr<TBinaryTreeItem<T>> node = right;
//    if (node)
//        while (node->left)
//            node = node->left;
//    else {
//        if (prev.lock() && prev.lock()->right.get() == this) {
//            node = prev.lock();
//            while (node->prev.lock() && node->prev.lock()->left != node)
//                node = node->prev.lock();
//            return node->prev.lock();
//        }
//        return prev.lock();
//    }
    return node;
}


template <class T>
void TBinaryTreeItem<T>::SetLeft(std::shared_ptr<TBinaryTreeItem> left) {
    this->left = left;
}

template <class T>
void TBinaryTreeItem<T>::PushBack(std::shared_ptr<TBinaryTreeItem<T>> _next) {
    PushBack(_next);
}

template <class T> TBinaryTreeItem<T>::~TBinaryTreeItem() {}

#include "TList.hpp"
#include "Figure.hpp"
template class TBinaryTreeItem<TList<Figure>>;
template class TBinaryTreeItem<Figure>;
