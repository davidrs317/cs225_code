/* Your code here! */
#pragma once
#include <vector>

/**
 * create n unconnected root nodes at the end of the vector
 */
class DisjointSets{
    public:
        /**
        * Creates n unconnected root nodes at the end of the vector
        */
        void addelements(int num);

        /**
        * Utilizes path compression to find the up-tree
        * in which the parameter element resides
        * @return the root of the previously mentioned up-tree
        */
        int find(int elem);

        /**
        * Unify two disjoint sets through union-by-size
        */
        void setunion(int a, int b);

        /**
        * @return the number of nodes in the up-tree
        * containing the passed-in element
        */
        int size(int elem);

    private:
        std::vector<int> nodes;
};