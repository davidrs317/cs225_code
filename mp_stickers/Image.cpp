#include "Image.h"
#include <cmath>

void Image::lighten(){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(pixel.l < 1.0){
        pixel.l += 0.1;
      }
      if(pixel.l > 1){
        pixel.l = 1.0;
      }

    }
  }
}

void Image::lighten(double amount){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      if(pixel.l < 1.0){
        pixel.l += amount;
      }
      if(pixel.l > 1.0){
        pixel.l = 1.0;
      }
    }
  }
}

void Image::darken(){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(pixel.l > 0.0){
        pixel.l -= 0.1;
      }
      if(pixel.l < 0.0){
        pixel.l = 0.0;
      }
    }
  }
}

void Image::darken(double amount){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      if(pixel.l > 0.0){
        pixel.l -= amount;
      }
      if(pixel.l < 0.0){
        pixel.l = 0.0;
      }
    }
  }
}

void Image::saturate(){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.s += 0.1;
      if(pixel.s > 1)
        pixel.s = 1;
      if(pixel.s < 0)
        pixel.s = 0;
    }
  }
}

void Image::saturate(double amount){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(((pixel.s + amount) <= 1.0) && ((pixel.l + amount) >= 0.0)){
        pixel.s += amount;
      }
    }
  }
}

void Image::desaturate(){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(pixel.s >= 0.1){
        pixel.s -= 0.1;
      }
    }
  }
}

void Image::desaturate(double amount){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(((pixel.s - amount) >= 0) && ((pixel.s - amount) <= 1.0)){
        pixel.s -= amount;
      }
    }
  }
}

void Image::grayscale(){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double amount){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      double value = amount + pixel.h;
      if(value > 360.0){
        double addend = value - 360.0;
        pixel.h = addend;
      }
      else if(value < 0.0){
        double sub = 360.0 + value;
        pixel.h = sub;
      }
      else{
        pixel.h = value;
      }
    }
  }
}

void Image::illinify(){
  for(unsigned x = 0; x < width(); x++){
    for(unsigned y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x, y);

      if(pixel.h >= 294){
        pixel.h = 11;
      }
      if(pixel.h >= 114){
        pixel.h = 216;
      }
      if(pixel.h <= 113){
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double factor){
  int w1 = factor * width();
  int h1 = factor * height();
  cs225::PNG* next_img = new PNG(*this);
  //set PNG to be updated heights and widths
  resize(w1, h1);
  //iterate over the current image to find the new x and y coordinates determined by the factor
  for(unsigned x = 0; x < this->width(); x++){
    for(unsigned y = 0; y < this->height(); y++){
      unsigned xer = (1.0*x) / factor;
      unsigned yer = (1.0*y) / factor;

      //set the old pixel to be the new pixel from the updated coordinates
      cs225::HSLAPixel & p1 = this->getPixel(x, y);
      cs225::HSLAPixel & p2 = next_img->getPixel(xer, yer);
      p1 = p2;
    }
  }
 
}

void Image::scale(unsigned w, unsigned int h){
  //generate factors for height and width
  double w_fact = (1.0 * w) / this->width();
  double h_fact = (1.0 * h) / this -> height();

  cs225::PNG * next_img = new PNG(*this);
  //set PNG to be updated height and width
  resize(w, h);

  //iterate over the current image to find the new x and y coordinates determined by the 
  //passed in height and width
  for(unsigned x = 0; x < this->width(); x++){
    for(unsigned y = 0; y < this->height(); x++){
      unsigned xer = (1.0 * x) / w_fact;
      unsigned yer = (1.0 * y) / h_fact;

      //set the image's pixels to be the pixels from the updated coordinates
      cs225::HSLAPixel & p1 = this->getPixel(x, y);
      cs225::HSLAPixel & p2 = next_img->getPixel(xer, yer);
      p1 = p2;
    }
  }
  
}
