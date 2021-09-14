#include "intro.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <cstdlib>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG img;
  bool fromfile = img.readFromFile(inputFile);
  if(fromfile == false){
    std::cout << "I'm sorry, your file was unable to be read" << std::endl;
    return;
  }

  cs225::PNG copy(img);

    for(unsigned int x = 0; x < img.width(); x++){
      for(unsigned int y = 0; y < img.height(); y++){
        cs225::HSLAPixel *beginning = &(img.getPixel(x, y));
        cs225::HSLAPixel *ending = &(copy.getPixel(img.width() - x - 1, img.height() - y - 1));
        *beginning = *ending;
      }
    }
  bool received = img.writeToFile(outputFile);
  if(!received){
    std::cout << "Unable to write your file" << std::endl;
  }
  return;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  unsigned int centerX = width/2;
  unsigned int centerY = height/2;
  unsigned int* lvlwo = NULL;
  unsigned int* lvlho = NULL;
  for(unsigned int x = 0; x < png.width() * 0.75; x++){
    for(unsigned int y = 0; y < png.height() * 0.75; y++){
      cs225::HSLAPixel& myPixel = (png.getPixel(x,y));
      unsigned int xdist = centerX - x;
      unsigned int ydist = centerY - y;
      unsigned int squarex = xdist * xdist;
      unsigned int squarey = ydist * ydist;
      unsigned int sumdist = squarex + squarey;
      double edist = sqrt(sumdist);
      if(edist < 200){
        myPixel.h = 70;
        myPixel.l = .5;
        myPixel.s = 1.0;
        myPixel.a = 1.0;
      }else{
        myPixel.h = 193;
        myPixel.s = 1.0;
        myPixel.l = 0.5;
        myPixel.a = 1.0;
      }
      unsigned int* lvlw = &x;
      unsigned int* lvlh = &y;
      lvlwo = lvlw;
      lvlho = lvlh;
    }
  }
  for(unsigned int x = (*lvlwo); x < png.width(); x++){
    for(unsigned int y = (*lvlho); y < png.height(); y++){
      cs225::HSLAPixel& myPixel = (png.getPixel(x,y));
      myPixel.h = 108;
      myPixel.s = 0.5;
      myPixel.l = 0.37;
      myPixel.a = 1.0;
    }
  }
  return png;
}
