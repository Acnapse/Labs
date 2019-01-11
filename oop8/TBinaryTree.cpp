#include "TBinaryTree.h"
#include <exception>

template <class T> TBinaryTree<T>::TBinaryTree() : head(nullptr), count(0) {}

template <class T>
std::shared_ptr<T> TBinaryTree<T>::operator[](size_t i) {
    if (i > size() - 1) throw std::invalid_argument("index greater then stack size");
    size_t j = 0;
    
    for (std::shared_ptr<T> a : * this) {
        if (j == i) return a;
        j++;
    }
    
    return std::shared_ptr<T>(nullptr);
}

template <class T> void TBinaryTree<T>::sort() {
    if (size() > 1) {
        double cnt = 1;
        std::shared_ptr<T> middle = pop(cnt);
        while (!middle) {
            cnt++;
            middle = pop(cnt);
        }
        TBinaryTree<T> left, right;
        
        while (!empty()) {
            std::shared_ptr<T> item = pop(cnt);
            while (!item) {
                cnt++;
                item = pop(cnt);
            }
            if (item->Square() < middle->Square()) {
                left.push(item, cnt);
            } else {
                right.push(item, cnt);
            }
        }
        
        left.sort();
        right.sort();
        
        int max = cnt;
        while (!left.empty()) {
            std::shared_ptr<T> item = left.pop(cnt);
            while (!item) {
                cnt--;
                item = left.pop(cnt);
            }
            push(item, cnt);
        }
        cnt = max;
        push(middle, cnt);
        while (!right.empty()) {
            std::shared_ptr<T> item = right.pop(cnt);
            while (!item) {
                cnt--;
                item = right.pop(cnt);
            }
            push(item, cnt);
        }
        
    }
}

template <class T> void TBinaryTree<T>::sort_parallel() {
    if (size() > 1) {
        double cnt = 1;
        std::shared_ptr<T> middle = pop(cnt);
        while (!middle) {
            cnt++;
            middle = pop(cnt);
        }
        TBinaryTree<T> left, right;
        
        while (!empty()) {
            std::shared_ptr<T> item = pop(cnt);
            while (!item) {
                cnt++;
                item = pop(cnt);
            }
            if (item->Square() < middle->Square()) {
                left.push(item, cnt);
            } else {
                right.push(item, cnt);
            }
        }
        
        int max = cnt;
        std::future<void> left_res = left.sort_in_background();
        std::future<void> right_res = right.sort_in_background();
        
        
        left_res.get();
        cnt = max;
        while (!left.empty()) {
            std::shared_ptr<T> item = left.pop(cnt);
            while (!item) {
                cnt--;
                item = left.pop(cnt);
            }
            push(item, cnt);
        }
        
        cnt = max;
        push(middle, cnt);
        
        right_res.get();
        cnt = max;
        while (!right.empty()) {
            std::shared_ptr<T> item = right.pop(cnt);
            while (!item) {
                cnt--;
                item = right.pop(cnt);
            }
            push(item, cnt);
        }
    }
}

template<class T > std::future<void> TBinaryTree<T>::sort_in_background() {
    std::packaged_task<void(void) > task(std::bind(std::mem_fn(&TBinaryTree<T>::sort_parallel), this));
    std::future<void> res(task.get_future());
    std::thread th(std::move(task));
    th.detach();
    return res;
}

template <class T> void TBinaryTree<T>::push(std::shared_ptr<T> item, size_t index) {
    std::shared_ptr<TBinaryTreeItem<T> > other(new TBinaryTreeItem<T>(item, index));
    if (empty()) {
        head = other;
        count++;
        return;
    }
    else {
        std::shared_ptr<TBinaryTreeItem<T> > tmp = head;
        while (tmp) {
            if (other.get()->GetValue()->Square() >= tmp.get()->GetValue()->Square()) {
                if (tmp->GetRight()) {
                    tmp = tmp->GetRight();
                    continue;
                }
                else {
                    std::shared_ptr<TBinaryTreeItem<T> > old = tmp;
                    other->SetParent(tmp);
                    tmp->SetRight(other);
                    count++;
                    return;
                }
            }
            else {
                if (tmp->GetLeft()) {
                    tmp = tmp->GetLeft();
                    continue;
                }
                else {
                    std::shared_ptr<TBinaryTreeItem<T> > old = tmp;
                    other->SetParent(tmp);
                    tmp->SetLeft(other);
                    count++;
                    return;
                }
            }
        }
    }
    
}

template <class T>
std::shared_ptr<TBinaryTreeItem<T> > Find (std::shared_ptr<TBinaryTreeItem<T> > root, size_t item) {
    std::shared_ptr<TBinaryTreeItem<T> > tmp = root, node;
    bool flag = true;
    int is_root = 0;
    
    if (tmp->GetIndex() == item) return tmp;
    
    if (tmp->GetRight()) {
        tmp = tmp->GetRight();
        while(tmp->GetLeft()) tmp = tmp->GetLeft();
        flag = false;
    }
    do {
        while(1) {
            if (item == tmp->GetIndex()) return tmp;
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


template <class T>
std::shared_ptr<T> TBinaryTree<T>::pop(size_t index) {
    std::shared_ptr<TBinaryTreeItem<T> > q, z;
    
    int is_root = 0;
    
    z = Find(head, index);
    
    if (z == nullptr) return nullptr;
    if (head == z) {
        is_root = 1;
        q = head;
    }
    else q = z->GetParent();
    count--;
    
    if (z->GetRight() == nullptr) {
        if (z->GetLeft() == nullptr && q->GetLeft() != nullptr) {
            q->SetLeft(z->GetLeft());
        }
        else if (z->GetLeft() != nullptr && q->GetLeft() != nullptr){
            if (is_root == 1) {
                std::shared_ptr<TBinaryTreeItem<T> > t = z->GetLeft();
                t->SetParent(nullptr);
                head = t;
                return z->GetValue();
            }
            std::shared_ptr<TBinaryTreeItem<T> > tmp = z->GetLeft();
            q->SetRight(tmp);
        }
        else if (z->GetLeft() == nullptr && q->GetLeft() == nullptr) {
            if (is_root == 1)
                head = nullptr;
            else {
                std::shared_ptr<TBinaryTreeItem<T> > tmp = z->GetRight();
                q->SetRight(tmp);
            }
        }
        else {
            std::shared_ptr<TBinaryTreeItem<T> > t = z->GetLeft();
            t->SetParent(q);
            q->SetRight(t);
        }
    }
    else {
        std::shared_ptr<TBinaryTreeItem<T> > y = z->GetRight();
        if (y->GetLeft() == nullptr) {
            y->SetLeft(z->GetLeft());
            y->SetParent(z->GetParent());
            if (is_root == 1) head = y;
            else {
                if (q->GetLeft() == nullptr && q->GetRight() != nullptr)
                    q->SetRight(y);
                else if (q->GetLeft() != nullptr && q->GetRight() == nullptr)
                    q->SetLeft(y);
                else if (q->GetLeft() != nullptr && q->GetRight() != nullptr)
                    q->SetLeft(y);
                else q->SetRight(y);
            }
        }
        else {
            std::shared_ptr<TBinaryTreeItem<T> > x = y->GetLeft();
            while (x->GetLeft() != nullptr) {
                x->SetParent(y);
                y = x;
                x = y->GetLeft();
            }
            y->SetLeft(x->GetRight());
            x->SetLeft(z->GetLeft());
            x->SetRight(z->GetRight());
            std::shared_ptr<TBinaryTreeItem<T> > k = z->GetRight();
            x->SetParent(z->GetParent());
            k->SetParent(x);
            if (y->GetLeft()) {
                std::shared_ptr<TBinaryTreeItem<T> > t = y->GetLeft();
                t->SetParent(y);
            }
            if (is_root == 1) head = x;
            else q->SetLeft(x);
        }
    }
    
    return z->GetValue();
}

template <class T> void TBinaryTree<T>::push(T *item, size_t index) {
    std::shared_ptr<TBinaryTreeItem<T> > other(new TBinaryTreeItem<T>(item, index));
    if (empty()) {
        head = other;
        count++;
        return;
    }
    else {
        std::shared_ptr<TBinaryTreeItem<T> > tmp = head;
        
        while (tmp) {
            if (other->GetIndex() >= tmp->GetIndex()) {
                if (tmp->GetRight()) {
                    tmp = tmp->GetRight();
                    continue;
                }
                else {
                    std::shared_ptr<TBinaryTreeItem<T> > old = tmp;
                    other->SetParent(tmp);
                    tmp->SetRight(other);
                    count++;
                    return;
                }
            }
            else if (other->GetIndex() < tmp->GetIndex()) {
                if (tmp->GetLeft()) {
                    tmp = tmp->GetLeft();
                    continue;
                }
                else {
                    std::shared_ptr<TBinaryTreeItem<T> > old = tmp;
                    other->SetParent(tmp);
                    tmp->SetLeft(other);
                    count++;
                    return;
                }
            }
        }
    }
}

template <class T>
void TBinaryTree<T>::print(std::ostream& os, std::shared_ptr<TBinaryTreeItem<T> > item) const{
    if (item) {
        print(os, item->GetLeft());
        os << "ID = " << item->GetIndex() << "   " << *item->GetValue() << std::endl;
        print(os, item->GetRight());
    }
}

template <class T>
std::ostream& operator<<(std::ostream& os, const TBinaryTree<T>& tree) {
    tree.print(os, tree.head);
    return os;
}

template <class T> bool TBinaryTree<T>::empty() {
    return head == nullptr;
}

template <class T> size_t TBinaryTree<T>::size() {
    return count;
}

template <class T> TIterator<TBinaryTreeItem<T>, T> TBinaryTree<T>::begin() const{
    return TIterator<TBinaryTreeItem<T>, T>(head);
}

template <class T> TIterator<TBinaryTreeItem<T>, T> TBinaryTree<T>::end() const{
    return TIterator<TBinaryTreeItem<T>, T>(nullptr);
}

template <class T> TBinaryTree<T>::~TBinaryTree() {}

#include "Triangle.h"
template class TBinaryTree<Triangle>;
template std::ostream& operator<<(std::ostream& os, const TBinaryTree<Triangle>& stack);
