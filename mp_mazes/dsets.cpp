/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num){
    //push -1 for each element as 1 is the size of their tree
    for(int i = 0; i < num; i++)
        nodes.push_back(-1);
}

int DisjointSets::find(int elem){
    //at root return the index
    if(nodes[elem] < 0)
        return elem;
    //if not at root recurse
    //update parent to be the root;
    else{
        int root = find(nodes[elem]);
        nodes[elem] = root;
        return root;
    }
}

void DisjointSets::setunion(int a, int b){
    int root1 = find(a);
    int root2 = find(b);

    //find the new size of smartUnion
    int size2 = nodes[root1] + nodes[root2];
    
    //nothing to do if they are already in the same set
    if(root1 == root2)
        return;

    //if root1 is more negative, it becomes the root of the union
    if(nodes[root1] <= nodes[root2]){
        nodes[root2] = root1;
        //increase size to account for union
        nodes[root1] = size2;
    }
    //else root 2 becomes the root of the union
    else{
        nodes[root1] = root2;
        nodes[root2] = size2;
    }
}

int DisjointSets::size(int elem){
    //return nodes.size();
    //if the value at the passed in element is negative, at a root
    //sizes will be negative, make sure to return them as positive
    if(nodes[elem] < 0)
        return (-nodes[elem]);
    //else check the parent node
    else
        return size(nodes[elem]);
}