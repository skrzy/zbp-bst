#include <set>
#include <random>
#include <cassert>
#include "binary_search_tree.h"

bool compare(int a, int b) {
    return a < b;
}

class test {
private:
    int value;
public:
//    ~test() {
//        cout << value << " destroyed" << endl;
//    }

    test(int v): value(v) {
//        cout << v << " created" << endl;
    };
    test(): value(-1) {};

    friend bool operator==(const test& l, const test& r) {
        return l.value == r.value;
    }

    friend bool operator<(const test& l, const test& r) {
        return l.value < r.value;
    }

    friend bool operator>(const test& l, const test& r) {
        return l.value > r.value;
    }
};

void testGreaterPredicate() {
    binary_search_tree<test, greater<>> bst;
    bst.insert(test(12));
    bst.insert(test(3));
    bst.insert(test(44));
    bst.insert(test(13545));
    bst.insert(test(-9));
    bst.insert(test(6654));
    bst.insert(test(0));

    assert(!bst.find(8));
    assert(bst.find(0));
    assert(bst.insert(222));
    assert(!bst.insert(0));
    assert(bst.erase(13545));
    assert(bst.min() == test(6654));
    assert(bst.max() == test(-9));

    bool result = bst.erase(test(12));

    cout << "result: " << result << endl;
}

void testFunctionPointerPredicate() {
    binary_search_tree<int, bool(*)(int,int)> bst(compare);
    bst.insert(45);
    bst.insert(23);
    bst.insert(11);
    bst.insert(22);
    bst.insert(99);
    bst.insert(5);
    assert(bst.min() == 5);
    assert(bst.max() == 99);
    assert(!bst.insert(99));
    assert(bst.insert(2));
    assert(bst.min() == 2);
    assert(!bst.erase(12));
    assert(bst.erase(45));
    assert(bst.min() == 2);
    assert(bst.erase(2));
    assert(bst.min() == 5);
}

void testMemory() {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1, 999999999);

    binary_search_tree<int, greater<>> bst;

    for (int i = 0; i < 1000000; i++) {
        int r = distribution(generator);
        bst.insert(r);
    }

    cout << "tree created" << endl;
    cin.ignore();

    while (!bst.empty()) {
        bst.erase(bst.min());
    }

    cout << "tree empty" << endl;
    cin.ignore();
}

int main() {
    testFunctionPointerPredicate();
//    testMemory();
    testGreaterPredicate();
    return 0;
}