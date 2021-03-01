#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"


int main() {

  Image alma; alma.readFromFile("alma.png");
  Image i;    i.readFromFile("i.png");
  i.scale(.27);
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 50);
  sheet.addSticker(i, 725, 50);
  sheet.addSticker(i, alma.width()/2 - 70, 20);
  Image expected = sheet.render();
  expected.writeToFile("myImage.png");
  return 0;

  return 0;
}
