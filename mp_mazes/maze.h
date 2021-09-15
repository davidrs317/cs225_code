#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>


using std::vector;
using namespace cs225;

class SquareMaze{
    public:
        /**
         * no parameter constructor
         * creates an empty maze
         */
        SquareMaze();
        /**
         * determine whether it is possible to travel in a given direction
         */
        bool canTravel(int x, int y, int dir) const;
        /**
         * draw the maze without its solution
         */
        PNG* drawMaze() const;
        /**
         * draw the maze with its solution
         */
        PNG* drawMazeWithSolution();
        /**
         * make a new Square Maze of given height and width
         */
        void makeMaze(int width, int height);
        /**
         * set whether or not the specified wall exists
         */
        void setWall(int x, int y, int dir, bool exists);
        /**
         * returns the vector of directions that provide the longest path
         */
        vector<int> solveMaze();


    private:
        /** private class that holds the status of walls
         * and whether or not a cell has been visited
         */
        class Node{
            public:
                Node();

                bool bwall;

                bool rwall;

                bool visited;
        };
        /**
         * private function that returns the index at a given point
         */
        int locate(int x, int y);
        /**
         * holds all cells of a SquareMaze
         */
        vector<vector<Node>> amaze;
        /**
         * used to make sure the SquareMaze is connected
         */
        DisjointSets cycle;
        /**
         * used to hold current best paths
         */
        vector<int> path;
        /**
         * holds the winning path
         */
        vector<int> solved;
        /**
         * width of the squareMaze
         */
        int width_;
        /**
         * height of the square maze
         */
        int height_;
        /**
         * used by solveMaze to show what the previous x value was
         */
        int xprev;
        /**
         * used by solveMaze to provide previous y value for calculations
         */
        int yprev;
        /**
         * helper function that clears any old data
         */
        void clearOld();
        /**
         * helper function that sets all walls in a maze to true
         */
        void setMaze();
        /**
         * helper function that randomly removes walls in a maze
         */
        void clearWalls();

        /**
         * helper function for solveMaze()
         */
        void solve(int x, int y, vector<int>& xcoords, vector<int>& ycoords, int dir);
        /**
         * helper function color a horizontal line in the solution red
         */
        static void hor_red(int x, int y, PNG*& p);
        /**
         * helper function to color a vertical line in the solution red
         */
        static void vert_red(int x, int y, PNG*& p);

};
