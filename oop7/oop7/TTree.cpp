#include "TTree.hpp"

template <class T, class TT>
TBinaryTree<T, TT>::TBinaryTree() : root(nullptr) {}

template <class T, class TT>
void TBinaryTree<T, TT>::RemoveSubitem(IRemoveCriteria<TT> *criteria) {
    std::cout << "\n-----------------" << std::endl;
    for (auto i : * this) {
        T copy;
        while (!i->empty()) {
            std::shared_ptr<TT> value = i->pop();
            
            if (criteria->isIt(value.get())) {
                std::cout << "BinaryTree: Delete element " << *value << std::endl;
            }
            else {
                copy.push(value);
            }
        }
        while (!copy.empty()) i->push(copy.pop());
    }
    std::cout << "------------------\n";
}

template <class T, class TT>
void TBinaryTree<T, TT>::InsertSubitem(std::shared_ptr<TT> value) {
    
    bool inserted = false;
    if (root != nullptr) {
        
        for (auto i : * this) {
            if (i->Size() < 5) {
                i->push(value);
                inserted = true;
            }
        }
    }
    
    if (!inserted) {
        T* t_value = new T();
        t_value->push(value);
        PushBack(t_value);
    }
}

template <class T, class TT>
void TBinaryTree<T, TT>::PushBack(T* value) {
    std::shared_ptr<TBinaryTreeItem<T>> other(new TBinaryTreeItem<T>(value));
    if (!root) {
        root = other;
        return;
    }
    else {
        std::shared_ptr<TBinaryTreeItem<T>> tmp = root;
        
        while (tmp) {
            if (other->GetIndex() >= tmp->GetIndex()) {
                if (tmp->GetRight()) {
                    tmp = tmp->GetRight();
                    continue;
                }
                else {
                    std::shared_ptr<TBinaryTreeItem<T>> old = tmp;
                    tmp->SetRight(other);
                    return;
                }
            }
            else if (other->GetIndex() < tmp->GetIndex()) {
                if (tmp->GetLeft()) {
                    tmp = tmp->GetLeft();
                    continue;
                }
                else {
                    std::shared_ptr<TBinaryTreeItem<T>> old = tmp;
                    tmp->SetLeft(other);
                    return;
                }
            }
        }
    }
}
//
//template <class T, class TT>
//bool TBinaryTree<T, TT>::Remove(T* value) {
//    bool result = false;
//    if (root != nullptr) {
//        result = true;
//        root = root->GetNext();
//    }
//
//    return result;
//}

template <class T, class TT>
size_t TBinaryTree<T, TT>::Size(){
    size_t result = 0;
    for(auto i : *this) result++;
    return result;
}

template <class T, class TT>
TIterator<TBinaryTreeItem<T>, T> TBinaryTree<T, TT>::begin() const{
    std::shared_ptr<TBinaryTreeItem<T>> node = root;
    while (node->GetLeft())
        node = node->GetLeft();
    TIterator<TBinaryTreeItem<T>, T> res(node);
    return res;
}

template <class T, class TT>
TIterator<TBinaryTreeItem<T>, T> TBinaryTree<T, TT>::end() const{
    return TIterator<TBinaryTreeItem<T>,T>(nullptr);
}

template <class A, class AA>
std::ostream& operator<<(std::ostream& os, const TBinaryTree<A, AA>& tree) {
    std::cout << "BinaryTree: \n\n";
    for(auto i:tree) std::cout << *i << std::endl;
    return os;
}

template <class T, class TT>
TBinaryTree<T, TT>::~TBinaryTree() {}

#include "TList.hpp"
#include "Figure.hpp"
template class TBinaryTree<TList<Figure>, Figure>;
template std::ostream& operator<<(std::ostream& os, const TBinaryTree<TList<Figure>, Figure>& BinaryTree);
