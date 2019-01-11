#include "BinaryTree.h"

template <class T>
BinaryTree<T>::BinaryTree() : head(nullptr), count(0) {}

template <class A>
void print(std::ostream &os, std::shared_ptr<A> item, int lvl) {
    if (item->GetLeft())
        print(os, item->GetLeft(), lvl + 1);
    os << "\nThe number of figure: " << item->GetIndex() << std::endl;
    item->GetFigure()->Print(os);
    os << " lvl = " << lvl << std::endl;
    if (item->GetRight())
        print(os, item->GetRight(), lvl + 1);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree) {
    std::shared_ptr<BinaryTreeItem<T>> item = tree.head;
    if (item != nullptr) {
        std::cout << std::endl;
        print(os, item, 0);
    }
    else std::cout << "The tree is empty\n";
    return os;
}

template <class T>
void BinaryTree<T>::push(const std::shared_ptr<T> &figure, size_t index) {
    std::shared_ptr<BinaryTreeItem<T>> other(new BinaryTreeItem<T>(figure, index));
    if (empty()) {
        head = other;
        //head->SetParent(nullptr);
        count++;
        return;
    }
    else {
        std::shared_ptr<BinaryTreeItem<T>> tmp = head;

        while (tmp) {
            if (other->GetIndex() >= tmp->GetIndex()) {
                if (tmp->GetRight()) {
                    tmp = tmp->GetRight();
                    continue;
                }
                else {
                    std::shared_ptr<BinaryTreeItem<T>> old = tmp;
                    //other->SetParent(old);
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
                    std::shared_ptr<BinaryTreeItem<T>> old = tmp;
                    //other->SetParent(old);
                    tmp->SetLeft(other);
                    count++;
                    return;
                }
            }
        }
    }
}

template <class T>
bool BinaryTree<T>::empty() {
    return head == nullptr;
}

template <class T>
bool Find (std::shared_ptr<BinaryTreeItem<T>> root, size_t item) {
    std::shared_ptr<BinaryTreeItem<T>> tmp = root;
    while (tmp != nullptr) {
        if (item > tmp->GetIndex())
            tmp = tmp->GetRight();
        else if (item < tmp->GetIndex())
            tmp = tmp->GetLeft();
        else return true;
    }
    return false;
}

template <class T>
size_t BinaryTree<T>::GetCount() {
    return this->count;
}

template<class T>
std::shared_ptr<BinaryTreeItem<T>> BinaryTree<T>::GetMin() const {
    std::shared_ptr<BinaryTreeItem<T>> tmp = head;
    while (tmp->GetLeft() != nullptr)
        tmp = tmp->GetLeft();
    return tmp;
}

template <class T>
Iterator<BinaryTreeItem<T>, T> BinaryTree<T>::begin() {
    return GetMin();
}

template<class T>
std::shared_ptr<BinaryTreeItem<T>> BinaryTree<T>::GetMax() const {
    std::shared_ptr<BinaryTreeItem<T>> tmp = head;
    while (tmp->GetRight() != nullptr)
        tmp = tmp->GetRight();
    return nullptr;
}

template <class T>
Iterator<BinaryTreeItem<T>, T> BinaryTree<T>::end() {
    push(NULL, GetMax()->GetIndex() + 1);
    return GetMax();
}

template <class T>
std::shared_ptr<T> BinaryTree<T>::pop(size_t index) {
    std::shared_ptr<BinaryTreeItem<T>> q, z;

    
    count--;
    if (Find(head, index) == false) {
        std::cout << "This element doesn't exist\n";
        return nullptr;
    }

    int is_root = 0;

    q = head;
    z = head;

    for (;;) {
        if (z == nullptr) return nullptr;
        if (index == z->GetIndex()) {
            is_root = 1;
            break;
        }
        else if (index > z->GetIndex()) {
            z = z->GetRight();
            if (index == z->GetIndex()) break;
            q = q->GetRight();
        }
        else {
            z = z->GetLeft();
            if (index == z->GetIndex()) break;
            q = q->GetLeft();
        }
    }


    if (z->GetRight() == nullptr) {
        if (z->GetLeft() == nullptr && q->GetLeft() != nullptr) {
            std::shared_ptr<BinaryTreeItem<T>> tmp = z->GetLeft();
            q->SetLeft(tmp);
        }
        else if (z->GetLeft() != nullptr && q->GetLeft() != nullptr){
            std::shared_ptr<BinaryTreeItem<T>> tmp = z->GetLeft();
            q->SetRight(tmp);
        }
        else if (z->GetLeft() == nullptr && q->GetLeft() == nullptr) {
            if (is_root == 1)
                head = nullptr;
            else {
                std::shared_ptr<BinaryTreeItem<T>> tmp = z->GetRight();
                q->SetRight(tmp);
            }
        }
    }
    else {
        std::shared_ptr<BinaryTreeItem<T>> y = z->GetRight();
        if (y->GetLeft() == nullptr) {
            std::shared_ptr<BinaryTreeItem<T>> tmp = z->GetLeft();
            y->SetLeft(tmp);
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
            std::shared_ptr<BinaryTreeItem<T>> x = y->GetLeft();
            while (x->GetLeft() != nullptr) {
                y = x;
                x = y->GetLeft();
            }
            std::shared_ptr<BinaryTreeItem<T>> tmp = x->GetRight();
            y->SetLeft(tmp);
            tmp = z->GetLeft();
            x->SetLeft(tmp);
            tmp = z->GetRight();
            x->SetRight(tmp);
            if (is_root != 1) q->SetRight(x);
            else head = x;
        }
    }

    return z->GetFigure();
}

template <class T>
BinaryTree<T>:: ~BinaryTree() {}

#include "Figure.h"
template class BinaryTree<Figure>;
template std::ostream& operator<<(std::ostream& k, const BinaryTree<Figure>& figure);



