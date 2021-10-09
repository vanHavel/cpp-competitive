#ifndef INTERVALTREE_H
#define INTERVALTREE_H
#include "Prelude.h"
struct ivertex {
    ivertex* parent;
    ivertex* left;
    ivertex* right;
    llll key; // interval
    ll maxRight; // max right point in subtree
    int height;
};

bool contains(llll a, llll b) {
    return a.first <= b.first && a.second >= b.second;
}

llll NOTFOUND = llll(-1, -1);

// Interval tree. Assumes all intervals have left points >= 0
class IntervalTree {
public:
    void insert(llll interval) { assert(interval.first >= 0); root = insert(root, interval); }
    bool search(llll interval) { return search(root, interval) != NULL; }
    int getHeight() { return root == NULL ? 0 : root->height; }
private:
    ivertex* root = NULL;
    int h(ivertex* T) { return T == NULL ? -1 : T->height; }
    ll mr(ivertex* T) { return T == NULL ? 0 : T->maxRight; }
    ivertex* search(ivertex* T, llll interval) {
        if (T == NULL) return NULL;
        else if (contains(T->key, interval)) return T;
        else if (T->left != NULL && T->left->maxRight >= interval.first) return search(T->left, interval);
        else return search(T->right, interval);
    }
    llll successor(ivertex* T) {
        if (T->right != NULL)
            return findMin(T->right);
        else {
            ivertex* par = T->parent;
            ivertex* cur = T;
            while ((par != NULL) && (cur == par->right)) {
                cur = par;
                par = cur->parent;
            }
            return par == NULL ? NOTFOUND : par->key;
        }
    }
    llll predecessor(ivertex* T) {
        if (T->left != NULL)
            return findMax(T->left);
        else {
            ivertex* par = T->parent;
            ivertex* cur = T;
            while ((par != NULL) && (cur == par->left)) {
                cur = par;
                par = cur->parent;
            }
            return par == NULL ? NOTFOUND : par->key;
        }
    }
    llll findMin(ivertex* T) {
        if (T == NULL) return NOTFOUND;
        else if (T->left == NULL) return T->key;
        else return findMin(T->left);
    }
    llll findMax(ivertex* T) {
        if (T == NULL) return NOTFOUND;
        else if (T->right == NULL) return T->key;
        else return findMax(T->right);
    }
    ivertex* rotateLeft(ivertex* T) {
        ivertex* w = T->right;
        w->parent = T->parent;
        T->parent = w;
        T->right = w->left;
        if (w->left != NULL) w->left->parent = T;
        w->left = T;
        T->height = std::max(h(T->left), h(T->right)) + 1;
        w->height = std::max(h(w->left), h(w->right)) + 1;
        T->maxRight = std::max(T->key.second, mr(T->left));
        T->maxRight = std::max(T->maxRight, mr(T->right));
        w->maxRight = std::max(w->key.second, mr(w->left));
        w->maxRight = std::max(w->maxRight, mr(w->right));
        return w;
    }
    ivertex* rotateRight(ivertex* T) {
        ivertex* w = T->left;
        w->parent = T->parent;
        T->parent = w;
        T->left = w->right;
        if (w->right != NULL) w->right->parent = T;
        w->right = T;
        T->height = std::max(h(T->left), h(T->right)) + 1;
        w->height = std::max(h(w->left), h(w->right)) + 1;
        T->maxRight = std::max(T->key.second, mr(T->left));
        T->maxRight = std::max(T->maxRight, mr(T->right));
        w->maxRight = std::max(w->key.second, mr(w->left));
        w->maxRight = std::max(w->maxRight, mr(w->right));
        return w;
    }
    ivertex* rebalance(ivertex* T) {
        int balance = h(T->left) - h(T->right);
        if (balance > 1) {
            int balance2 = h(T->left->left) - h(T->left->right);
            if (balance2 == 1) {
                T = rotateRight(T);
            }
            else {
                T->left = rotateLeft(T->left);
                T = rotateRight(T);
            }
        }
        else if (balance < -1) {
            int balance2 = h(T->right->left) - h(T->right->right);
            if (balance2 == -1)
                T = rotateLeft(T);
            else {
                T->right = rotateRight(T->right);
                T = rotateLeft(T);
            }
        }
        T->height = std::max(h(T->left), h(T->right)) + 1;
        return T;
    }
    ivertex* insert(ivertex* T, llll interval) {
        if (T == NULL) {
            T = new ivertex;
            T->key = interval;
            T->parent = T->left = T->right = NULL;
            T->height = 0;
            T->maxRight = interval.second;
        }
        else if (T->key < interval) {
            T->right = insert(T->right, interval);
            T->right->parent = T;
            T->maxRight = std::max(T->maxRight, interval.second);
        }
        else {
            T->left = insert(T->left, interval);
            T->left->parent = T;
            T->maxRight = std::max(T->maxRight, interval.second);
        }
        T = rebalance(T);
        return T;
    }
};
#endif