#include "HashTable.h"
#include "UnionFind.h"
#include <iostream>

using namespace std;

int main() {
    HashTable<int> table(30);
    for(int i=1; i<=30; i++) {
        table.insert(i, i);
    }

    table.insert(35, 35);
    table.insert(45, 45);
    table.insert(95, 95);
    table.insert(622, 622);

    for(int i=2000; i<=3000; i++) {
        table.insert(i, i);
    }


    table.print();

    for(int i=2000; i<=3000; i++) {
        table.remove(i);
    }

    table.print();

    cout << table.lookup(622) << endl;
}