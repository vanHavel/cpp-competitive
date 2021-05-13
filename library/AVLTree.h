#ifndef AVLTREE_H
#define AVLTREE_H
#include "Prelude.h"
struct vertex {
    vertex* parent;
    vertex* left;
    vertex* right;
    ll key;
    int height;
    int elems;
};
// AVL tree with order statistics for positive elements
class AVLTree {
public:
    void insert(ll v) { assert(v >= 0); root = insert(root, v); }
    void remove(ll v) { root = remove(root, v); }
    bool search(ll v) { return search(root, v) != NULL; }
    ll successor(ll v) {
        vertex* vPos = search(root, v);
        return vPos == NULL ? -1 : successor(vPos);
    }
    ll predecessor(ll v) {
        vertex* vPos = search(root, v);
        return vPos == NULL ? -1 : predecessor(vPos);
    }
    vll inorder() {
        vll res;
        inorder(root, res);
        return res;
    }
    ll findMin() { return findMin(root); }
    ll findMax() { return findMax(root); }
    int getHeight() { return root == NULL ? 0 : root->height; }
    int rank(ll v) {
        vertex* vPos = search(root, v);
        return vPos == NULL ? -1 : rank(vPos);
    }
    int getCount() { return root == NULL ? 0 : root->elems; }
    ll select(int k) { return k > getCount() ? -1 : select(root, k); }
private:
    vertex* root = NULL;
    int h(vertex* T) { return T == NULL ? -1 : T->height; }
    int c(vertex* T) { return T == NULL ? 0 : T->elems; }
    vertex* search(vertex* T, ll v) {
        if (T == NULL) return T;
        else if (T->key == v) return T;
        else if (T->key < v) return search(T->right, v);
        else return search(T->left, v);
    }
    void inorder(vertex* T, vll &vec) {
        if (T == NULL) { return; }
        inorder(T->left, vec);
        vec.push_back(T->key);
        inorder(T->right, vec);
    }
    ll successor(vertex* T) {
        if (T->right != NULL)
            return findMin(T->right);
        else {
            vertex* par = T->parent;
            vertex* cur = T;
            while ((par != NULL) && (cur == par->right)) {
                cur = par;
                par = cur->parent;
            }
            return par == NULL ? -1 : par->key;
        }
    }
    ll predecessor(vertex* T) {
        if (T->left != NULL)
            return findMax(T->left);
        else {
            vertex* par = T->parent;
            vertex* cur = T;
            while ((par != NULL) && (cur == par->left)) {
                cur = par;
                par = cur->parent;
            }
            return par == NULL ? -1 : par->key;
        }
    }
    ll findMin(vertex* T) {
        if (T == NULL) return -1;
        else if (T->left == NULL) return T->key;
        else return findMin(T->left);
    }
    ll findMax(vertex* T) {
        if (T == NULL) return -1;
        else if (T->right == NULL) return T->key;
        else return findMax(T->right);
    }
    vertex* rotateLeft(vertex* T) {
        vertex* w = T->right;
        w->parent = T->parent;
        T->parent = w;
        T->right = w->left;
        if (w->left != NULL) w->left->parent = T;
        w->left = T;
        T->height = std::max(h(T->left), h(T->right)) + 1;
        w->height = std::max(h(w->left), h(w->right)) + 1;
        T->elems = c(T->left) + c(T->right) + 1;
        w->elems = c(w->left) + c(w->right) + 1;
        return w;
    }
    vertex* rotateRight(vertex* T) {
        vertex* w = T->left;
        w->parent = T->parent;
        T->parent = w;
        T->left = w->right;
        if (w->right != NULL) w->right->parent = T;
        w->right = T;
        T->height = std::max(h(T->left), h(T->right)) + 1;
        w->height = std::max(h(w->left), h(w->right)) + 1;
        T->elems = c(T->left) + c(T->right) + 1;
        w->elems = c(w->left) + c(w->right) + 1;
        return w;
    }
    vertex* rebalance(vertex* T) {
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
    vertex* insert(vertex* T, ll v) {
        if (T == NULL) {
            T = new vertex;
            T->key = v;
            T->parent = T->left = T->right = NULL;
            T->height = 0;
            T->elems = 1;
        }
        else if (T->key < v) {
            T->right = insert(T->right, v);
            T->right->parent = T;
            T->elems = c(T->left) + c(T->right) + 1;
        }
        else {
            T->left = insert(T->left, v);
            T->left->parent = T;
            T->elems = c(T->left) + c(T->right) + 1;
        }
        T = rebalance(T);
        return T;
    }
    vertex* remove(vertex* T, ll v) {
        if (T == NULL)  return T;
        if (T->key == v) {
            if (T->left == NULL && T->right == NULL) {
                T = NULL;
            }
            else if (T->left == NULL && T->right != NULL) {
                T->right->parent = T->parent;
                T = T->right;
            }
            else if (T->left != NULL && T->right == NULL) {
                T->left->parent = T->parent;
                T = T->left;
            }
            else {
                ll succ = successor(v);
                T->key = succ;
                T->right = remove(T->right, succ);
                T->elems--;
            }
        }
        else if (T->key < v) {
            T->right = remove(T->right, v);
            T->elems--;
        }
        else {
            T->left = remove(T->left, v);
            T->elems--;
        }
        if (T != NULL) {
            T = rebalance(T);
        }
        return T;
    }
    ll select(vertex* T, int k) {
        if (k == c(T->left) + 1) {
            return T->key;
        }
        else if (k < c(T->left) + 1) {
            return select(T->left, k);
        }
        else {
            return select(T->right, k - (c(T->left) + 1));
        }
    }
    int rank(vertex* T) {
        if (T == NULL) {
            return -1;
        }
        else if (T == root) {
            return c(T->left) + 1;
        }
        else if (T->parent->left == T) {
            return rank(predecessor(T)) + 1;
        }
        else {
            return rank(T->parent) + c(T->left) + 1;
        }
    }
};
#endif