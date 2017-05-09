#include <bits/stdc++.h>
#include "treap.hpp"

using namespace std;

const int MOD = 1000000007;

void test(vector<int>& nums) {
    ImplicitTreap<int> tree;
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

    cout << "Running basic insert/erase/find tests" << endl;
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
    cout << ">> OK" << endl;

    cout << "Running set functionality checks" << endl;
    ImplicitTreap<int> sit;
    assert(sit.insert(4));
    assert(!sit.insert(4));
    assert(sit.erase(4));
    assert(!sit.erase(4));
    assert(!sit.find(4));
    cout << ">> OK" << endl;
}
