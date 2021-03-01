#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG input;
  input.readFromFile(inputFile);
  unsigned width = input.width();
  unsigned height = input.height();
  cs225::PNG* output = new cs225::PNG(width, height);
  for (unsigned x = 0; x < width; x++){
    for (unsigned y = 0; y < height; y++) {
      cs225::HSLAPixel& inputPixel = input.getPixel(x, y);
      output->getPixel(width - x -1, height - y - 1) = inputPixel;
    }
  }
  output->writeToFile(outputFile);
  delete output;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG output(width, height);
  // TODO: Part 3
  int modulator = 1;
  for (unsigned i = 0; i < width; i++) {
    for (unsigned j = 0; j < height; j++) {
      if (i != 0 && j != 0) {
        if (i*j % 360 == 0) {
          modulator += 1;
        }
      }
      if (modulator % 2 == 1) {
        output.getPixel(i, j).h = ((i*j) % 360);
        output.getPixel(i, j).s = .5;
        output.getPixel(i, j).l = .5;
        output.getPixel(i, j).a = 1;
        modulator += 1;
      } else if (modulator % 2 == 0) {
        output.getPixel(i, j).h = 360 - ((i*j) % 360);
        output.getPixel(i, j).s = .5;
        output.getPixel(i, j).l = .5;
        output.getPixel(i, j).a = 1;
      } 
      
      //* if ((i*j) % 7 == 2) {
      //*  output.getPixel(i, j).h = 240;
      //*  output.getPixel(i, j).s = .5;
      //*  output.getPixel(i, j).l = .5;
      //*  output.getPixel(i, j).a = 1;
      //*} else if (i*j*i%7 == 3) {
      //*  output.getPixel(i, j).h = 200;
      //*  output.getPixel(i, j).s = .5;
      //*  output.getPixel(i, j).l = .5;
      //*  output.getPixel(i, j).a = 1;
      //*} else if (i % 7 == 4) {
      //*  output.getPixel(i, j).h = j / i;
      //*  output.getPixel(i, j).s = .5;
      //*  output.getPixel(i, j).l = .5;
      //*  output.getPixel(i, j).a = 1;
      //*} else {
      //*  output.getPixel(i, j).h = (i);
      //*  output.getPixel(i, j).s = .5;
      //*  output.getPixel(i, j).l = .5;
       //* output.getPixel(i, j).a = 1;
      //*}
    }
  }
  return output;
}
