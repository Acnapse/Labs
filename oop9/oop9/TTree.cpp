#include "TTree.hpp"
#include <exception>

template <class T> TTree<T>::TTree() : root(nullptr), count(0) {}


template <class T> std::shared_ptr<T> TTree<T>::operator[](size_t i) {
    std::lock_guard<std::recursive_mutex> lock(tree_mutex);
    if (i > size() - 1) throw std::invalid_argument("index greater then tree size");
    size_t j = 0;
    
    for (std::shared_ptr<T> a : * this) {
        if (j == i) return a;
        j++;
    }
    
    return std::shared_ptr<T>(nullptr);
}

template <class T> std::ostream& operator<<(std::ostream& os, const TTree<T>& tree) {
    for(auto i:tree) os << *i << std::endl;
    return os;
}

template <class T> void TTree<T>::push(T *item, size_t index) {
    std::lock_guard<std::recursive_mutex> lock(tree_mutex);
    std::shared_ptr<TTreeItem<T>> other(new TTreeItem<T>(item, index, &tree_mutex));
    count++;
    if (!root) {
        root = other;
        return;
    }
    else {
        std::shared_ptr<TTreeItem<T>> tmp = root;
        
        while (tmp) {
            if (other->GetIndex() >= tmp->GetIndex()) {
                if (tmp->GetRight()) {
                    tmp = tmp->GetRight();
                    continue;
                }
                else {
                    std::shared_ptr<TTreeItem<T>> old = tmp;
                    tmp->SetRight(other);
                    other->SetParent(tmp);
                    return;
                }
            }
            else if (other->GetIndex() < tmp->GetIndex()) {
                if (tmp->GetLeft()) {
                    tmp = tmp->GetLeft();
                    continue;
                }
                else {
                    std::shared_ptr<TTreeItem<T>> old = tmp;
                    tmp->SetLeft(other);
                    other->SetParent(tmp);
                    return;
                }
            }
        }
    }
    
}

template <class T> bool TTree<T>::empty() {
    std::lock_guard<std::recursive_mutex> lock(tree_mutex);
    return root == nullptr;
}

template <class T>
std::shared_ptr<TTreeItem<T> > Find (std::shared_ptr<TTreeItem<T> > root, std::shared_ptr<T> item) {
    std::shared_ptr<TTreeItem<T> > tmp = root, node;
    bool flag = true;
    int is_root = 0;
    
    if (tmp->GetValue() == item) return tmp;
    
    if (tmp->GetRight()) {
        tmp = tmp->GetRight();
        while(tmp->GetLeft()) tmp = tmp->GetLeft();
        flag = false;
    }
    do {
        while(1) {
            if (item == tmp->GetValue()) return tmp;
            if (tmp == root) {
                is_root++;
                break;
            }
            if (!flag && tmp->GetRight()) {
                tmp = tmp->GetRight();
                break;
            }
            node = tmp;
            tmp = tmp->GetParent();
            flag = (node == tmp->GetRight());
        }
        if (is_root > 2) return nullptr;
        while (tmp->GetLeft()) tmp = tmp->GetLeft();
    } while(1);
    
    return nullptr;
}

template<class T>
void TTree<T>::Change(TIterator<TTreeItem<T>, T> item) {
    std::shared_ptr<TTreeItem<T>> q = item.get();
    if (q) q->SetFlag();
}

template <class T>
void TTree<T>::walk(std::shared_ptr<TTreeItem<T>> node, int fl) {
    if(node == NULL) return;
    walk(node->GetLeft(), fl);
    if(node->GetFlag() != fl) node->SetFlag();
    walk(node->GetRight(), fl);
}

template <class T> void TTree<T>::Get() {
    std::shared_ptr<TTreeItem<T>> q = root;
    while (q->GetLeft()) {
        q = q->GetLeft();
    }
    q->SetFlag();
    walk(root, q->GetFlag());
}


template <class T>
std::shared_ptr<T> TTree<T>::pop(std::shared_ptr<T> item) {
    std::shared_ptr<TTreeItem<T>> q, z;
    
    int is_root = 0;
    
    z = Find(root, item);
    
    if (z == nullptr) return nullptr;
    if (root == z) {
        is_root = 1;
        q = root;
    }
    else q = z->GetParent();
    count--;
    
    if (z->GetRight() == nullptr) {
        if (z->GetLeft() == nullptr && q->GetLeft() != nullptr) {
            q->SetLeft(nullptr);
        }
        else if (z->GetLeft() != nullptr && q->GetLeft() != nullptr){
            if (is_root == 1) {
                std::shared_ptr<TTreeItem<T> > t = z->GetLeft();
                t->SetParent(nullptr);
                root = t;
                return z->GetValue();
            }
            std::shared_ptr<TTreeItem<T> > tmp = z->GetLeft();
            q->SetRight(tmp);
        }
        else if (z->GetLeft() == nullptr && q->GetLeft() == nullptr) {
            if (is_root == 1)
                root = nullptr;
            else {
                std::shared_ptr<TTreeItem<T> > tmp = z->GetRight();
                q->SetRight(tmp);
            }
        }
        else {
            std::shared_ptr<TTreeItem<T> > t = z->GetLeft();
            t->SetParent(q);
            q->SetRight(t);
        }
    }
    else {
        std::shared_ptr<TTreeItem<T> > y = z->GetRight();
        if (y->GetLeft() == nullptr) {
            y->SetLeft(z->GetLeft());
            y->SetParent(z->GetParent());
            std::shared_ptr<TTreeItem<T>> t = z->GetLeft();
            if (t) t->SetParent(y);
            if (is_root == 1) root = y;
            else if (q->GetLeft() == z) q->SetLeft(y);
            else q->SetRight(y);
        }
        else {
            std::shared_ptr<TTreeItem<T> > x = y->GetLeft();
            while (x->GetLeft() != nullptr) {
                x->SetParent(y);
                y = x;
                x = y->GetLeft();
            }
            y->SetLeft(x->GetRight());
            x->SetLeft(z->GetLeft());
            x->SetRight(z->GetRight());
            std::shared_ptr<TTreeItem<T> > k = z->GetRight();
            x->SetParent(z->GetParent());
            k->SetParent(x);
            if (y->GetLeft()) {
                std::shared_ptr<TTreeItem<T> > t = y->GetLeft();
                t->SetParent(y);
            }
            if (is_root == 1) root = x;
            else if (q->GetLeft() == z) q->SetLeft(x);
            else q->SetRight(x);
        }
    }
    
    return z->GetValue();
}

template <class T> size_t TTree<T>::size() {
    std::lock_guard<std::recursive_mutex> lock(tree_mutex);
    int result = 0;
    for (auto i : *this) result++;
    return result;
}

template <class T> TIterator<TTreeItem<T>, T> TTree<T>::begin() const{
    if (!root)
        return root;
    std::shared_ptr<TTreeItem<T>> node = root;
    while (node->GetLeft())
        node = node->GetLeft();
    node->SetFlag();
    TIterator<TTreeItem<T>, T> res(node);
    return res;
}

template <class T> TIterator<TTreeItem<T>, T> TTree<T>::end() const{
    return TIterator<TTreeItem<T>, T>(nullptr);
}

template <class T> TTree<T>::~TTree() {}

#include "Figure.hpp"
template class TTree<Figure>;
template std::ostream& operator<<(std::ostream& os, const TTree<Figure>& tree);
