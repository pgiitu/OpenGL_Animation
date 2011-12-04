/*
 * Room.h
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */

#ifndef Room_H_
#define Room_H_

/*
 * Room.cpp
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */






// A Room class.  A Room has alternating red and white
// squares.  The number of squares is set in the constructor.  Each square
// is 1 x 1.  One corner of the board is (0, 0) and the board stretches out
// along positive x and positive z.  It rests on the xz plane.  I put a
// spotlight at (4, 3, 7).
class Room {
public:
  int displayListId;
  int width;
  int depth;
  int height;
public:
  Room(int width, int depth,int height);
  double centerx();
  double centerz();
  void create();
  void draw();
};


#endif /* Room_H_ */
