#pragma once

#include <random>
#include <functional>

template<class T, class Compare = std::less<T>>
class ImplicitTreap {
    private:
        // number of possible heap values
        const static int MOD = 1000000007;

        // pointer to treap node structure
        typedef struct _Node {
            // initialize node with key and random heap priority
            _Node(T k) : key(k), priority(rand() % MOD),
                         left(nullptr), right(nullptr) {}
            T key;
            int priority;
            _Node * left, * right;
        } * Node;

        // instantiate comparator object
        Compare compare;

        // element equality check only using the comparator
        bool equals(const T& x, const T& y) const {
            if (!compare(x, y) && !compare(y, x))
                return 1;
            return 0;
        }

        Node merge(Node l, Node r) {
            if (!l || !r)
                return l ? l : r;
            if (l->priority > r->priority) {
                l->right = merge(l->right, r);
                return l;
            }
            r->left = merge(l, r->left);
            return r;
        }

        void split(const T& x, Node n, Node& l, Node& r) {
            if (!n)
                l = r = 0;
            else if (compare(x, n->key))
                split(x, n->left, l, n->left), r = n;
            else
                split(x, n->right, n->right, r), l = n;
        }

        bool findRec(const T& x, Node n) const {
            if (!n)
                return 0;
            if (equals(n->key, x))
                return 1;
            if (compare(n->key, x))
                return findRec(x, n->right);
            return findRec(x, n->left);
        }

        void insertRec(Node x, Node& n) {
            if (!n)
                n = x;
            else if (x->priority > n->priority)
                split(x->key, n, x->left, x->right), n = x;
            else
                insertRec(x, compare(x->key, n->key) ? n->left : n->right);
        }

        void eraseRec(const T& x, Node& n) {
            if (equals(n->key, x)) {
                delete n;
                n = merge(n->left, n->right);
            } else {
                eraseRec(x, compare(x, n->key) ? n->left : n->right);
            }
        }

        Node tree;

    public:
        ImplicitTreap() {
            srand(time(NULL));
        }

        bool find(T x) const {
            return findRec(x, tree);
        }

        bool insert(T x) {
            if (find(x))
                return 0;
            insertRec(new _Node(x), tree);
            return 1;
        }

        bool erase(T x) {
            if (!find(x))
                return 0;
            eraseRec(x, tree);
            return 1;
        }
};
