/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    //initialize rows and columns to fill in the mosaic canvas
    int rows = theSource.getRows();
    int cols = theSource.getColumns();

    //initialize the canvas to be created
    MosaicCanvas* theCanvas = new MosaicCanvas(rows, cols);

    //create a map to find color of tiles in the mosaic
    map<Point<3>, int> mapTileColors;
    
    //create a vector to hold all of the points that are created from the LUVAPixels in theTiles
    vector<Point<3>> colorsToPoints;

    //go over the tiles and convert LUVAPixels to points 
    for(unsigned i = 0; i < theTiles.size(); i++){
        //create a new Point from the current LUVAPixel
        Point<3> newPoint = convertToXYZ(theTiles[i].getAverageColor());
        //store the point in the previously created vector
        colorsToPoints.push_back(newPoint);
        //map the Point to this index to retrieve the color later
        mapTileColors[colorsToPoints[i]] = i;
    }
    
    //create a KDTree to store all of the points representing colors so they can be easily accessed later
    KDTree<3> colores(colorsToPoints);
    //run a nested loop over the rows and columns to create the Mosaic
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            TileImage* current = findTile(theSource, theTiles, colores, mapTileColors, i, j);
            theCanvas->setTile(i, j, current);
        }
    }
    return theCanvas;
}
TileImage* findTile(SourceImage const& theSource, vector<TileImage>& theTiles, const KDTree<3> neighbors, map<Point<3>, int> colorFinder, int row, int col){
     //create a LUVAPixel that is the color on the average color on the Source Image
    LUVAPixel color = theSource.getRegionColor(row, col);
    //create a point that represents the average color
    Point<3> conPoint = convertToXYZ(color);
    //find the nearest point to that color so that we can use it
    Point<3> homie = neighbors.findNearestNeighbor(conPoint);
    //find the index that was saved in the map for this point
    int idx = colorFinder[homie];
    //@return the address of the tile represented by the previously found point
    return &theTiles[idx];
}