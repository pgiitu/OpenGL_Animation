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
#include "intersection_point.h"
#include "ray.h"
#include "vector.h"
#include <stdio.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include "texture.h"

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
  double minimumHeight;
  double x;
  double y;
  double z;
  double inc_factor;  //for the increment in motion
  vector v;  //for the direction
  int direction;
  double mass;
  double theta;
  double gravity;
  double time;
  int flag;
  vector starting;
  vector starting_v;
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

  //for texture
  unsigned int g_Texture;



public:
  int motion;
public:
  Ball(double r, GLfloat* c, double h, double x, double z,double t,double m);
  void update();
	void intersection_with_walls(double width,double height);
	void set_start_position();
void intersection_with_balls(int index,Ball balls[],int no_of_balls);

void rolling(int i,Ball balls[],int no_of_balls,double width,double height);  //where the integer i represents the index of the ball in the balls array

void initialize_texture();
void check_inside(double x,double y);
/*
 * ALboolean LoadALData()
 *
 *	This function will load our sample data from the disk using the Alut
 *	utility and send the data into OpenAL as a buffer. A source is then
 *	also created to play that buffer.
 */
ALboolean LoadALData();
/*
 * void SetListenerValues()
 *
 *	We already defined certain values for the Listener, but we need
 *	to tell OpenAL to use that data. This function does just that.
 */
void SetListenerValues();



/*
 * void KillALData()
 *
 *	We have allocated memory for our buffers and sources which needs
 *	to be returned to the system. This function frees that memory.
 */
void KillALData();


};


