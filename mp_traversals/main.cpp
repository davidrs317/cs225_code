
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
//create a PNG to serve as the base
PNG star(100, 100);
//create a bottom point to traverse
Point low(0, 0);
//create an upper bound to travers
Point cp(100, 100);
PNG colors;
//pull in the colors to get from MyColorPicker
colors.readFromFile("multicolor.png");
MyColorPicker hue(colors);
//call two ColorPickers
RainbowColorPicker fun(4);
//run two traversals to add fills
DFS dfs1(star, cp, .5);
BFS bfs1(star, low, 1);
FloodFilledImage newb(star);
newb.addFloodFill(dfs1, fun);
newb.addFloodFill(bfs1, hue);
//animate
Animation animation = newb.animate(1000);
PNG lastFrame = animation.getFrame(animation.frameCount() -1);
lastFrame.writeToFile("myFloodFill.png");
animation.write("myFloodFill.gif");
  return 0;
}
