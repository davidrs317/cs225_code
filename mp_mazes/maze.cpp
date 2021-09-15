#include "maze.h"

using std::vector;


SquareMaze::SquareMaze(){
    srand(time(NULL));
}

SquareMaze::Node::Node(){
    //initialize all walls to tru
    bwall = true;
    rwall = true;
    visited = false;
}

void SquareMaze::clearOld(){
    //clear any old vectors out
    amaze.clear();
    path.clear();
    solved.clear();
}

void SquareMaze::setMaze(){
    //create maze full of walls
    vector<Node> nodeHold;
    for(int i = 0; i < width_; i++){
        for(int j = 0; j < height_; j++){
            nodeHold.push_back(Node());
        }
        amaze.push_back(nodeHold);
    }
}

int SquareMaze::locate(int x, int y){
    return (x+width_*y);
}

void SquareMaze::clearWalls(){
    int trueSize = width_*height_;
    int i, j, dk;
    while(cycle.size(0) < trueSize){
        i = rand()%width_;
        j = rand()%height_;
        dk = rand()%2;
        //check right wall
        if(dk == 0 && i != width_-1){
            int idx = locate(i, j);
            int nidx = locate(i+1, j);
            if(cycle.find(idx) != cycle.find(nidx)){
                //setWall(i, j, 0, false);
                amaze[i][j].rwall = false;
                cycle.setunion(idx, nidx);
            }
        }
        //check down wall
        else if(dk == 1 && j != height_-1){
            int idx = locate(i, j);
            int nidx = locate(i, j+1);
            if(cycle.find(idx) != cycle.find(nidx)){
                //setWall(i, j, 1, false);
                amaze[i][j].bwall = false;
                cycle.setunion(idx, nidx);
            }
        }
    }
}

void SquareMaze::makeMaze(int width, int height){
    width_ = width;
    height_ = height;

    clearOld();
    setMaze();
    cycle.addelements(width_ * height_);
    clearWalls();

}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    //check if setting right wall
    if(dir == 0){
        if(exists == true)
            amaze[x][y].rwall = true;
        else
            amaze[x][y].rwall = false;
    }    
    //check if setting bottom wall
    else if(dir == 1){
        if(exists == true)
            amaze[x][y].bwall = true;
        else
            amaze[x][y].bwall = false;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    //if going right
    if(dir == 0){
        if(x >= width_-1)
            return false;
        if(amaze[x][y].rwall == true)
            return false;
        return true;
    }
    //if going down
    else if(dir == 1){
        if(y >= height_-1)
            return false;
        if(amaze[x][y].bwall == true)
            return false;
        return true;
    }
    //if going left
    else if(dir == 2){
        if (x <= 0)
            return false;
        if(amaze[x-1][y].rwall == true)
            return false;
        return true;
    }
    //if going up
    else if(dir == 3){
        if(y <= 0)
            return false;
        if(amaze[x][y-1].bwall == true)
            return false;
        return true;
    }
    else{
        return false;
    }
    
}

void SquareMaze::solve(int x, int y, vector<int>& xcoords, vector<int>& ycoords, int dir){
    path.push_back(dir);
    //vectors to hold x and y coordinates
    xcoords.push_back(x);
    ycoords.push_back(y);
    //make sure the current node has been marked as visited so it isn't checked again
    amaze[x][y].visited = true;

    if(y == height_-1 && path.size() > 0){
        //increment y count
        yprev++;
        if(solved.size() <= path.size()){
            if(solved.size() == path.size()){
                if(xprev > x){
                    solved = path;
                    //want smallest x possible
                    xprev = x;
                }
            }
            else{
                solved = path;
                xprev = x;
            }
        }
    }
}

vector<int> SquareMaze::solveMaze(){
    //start ycount at 0 with largest x possible
    yprev = 0; xprev = INT_MAX;
    int x = 0;
    int y = 0; 
    int backtrack = 0;
    //vectors holding xes and ys
    vector<int> equis(1,0);
    vector<int> griega(1,0);
    
    //as long as there are x coordinates, travel is possible
    while(equis.size() != 0){
        //stop travelling if there is no where for y to go
        if(yprev == height_)
            break;
        x = equis.back();
        y = griega.back();

        //look right
        //if the direction is valid, push it to the best possible direction and 
        //compare the current path to the best possible
        if(canTravel(x, y, 0) == true && amaze[x+1][y].visited == false){
            solve(x+1, y, equis, griega, 0);
            x++;
        }
        //backtrack serves as a check for if anything was done
        else{
            backtrack++;
        }
        //look down
        //if the direction is valid, push it to the best possible direction and 
        //compare the current path to the best possible
        if(canTravel(x, y, 1) == true && amaze[x][y+1].visited == false){
            solve(x, y+1, equis, griega, 1);
            y++;
        }
        else{
            backtrack++;
        }
        //look left
        //if the direction is valid, push it to the best possible direction and 
        //compare the current path to the best possible        
        if(canTravel(x, y, 2) == true && amaze[x-1][y].visited == false){
            solve(x-1, y, equis, griega, 2);
            x--;
        }
        else{
            backtrack++;
        }
        //look up
        //if the direction is valid, push it to the best possible direction and 
        //compare the current path to the best possible        
        if(canTravel(x, y, 3) == true && amaze[x][y-1].visited == false){
            solve(x, y-1, equis, griega, 3);
            y--;
        }
        else{
            backtrack++;
        }
        //if backtrack was able to increment four times, nothing was done and the current
        //coordinates are not valid
        //prop them and go to the next iteration
        if(backtrack > 3){
            equis.pop_back();
            griega.pop_back();
            if(path.size() != 0)
                path.pop_back();
        }
        backtrack = 0;
    }
    //return the completed vector
    return solved;
    //return vector<int>();
}

PNG* SquareMaze::drawMaze() const{
    PNG* ret = new PNG(width_*10+1, height_*10+1);
    HSLAPixel b(0,0,0,1);
    HSLAPixel w(0,0,1,1);
    for(int i = 0; i < width_*10+1; i++){
        HSLAPixel& grab = ret->getPixel(i, 0);
        grab = b;
    }
    for(int i = 0; i < height_*10+1; i++){
        HSLAPixel& grab = ret->getPixel(0, i);
        grab = b;
    }
    for(int i = 1; i < 10; i++){
        HSLAPixel& grab = ret->getPixel(i, 0);
        grab = w;
    }
    for(int i = 0; i < width_; i++){
        for(int j = 0; j < height_; j++){
            if(amaze[i][j].rwall == true){
                for(int k = 0; k < 11; k++){
                    HSLAPixel& grab = ret->getPixel((i+1)*10, j*10+k);
                    //HSLAPixel& grab = ret->getPixel(i*10+k, (j+1)*10);
                    grab = b;
                }
            }
            if(amaze[i][j].bwall == true){
                for(int k = 0; k < 11; k++){
                    HSLAPixel& grab = ret->getPixel(i*10+k, (j+1)*10);
                    //HSLAPixel& grab = ret->getPixel((i+1)*10, j*10+k);
                    grab = b;
                }
            }
        }
    }
    return ret;
}

void SquareMaze::hor_red(int x, int y, PNG*& p){
    HSLAPixel r(0,1,.5,1);
    for(int i = 0; i < 11; i++){
        HSLAPixel& grab = p->getPixel(x+i, y);
        grab = r;
    }
}

void SquareMaze::vert_red(int x, int y, PNG*& p){
    HSLAPixel r(0,1,.5,1);
    for(int i = 0; i < 11; i++){
        HSLAPixel& grab = p->getPixel(x, y+i);
        grab = r;
    }
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG* ret = drawMaze();
    HSLAPixel w(0,0,1,1);
    vector<int> trueSolu = solveMaze();
    int x = 0; 
    int y = 0;

    for(int dir : trueSolu){
        if(dir == 0){
            hor_red(x*10+5, y*10+5, ret);
            x++;
        }
        if(dir == 1){
            //vert_red(x*10+5, y*10+5, ret);
            vert_red(x*10+5, y*10+5, ret);
            y++;
        }
        if(dir == 2){
            //hor_red(x*10+5, y*10+5, ret);
            hor_red(x*10+5, y*10+5, ret);
            x--;
        }
        if(dir == 3){
            //vert_red(x*10+5, y*10+5, ret);
            vert_red(x*10+5, y*10+5, ret);
            y--;
        }
    }

    for(int i = 1; i < 10; i++){
        HSLAPixel& grab = ret->getPixel(x+10*i, (y+1)*10);
        grab = w;
    }
    return ret;
}