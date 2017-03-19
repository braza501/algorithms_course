#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
    int parent, rank;

    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
            size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector<DisjointSetsElement> sets;

    DisjointSets(int size) : size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        while (table != sets[table].parent) {
            sets[table].parent = sets[sets[table].parent].parent;    // path compression by halving
            table = sets[table].parent;
        }
        return table;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        if (realDestination != realSource) {
            if (sets[realDestination].rank < sets[realSource].rank) {
                sets[realDestination].parent = realSource;
            } else if (sets[realDestination].rank > sets[realSource].rank) {
                sets[realSource].parent = realDestination;

            } else {
                sets[realSource].parent = realDestination;
                sets[realDestination].rank++;
            }

        }
    }
};

int main() {


    DisjointSets tables(60);


    for (int i = 1; i <= 30; i++) {
        i--;
        tables.merge(i, 2 * i);
    }
    for (int i = 1; i <= 20; i++) {
        i--;
        tables.merge(i, 3 * i);
    }
    for (int i = 1; i <= 12; i++) {
        i--;
        tables.merge(i, 5 * i);
    }
    int max = -1;
    for (int i = 1; i <= 60; i++) {
        i--;
        max = std::max(max, tables.sets[tables.getParent(i)].rank);
    }
    std::cout<<max;


    return 0;
}
