#include <set>
#include "binary_search_tree.h"

int main() {
    binary_search_tree<int, greater<>> bst;
    bst.insert(12);
    bst.insert(6);
    bst.insert(1);
    bst.insert(4);
    bst.insert(9);
    bst.insert(13);
    bst.insert(16);
    bst.insert(22);
    bst.print();
    cout << "find 4: " << bst.find(4) << endl;
    cout << "find 12: " << bst.find(12) << endl;
    cout << "find 55: " << bst.find(55) << endl;
    bst.erase(12);
    bst.print();

    return 0;
}