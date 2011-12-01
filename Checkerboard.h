/*
 * CheckerBoard.h
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */

#ifndef CHECKERBOARD_H_
#define CHECKERBOARD_H_

/*
 * CheckerBoard.cpp
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */

#include "Checkerboard.h"





// A checkerboard class.  A checkerboard has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).
class Checkerboard {
public:
  int displayListId;
  int width;
  int depth;
public:
  Checkerboard(int width, int depth);
  double centerx();
  double centerz();
  void create();
  void draw();
};


#endif /* CHECKERBOARD_H_ */
