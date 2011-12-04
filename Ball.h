/*
 * ball.h
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */

#ifndef BALL_H_
#define BALL_H_

/*
 * ball.cpp
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */

#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include "Vector.h"
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

using namespace std;

#define factor 0.1000


// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.

class Ball {
public:
  double radius;
  GLfloat* color;
  double maximumHeight;
  double x;
  double y;
  double z;
  double inc_factor;  //for the increment in motion
  Vector v;  //for the direction
  double mass;
  double gravity;
  double time;
  double speed;
  int flag;
  Vector starting;
  Vector starting_v;
  int launched; //to specify whether has been launched of not. by default it is zero


/*
 * Variables for openAL
 */

  ALuint Source;
  ALuint Buffer;

  // Position of the source sound.
  ALfloat SourcePos[3];

  // Velocity of the source sound.
  ALfloat SourceVel[3];

  // Position of the Listener.
  ALfloat ListenerPos[3];

  // Velocity of the Listener.
  ALfloat ListenerVel[3];

  // Orientation of the Listener. (first 3 elements are "at", second 3 are "up")
  // Also note that these should be units of '1'.
  ALfloat ListenerOri[6];

  /*
   * Texture Variable
   */
  unsigned int g_Texture;


public:
//  int motion;
  //int direction;
public:
  Ball();
  Ball(double r, GLfloat* c, double h, double x, double z,Vector v1,double m,double s);
/*
 *   void update();
 */
	void intersection_with_walls(double width,double height);
	void set_start_position();
void intersection_with_balls(int index,Ball balls[],int no_of_balls);

void rolling(int i,Ball balls[],int no_of_balls,double width,double depth,double height);  //where the integer i represents the index of the ball in the balls array

void check_inside(double x,double y);
/*
 * ALboolean LoadALData()
 *
 *	This function will load our sample data from the disk using the Alut
 *	utility and send the data into OpenAL as a buffer. A source is then
 *	also created to play that buffer.
 */
ALboolean LoadALData(char *s);
/*
 * void SetListenerValues()
 *
 *	We already defined certain values for the Listener, but we need
 *	to tell OpenAL to use that data. This function does just that.
 */
void SetListenerValues();

void play_sound(char *s1);

/*
 * void KillALData()
 *
 *	We have allocated memory for our buffers and sources which needs
 *	to be returned to the system. This function frees that memory.
 */
void KillALData();


};


