#include <bits/stdc++.h>
#include "treap.hpp"

using namespace std;

const int MOD = 1000000007;

void test(vector<int>& nums) {
    Treap<int> tree;
    for (auto i : nums) {
        tree.insert(i);
    }
    for (auto i : nums) {
        assert(tree.find(i));
        tree.erase(i);
        assert(!tree.find(i));
    }
}

int main() {
    srand(time(0));

    cout << "TREAP: Running basic insert/erase/find tests" << endl;
    vector<int> test1 = {10, 5, 12, 13, 14, 3, 7},
        test2 = {1, 2, 3, 4, 5},
        test3 = {5, 4, 3, 2, 1},
        test4;
    set<int> s;
    for (int i = 0; i < 1000; i++) {
        int x = rand() % MOD;
        while (s.count(x))
            x = rand() % MOD;
        s.insert(x);
        test4.push_back(x);
    }
    test(test1);
    test(test2);
    test(test3);
    test(test4);
    cout << ">> OK" << endl;

    cout << "TREAP: Running set functionality checks" << endl;
    Treap<int> sit;
    assert(sit.insert(4));
    assert(!sit.insert(4));
    assert(sit.erase(4));
    assert(!sit.erase(4));
    assert(!sit.find(4));
    cout << ">> OK" << endl;

    cout << "IMPLITREAP: Running push_back tests" << endl;
    ImplicitTreap<int> it1;
    int testSize = 2000;
    vector<int> test5;
    for (int i = 0; i < testSize; i++) {
        test5.push_back(rand() % MOD);
        it1.push_back(test5.back());
    }
    cout << "  Treap depth @ " << testSize << " elements: " << 
        it1.depth() << endl;
    assert(it1.size() == testSize);
    for (int i = 0; i < testSize; i++) {
        assert(it1.at(i) == test5[i]);
    }
    cout << ">> OK" << endl;

    cout << "IMPLITREAP: Running pop_back tests" << endl;
    for (int i = 0; i < testSize; i++) {
        it1.pop_back();
        for (int j = 0; j < it1.size(); j++) {
            assert(it1.at(j) == test5[j]);
        }
    }
    assert(it1.depth() == 0);
    cout << ">> OK" << endl;

    cout << "IMPLITREAP: Running random insert tests" << endl;
    testSize = 500;
    vector<int> test6;
    for (int i = 0; i < testSize; i++) {
        int pos = (i ? (rand() % i) : 0), elem = rand() % MOD;
        test6.insert(test6.begin() + pos, elem);
        it1.insert(elem, pos);
    }
    for (int i = 0; i < testSize; i++) {
        assert(it1.at(i) == test6[i]);
    }
    cout << ">> OK" << endl;

    cout << "IMPLITREAP: Running random erase tests" << endl;
    for (int i = 0; i < testSize; i++) {
        int pos = (test6.size() ? (rand() % test6.size()) : 0);
        test6.erase(test6.begin() + pos);
        it1.erase(pos);
        for (int j = 0; j < it1.size(); j++) {
            assert(it1.at(j) == test6[j]);
        }
    }
    assert(it1.depth() == 0);
    cout << ">> OK" << endl;
}
