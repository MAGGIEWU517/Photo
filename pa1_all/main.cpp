/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include "block.h"
#include "PNGutil.h"
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

int main() {
   PNG png1;

   png1.readFromFile("images/rosegarden.png");
   PNG result1 = grayscale(png1);
   result1.writeToFile("images/out-ubcRose.png");
   
   Block b;
   b.build(png1,0,150,450,225);
   b.render(result1,450,300);
   result1.writeToFile("images/out-blocktest.png");


   cout<<"Block is fine"<<endl;
   Chain c(png1,1,16);
   PNG test = c.render(1,16);
   test.writeToFile("images/c.png");
   for (int i = 1; i <c.size(); i*=2){
      c.moveToBack(1+c.size()*(i-1)/i, c.size()/(2*i));
   }
   PNG result2 = c.render(1,16);
   result2.writeToFile("images/out-moveToBack.png");
   cout<<"MOVETOBACK is fine"<<endl;


   Chain d(png1,2,8);
   d.swap(2,15);
   PNG result3 = d.render(2,8);
   result3.writeToFile("images/out-swapEasy.png");
   cout<<"SWAP IS FINE"<<endl;

 
   Chain e(png1,4,18);
   PNG resulte = e.render(4,18);
   resulte.writeToFile("images/e.png");
   Chain g(e);
   PNG resultg = g.render(4,18);
   resultg.writeToFile("images/g.png");
   Chain f(result1,4,18);
   PNG resultf = f.render(4,18);
   resultf.writeToFile("images/f.png");
   

   g.twist(f);
   PNG result6 = g.render(4,18);
   PNG result7 = f.render(4,18);

   result6.writeToFile("images/out-twistSame1.png");
   result7.writeToFile("images/out-twistSame2.png");
   cout<<"Twist is Fine"<<endl;

   Chain c1(png1, 1, 16);
   Chain c2(png1, 2, 8);
   Chain c3 (result1, 2,8);
   PNG resultc1 = c1.render(1,16);
   PNG resultc2 = c2.render(2,8);
   PNG resultc3 = c3.render(2,8);
   resultc1.writeToFile("images/c1.png");
   resultc2.writeToFile("images/c2.png");
   resultc3.writeToFile("images/c3.png");
   

   c1 = c2;
   PNG resultc12 = c1.render(2,8);
   resultc12.writeToFile("images/c12.png");

   c3 = c2;
   PNG resultc32 = c3.render(2,8);
   resultc32.writeToFile("images/c32.png");




   return 0;
}
