#include "StickerSheet.h"
#include "cs225/PNG.h"

StickerSheet::StickerSheet(const Image & picture, unsigned max){
  //create new arrays to hold coordinates and stickers
  //initialize all values to NULL except for base layer
  //which will be the image passed in
  _stickers = new Image*[max];
  Image* curr = new Image(picture);
  base_ = curr;

  for(unsigned i = 0; i < max; i++)
    _stickers[i] = nullptr;

  _xcoord = new unsigned[max];
  _xcoord[0] = 0;
  _ycoord = new unsigned[max];
  _ycoord[0] = 0;
  max_ = max;
}

StickerSheet::~StickerSheet(){
  _clearSheet();
}

StickerSheet::StickerSheet(const StickerSheet & other){
  _clearSheet();
  _copySheet(other);
}

const StickerSheet& StickerSheet::operator=(const StickerSheet & other){
  if(this != &other){
    _clearSheet();
    _copySheet(other);
  }
  return *this;
}

//add sticker at the closest spot, else return -1 if no spots are open
int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y){
  bool check = false;
  unsigned index = 0;
  //iterate over the array to find the closest free spot
  for(index = 0; index < max_; index++){
    if(_stickers[index] == nullptr){
      Image* newbie = new Image(sticker);
      _stickers[index] = newbie;
      _xcoord[index] = x;
      _ycoord[index] = y;
      check = true;
      break;
    }
  }

  //if no free spot found return -1
  if(check == false)
    return -1;
  
  return index;
}

void StickerSheet::changeMaxStickers(unsigned max){
  if(max == max_)
    return;
  
  //create new arrays of updated size
  unsigned omax = max_;
  Image** stickers2 = new Image*[max];
  unsigned* xcoord2 = new unsigned[max];
  unsigned* ycoord2 = new unsigned[max];

  if(max > max_)
    omax = max;
  
  //iterate and assign all values from old array to new array or null to expanded values
  //deleting values that are at a location greater than the new size
  for(unsigned i = 0; i < omax; i++){
    if(i < max && i < max_){
      stickers2[i] = _stickers[i];
      xcoord2[i] = _xcoord[i];
      ycoord2[i] = _ycoord[i];
    }else if(i < max_)
      delete _stickers[i];
    else if(i < max)
      stickers2[i] = nullptr;
    else if(i > max)
      break;
  }
  //reassign member variables to new values and update max
  _updater(stickers2, xcoord2, ycoord2);
  max_ = max;
}

Image* StickerSheet::getSticker(unsigned index){
  if(index > max_)
    return nullptr;
  
  return _stickers[index];
}

void StickerSheet::removeSticker(unsigned index){
  if(index > max_)
    return;
  

  if(_stickers[index] == nullptr)
    return;

  delete _stickers[index];
  _stickers[index] = nullptr;

  //move all values back one index to maintain original indices following removal
  for(unsigned i = index; i < max_ - 1; i++){
    _stickers[i] = _stickers[i+1];
    _xcoord[i] = _xcoord[i+1];
    _ycoord[i] = _ycoord[i+1];
  }

  _stickers[max_ - 1] = nullptr;
}

Image StickerSheet::render() const{
  unsigned Xmaxi = 0;
  unsigned Ymaxi = 0;

  //iterate over all the possible heights and widths
  //to find the greatest possible x and y values
  for(unsigned i = 0; i < max_; i++){
    if(_stickers[i] != nullptr){
      unsigned width = _stickers[i]->width() + _xcoord[i];
      unsigned height = _stickers[i]->height() + _ycoord[i];

      if(Xmaxi < width)
        Xmaxi = width;
      if(Ymaxi < height)
        Ymaxi = height;
    }
  }

  unsigned width = base_->width();
  unsigned height = base_->height();
  //want final height and width to be maximum x and y values
  if(width < Xmaxi)
    width = Xmaxi;
  if(height < Ymaxi)
    height = Ymaxi;
  
  Image newbie(width, height);

  //iterate over base to create new picture that appears the same
  for(unsigned x = 0; x < base_->width(); x++){
    for(unsigned y = 0; y < base_->height(); y++){
      newbie.getPixel(x, y) = base_->getPixel(x, y);
    }
  }

  //iterate over all of the stickers to find to write them onto the new Image
  for(unsigned i = 0; i < max_; i++){
    if(_stickers[i] != nullptr){
      for(unsigned x = 0; x < _stickers[i]->width(); x++){
        for(unsigned y = 0; y < _stickers[i]->height(); y++){
          if(_stickers[i]->getPixel(x,y).a != 0)
            newbie.getPixel(x + _xcoord[i], y + _ycoord[i]) = _stickers[i]->getPixel(x, y);
        }
      }
    }
  }
  return newbie;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(_stickers == nullptr)
    return false;
  if(index >= max_)
    return false;
  if(_stickers[index] == nullptr)
    return false;
  
  //assign new x and y values to the given index
  _xcoord[index] = x;
  _ycoord[index] = y;
  return true;
}

void StickerSheet::_clearSheet(){
  if(_stickers == nullptr)
    return;
  
  //remove all stickers
  for(unsigned i = 0; i < max_; i++){
    if(_stickers[i] != nullptr)
      delete _stickers[i];
  }

  //update each array to null
 _updater(nullptr, nullptr, nullptr);
 max_ = 0;
}

void StickerSheet::_copySheet(const StickerSheet & other){
  max_ = other.max_;
  _stickers = new Image*[max_];
  _xcoord = new unsigned[max_];
  _ycoord = new unsigned[max_];
  base_ = new Image(*other.base_);

  //deep copy of each sticker and coordinate
  for(unsigned i = 0; i < max_; i++){
    if(other._stickers[i] != nullptr){
      _stickers[i] = new Image(*other._stickers[i]);
      _xcoord[i] = other._xcoord[i];
      _ycoord[i] = other._ycoord[i];
    }else
      _stickers[i] = nullptr;
  }
}

void StickerSheet::_updater(Image** stickers, unsigned* xcoord, unsigned* ycoord){
  delete[] _stickers;
  _stickers = stickers;
  delete[] _xcoord;
  _xcoord = xcoord;
  delete[] _ycoord;
  _ycoord = ycoord;
}