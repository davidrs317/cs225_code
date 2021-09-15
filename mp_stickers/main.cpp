#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"

int main() {
  Image base;
  base.readFromFile("therealpic.png");
  StickerSheet here(base, 1);
  Image primeroS;
  primeroS.readFromFile("i.png");
  here.addSticker(primeroS, 0, 0);
  Image done = here.render();
  done.writeToFile("myImage.png");
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
