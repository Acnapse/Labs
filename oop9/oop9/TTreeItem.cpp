#include "TTreeItem.hpp"
#include <iostream>

template <class T> TTreeItem<T>::TTreeItem(T* item, size_t index, std::recursive_mutex *parent) {
    this->tree_mutex = parent;
    this->item = std::shared_ptr<T>(item);
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->index = index;
    this->flag = 0;
    //std::cout << "Stack item: created" << std::endl;
}

template <class T> std::shared_ptr<TTreeItem<T>> TTreeItem<T>::SetLeft(std::shared_ptr<TTreeItem<T>> left) {
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    std::shared_ptr<TTreeItem < T>> old = this->left;
    this->left = left;
    return old;
}

template <class T> std::shared_ptr<TTreeItem<T>> TTreeItem<T>::SetRight(std::shared_ptr<TTreeItem<T>> right) {
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    std::shared_ptr<TTreeItem <T>> old = this->right;
    this->right = right;
    return old;
}

template <class T> std::shared_ptr<TTreeItem<T>> TTreeItem<T>::SetParent(std::shared_ptr<TTreeItem<T>> parent) {
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    std::shared_ptr<TTreeItem <T>> old = this->parent;
    this->parent = parent;
    return old;
}

template <class T>
std::shared_ptr<TTreeItem<T>> TTreeItem<T>::GetNext(){
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    std::shared_ptr<TTreeItem<T>> node, tmp, nd;
    bool fl = true;
    if (left && left->flag == flag && right) {
        tmp = right;
        while (tmp->left) tmp = tmp->left;
        node = tmp;
    }
    else if (!left && right && flag != right->flag) {
        tmp = right;
        while (tmp->left) tmp = tmp->left;
        node = tmp;
    }
    else if (parent) {
        if (parent->right) tmp = parent->right;
        else tmp = parent->left;
        while(1) {
            if (!fl && tmp->GetLeft()) {
                if (tmp->left->flag != flag)
                    tmp = tmp->GetLeft();
                node = tmp;
                break;
            }
            if (tmp->left && tmp->left->flag != tmp->flag) {
                node = tmp;
                break;
            }
            nd = tmp;
            tmp = tmp->GetParent();
            if (!tmp) return nullptr;
            fl = (nd == tmp->GetRight());
        }
    }
    else return nullptr;
    node->SetFlag();
    return node;
}

template <class T> std::shared_ptr<T> TTreeItem<T>::GetValue() const {
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    return this->item;
}

template <class T> int TTreeItem<T>::GetFlag() {
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    return this->flag;
}

template <class T> void TTreeItem<T>::SetFlag() {
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    this->flag = (flag + 1) % 2;
}

template <class T> size_t TTreeItem<T>::GetIndex() const{
    std::unique_lock<std::recursive_mutex> lock(*tree_mutex);
    return this->index;
}

template <class T> std::shared_ptr<TTreeItem<T>> TTreeItem<T>::GetLeft() {
    std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    return this->left;
}

template <class T> std::shared_ptr<TTreeItem<T>> TTreeItem<T>::GetRight() {
    std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    return this->right;
}

template <class T> std::shared_ptr<TTreeItem<T>> TTreeItem<T>::GetParent() {
    std::lock_guard<std::recursive_mutex> lock(*tree_mutex);
    return this->parent;
}

template <class T> TTreeItem<T>::~TTreeItem() {
    //std::cout << "Stack item: deleted" << std::endl;
}

template <class A> std::ostream& operator<<(std::ostream& os, const TTreeItem<A>& obj) {
    std::lock_guard<std::recursive_mutex> lock(*obj.tree_mutex);
    os << "[" << *obj.item << "]" << std::endl;
    return os;
}


#include "Figure.hpp"
template class TTreeItem<Figure>;
template std::ostream& operator<<(std::ostream& os, const TTreeItem<Figure>& obj);
