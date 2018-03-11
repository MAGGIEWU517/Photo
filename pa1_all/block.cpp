#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "block.h"

using namespace cs221util;
using namespace std;


/**
 * @ Returns the width of the current block.
**/
int Block::width() const{
   int w = data[0].size();
   return w;
}
/**
 * @ Returns the height of the current block.
**/
int Block::height() const{
   int h = data.size();
   return h;
}
/**
 *Draws the current block at position (upLeftX,upLeftY) in im.
 *& im is address of image 
**/
void Block::render(PNG & im, int upLeftX, int upLeftY) const {
   for(int y = 0; y < height(); y++){
    for(int x = 0; x < width(); x++){
    int positionx= upLeftX + x;
    int positiony = upLeftY +y;
    *im.getPixel(positionx,positiony) = data[y][x];
    }
   }
   /* your code here */
   return;
}
/**
 * From im, grabs the rows by cols block of pixels whose upper left corner is position
 * (upLeftX,upLeftY).
**/

void Block::build(PNG & im, int upLeftX, int upLeftY, int cols, int rows) {

   for(int y = 0; y < rows; y++){
   vector < HSLAPixel > data2;
    for(int x = 0; x< cols; x++){
    
        data2.push_back(*im.getPixel(upLeftX+x,upLeftY+y));      
    }   
   data.push_back(data2);
   }
   /* your code here */
   return;
}
