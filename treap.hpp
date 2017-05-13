#pragma once

#include <random>
#include <functional>

#include <iostream>
using namespace std;

template<class T, class Compare = std::less<T>>
class Treap {
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
            if (l->priority < r->priority) {
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
            else if (x->priority < n->priority)
                split(x->key, n, x->left, x->right), n = x;
            else
                insertRec(x, compare(x->key, n->key) ? n->left : n->right);
        }

        void eraseRec(const T& x, Node& n) {
            if (equals(n->key, x)) {
                Node deletedElem = n;
                n = merge(n->left, n->right);
                delete deletedElem;
            } else {
                eraseRec(x, compare(x, n->key) ? n->left : n->right);
            }
        }

        Node tree;

    public:
        Treap() {
            srand(time(NULL));
            tree = 0;
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

// ----------------------------------------------------------------------------

template<class T>
class ImplicitTreap {
    private:
        // number of possible heap values
        const static int MOD = 1000000007;

        // pointer to treap node structure
        typedef struct _Node {
            // initialize node with key and random heap priority
            _Node(T k) : key(k), priority(rand() % MOD), subSize(1),
                         left(0), right(0) {}
            T key;
            int priority, subSize;
            _Node * left, * right;
        } * Node;

        void compSize(Node n) {
            n->subSize =   (n->left ?  n->left->subSize  : 0)
                         + (n->right ? n->right->subSize : 0)
                         + 1;
        }

        Node merge(Node l, Node r) {
            if (!l || !r)
                return l ? l : r;
            if (l->priority < r->priority) {
                l->right = merge(l->right, r);
                compSize(l);
                return l;
            }
            r->left = merge(l, r->left);
            compSize(r);
            return r;
        }

        void split(int x, Node n, Node& l, Node& r, int inh=0) {
            if (!n) {
                l = r = 0;
                return;
            }
            int pos = inh + (n->left ? n->left->subSize : 0);
            if (pos > x)
                split(x, n->left, l, n->left, inh), r = n;
            else
                split(x, n->right, n->right, r, pos+1), l = n;
            compSize(n);
        }

        T atRec(Node n, int x, int inh=0) const {
            int pos = inh + (n->left ? n->left->subSize : 0);
            if (pos == x)
                return n->key;
            else if (pos > x)
                return atRec(n->left, x, inh);
            return atRec(n->right, x, pos+1);
        }

        int depthRec(Node n) {
            if (!n) return 0;
            return max(depthRec(n->left), depthRec(n->right)) + 1;
        }

        Node tree;
        int elementsCount;

    public:
        ImplicitTreap() {
            srand(time(NULL));
            tree = 0;
            elementsCount = 0;
        }

        T at(int pos) const {
            return atRec(tree, pos);
        }

        void preOrder(Node n, int ind) {
            if (!n) return;
            for(int i = 0; i < ind; i++) cout << "  ";
            cout << "START " << n->key << endl;
            for(int i = 0; i < ind; i++) cout << "  ";
            cout << "subsize: " << n->subSize << endl;
            preOrder(n->left, ind+2);
            preOrder(n->right, ind+2);
            for(int i = 0; i < ind; i++) cout << "  ";
            cout << "END " << n->key << endl;
        }

        void print() {
            cout << endl << endl;
            preOrder(tree, 0);
            cout << endl << endl;
        }
        int depth() {
            return depthRec(tree);
        }

        bool insert(T x, int pos) {
            if (pos > elementsCount)
                return 0;

            // split to l[0...pos-1] and r[pos...n-1]
            Node lsplit, rsplit;
            split(pos-1, tree, lsplit, rsplit);

            // merge x to left treap
            lsplit = merge(lsplit, new _Node(x));

            // merge treaps back together
            tree = merge(lsplit, rsplit);

            elementsCount++;
            return 1;
        }

        bool erase(int pos) {
            if (pos >= elementsCount)
                return 0;

            // split to l[0...pos-1] and r[pos...n-1]
            Node lsplit, rsplit;
            split(pos-1, tree, lsplit, rsplit);

            // split element at pos from r
            Node rpos, rrest;
            split(0, rsplit, rpos, rrest);
            delete rpos;

            // merge leftovers
            tree = merge(lsplit, rrest);

            elementsCount--;
            return 1;
        }

        void push_back(T x) {
            insert(x, elementsCount);
        }

        void push_front(T x) {
            insert(x, 0);
        }

        void pop_back() {
            erase(elementsCount-1);
        }

        void pop_front() {
            erase(0);
        }

        int size() const {
            return elementsCount;
        }
};
