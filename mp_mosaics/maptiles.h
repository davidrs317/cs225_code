/**
 * @file maptiles.h
 *
 * mapTiles() function.
 * Developed for CS225 PhotoMosaic MP
 *
 * @author Jack Toole
 * @date Fall 2011
 */

#pragma once

#include <map>
#include <vector>
#include "cs225/PNG.h"
#include "kdtree.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "tileimage.h"

using namespace std;
using namespace cs225;

/**
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 *
 * @todo This function is required for Part 2.
 * @param theSource The input image to construct a photomosaic of
 * @param theTiles The tiles image to use in the mosaic
 */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> & theTiles);

// TODO: move this comment back to inline above once someone figures out unidef-like real directive parsing
// SOLUTION
//PRIVATE HELPER FUNCTION
/**
 * this is a function to find the correct tile to put in the canvas at a certain point
 */
TileImage* findTile(SourceImage const& theSource, vector<TileImage>& theTiles, const KDTree<3> neighbors, map<Point<3>, int> colorFinder, int row, int col);