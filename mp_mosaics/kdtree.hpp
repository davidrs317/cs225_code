/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    double valone = first[curDim];
    double valtwo = second[curDim];

    if(valone == valtwo)
      return first < second;
    
    return valone < valtwo;
    
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double dist_Pot = find_Dist(target, potential);
    double dist_Cur = find_Dist(target, currentBest);

    if(dist_Pot < dist_Cur)
      return true;
    else if(dist_Pot > dist_Cur)
      return false;
    else 
      return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    if(newPoints.empty() == true){
      root = NULL;
      return;
    }
    //have to pass in the vector as a copy to avoid the const restriction on the passed in vector
    vector<Point<Dim>> points(newPoints);
    buildTree(points, 0, 0, points.size() - 1, root);
}   

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  _copy(other.root, root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  //to set one tree equal to another clear the old tree and copy the new tree into it
  _clear(root);
  _copy(rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    //utilize the helper function
    return nearestNeighbor(query, 0, root);
}

template <int Dim>
double KDTree<Dim>::find_Dist(const Point<Dim>& first, const Point<Dim>& sec) const{
  double dist = 0;
  for(int i = 0; i < Dim; i++)
    dist = dist + ((first[i] - sec[i]) * (first[i] - sec[i]));
  
  return dist;
}

template <int Dim>
//need to pass in the KDTreeNode* as a reference so that it refers to a consistent root of the tree
void KDTree<Dim>::buildTree(vector<Point<Dim>>& points, int dim ,int left, int right, KDTreeNode*& curRoot){
  //followed the pseudocode given in lab
  if(left <= right){
    int middle = (left + right)/2;
    //rearrange points according to quickSort algorithm
    curRoot = new KDTreeNode(quickSelect(points, left, right, middle, dim)); //curRoot is new KDTreeNode at middle point?
    size++;

    //recurse left subtree on (dim+1) % Dim
    buildTree(points, (dim+1) % Dim, left, middle-1, curRoot->left);
    buildTree(points, (dim+1) % Dim, middle+1, right, curRoot->right);
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& points, int left, int right, int k, int dim){
  //followed the recursive pseducode from wikipedia, made more sense to do it this way
  if (left == right)
    return points[left];
  //set pivotIndex to any value between left and right
  int pivotIndex = left + rand() % (right - left +1);
  //find a new pivotIndex with the partition function
  pivotIndex = partitioner(points, left, right, pivotIndex, dim);
  //case in which we've found the index
  if(k == pivotIndex)
    return points[k];
  //smaller index recursive case
  else if(k < pivotIndex)
    return quickSelect(points, left, pivotIndex-1, k, dim);
  //larger index recursive case
  else
    return quickSelect(points, pivotIndex+1, right, k, dim);
  
}

template <int Dim>
int KDTree<Dim>::partitioner(vector<Point<Dim>>& points, int left, int right, int pivotIndex, int dim){
  //swap pivotValue and right point
  Point<Dim> pivotValue = points[pivotIndex];
  points[pivotIndex] = points[right];
  points[right] = pivotValue;

  //create a left index to access later and a point to use for swapping in lieu of a helper function
  int storeIndex = left;
  Point<Dim> swapper;

  for(int i = left; i <= right-1; i++){
    //swap if points[i] is smaller than pivotValue, from algorithm on wikipedia and in AMA
    if(smallerDimVal(points[i], pivotValue, dim)){

      swapper = points[storeIndex];
      points[storeIndex] = points[i];
      points[i] = swapper;
      storeIndex++;

    }
  }
  //final swap
  swapper = points[storeIndex];
  points[storeIndex] = points[right];
  points[right] = swapper;
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::nearestNeighbor(const Point<Dim>& query, int dim, KDTreeNode* curRoot) const{
  //if there are no children, the curRoot is the closest point
  //based on algorithm from AMA
  if(curRoot->left == nullptr && curRoot->right == nullptr)
    return curRoot->point;

  //create a nearest Point and a KDTreeNode* to use in order to recursively explore other branch for a nearestNeighbor
  Point<Dim> nearest;
  KDTreeNode* oside = nullptr;
  if(smallerDimVal(query, curRoot->point, dim)){
    if(curRoot->left != nullptr)
      //if smaller explore the left subtree
      nearest = nearestNeighbor(query, (dim + 1) % Dim, curRoot->left);
    else
      //set nearest to curRoot->point to avoid any issues with setting tiles
      nearest = curRoot->point;
    if(curRoot->right != nullptr)
      //set the KDTreeNode* initialized earlier for exploring the other tree
      oside = curRoot->right;
  }else{
    //else explore the right subtree
    if(curRoot->right != nullptr)
      nearest = nearestNeighbor(query, (dim+1) % Dim, curRoot->right);
    else
      nearest = curRoot->point;
    if(curRoot->left != nullptr)
      oside = curRoot->left;
    
  }

  double nearDist = find_Dist(nearest, query);
  //do a final check of the curRoot point to see if it is nearer or not
  if(shouldReplace(query, nearest, curRoot->point))
    nearest = curRoot->point;
  
  double splitDist = (curRoot->point[dim] - query[dim]) * (curRoot->point[dim] - query[dim]);
  if(splitDist <= nearDist && oside != nullptr){
    //need to check other branch in this case
    Point<Dim> tempNearest = nearestNeighbor(query, (dim + 1) % Dim, oside);
    if(shouldReplace(query, nearest, tempNearest))
      nearest = tempNearest;
  }
  return nearest;

}

template <int Dim>
void KDTree<Dim>::_clear(KDTreeNode*& curRoot){
  if(curRoot == nullptr)
    return;
  if(curRoot->left == nullptr && curRoot->right == nullptr){
    delete curRoot;
    curRoot = nullptr;
    return;
  }
  _clear(curRoot->left);
  _clear(curRoot->right);
  delete curRoot; 
  curRoot = nullptr;
  size = 0;
}

template <int Dim>
void KDTree<Dim>::_copy(const KDTreeNode* curRoot, KDTreeNode*& newbie){
  if(curRoot == nullptr)
    return;
  
  newbie = new KDTreeNode(curRoot->point);
  _copy(curRoot->left, newbie->left);
  _copy(curRoot->right, newbie->right);
}