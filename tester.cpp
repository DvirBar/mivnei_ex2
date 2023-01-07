//
// Created by Dvir Bartov on 07/01/2023.
//

#include "RankTree.h"
#include <iostream>
using namespace std;
int main() {
    RankTree<Pair<int,int>, int> tree;
    tree.insert(Pair<int, int>(3, 3), 3);
    tree.insert(Pair<int, int>(3, 72882), 72882);
    tree.insert(Pair<int, int>(24, 26244), 26244);
    tree.insert(Pair<int, int>(38, 1), 1);
    tree.insert(Pair<int, int>(119, 3707), 3707);

    int data = tree.Select(0);
    cout << data << endl;
    tree.printTree();
}