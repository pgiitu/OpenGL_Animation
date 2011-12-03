/*
 * ball.cpp
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */

#include <GLUT/glut.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "intersection_point.h"
#include "ray.h"
#include "Vector.h"
#include "Ball.h"
using namespace std;

#define factor 1.000
#define gravity_factor 0.008
#define gravity_up 0.8
#define gravity_down 1.4
#define time_inc 1.0/60.0


//Acceleration due to gravity
Vector acc(0.0,-9.806,0.0);

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.

Ball::Ball()
{

}

Ball::Ball(double r, GLfloat* c, double h, double x, double z,Vector v1,double m,double s)
{

	  radius=r;
	  color=c;
	  maximumHeight=h;
	  this->y=h;
	  this->x=x;
	  this->z=z;

	  speed=s;
	  v=v1.multiply_scalar(s);
	  starting_v=v;
/*
	  v.x=8*cos(t*M_PI/180);
	  v.y=0.0;
	  v.z=8*sin(t*M_PI/180);
*/
	  inc_factor=0.08;
	  gravity=inc_factor;
	  mass=m;
	  time =0.0;
	  flag=0;
/*
	  starting.x=0.0;
	  starting.y=0.0;
	  starting.z=0.0;
*/
	  starting=v1.multiply_scalar(3);

	  //finish texture

	  for(int k=0;k<3;k++)
	  {
		  SourcePos[k]=0.0;
		  SourceVel[k]=0.0;
		  ListenerPos[k]=0.0;
		  ListenerVel[k]=0.0;
	  }

// faltu variables
	  //	  direction=1;
	  //	  motion=1;

/*
 * Code for openal(sound)
 */

	  ListenerOri[0] = 0.0;
	  ListenerOri[1]=0.0;
	  ListenerOri[2]=-1.0;
      ListenerOri[3]=0.0;
      ListenerOri[4]=1.0;
      ListenerOri[5]=0.0;

  	alutInit(NULL, 0);
  	alGetError();

  	// Load the wav data.
  	if(LoadALData() == AL_FALSE)
  	{
  	    printf("Error loading data.");
  		//return 0;
  	}

  	SetListenerValues();
  	// Setup an exit procedure.

  	//atexit(KillALData);

  }


/*
 *Extraneous function
 *Right now I am not using this function
 *
 */
void Ball::check_inside(double x1,double y1)
{
	Vector r1(this->x-x1,this->y-y1,0);
	if(r1.magnitude()<this->radius)
	{
		this->maximumHeight=this->maximumHeight+2;
		this->inc_factor=0.3;
	}
}


void Ball::set_start_position()
{
	flag=1;
}
/*
void Ball::rolling(int i,Ball balls[],int no_of_balls,double width,double height)  //where the integer i represents the index of the ball in the balls array
  {

    intersection_with_walls(width,height);
  	intersection_with_balls(i,balls,no_of_balls);

  	this->time=this->time+time_inc;
  	double t=this->time;

  	v=starting_v + acc.multiply_scalar(t);


  	Vector n1=starting + ((starting_v.multiply_scalar(t)) + (acc.multiply_scalar(0.5*t*t)));
    x=n1.x;
    y=n1.y;
    z=n1.z;

    intersection_with_walls(width,height);
  	intersection_with_balls(i,balls,no_of_balls);

    if(y<radius)
  	{
  		  v.y=-factor*v.y;
  		  maximumHeight=(v.y*v.y)/(2*9.806);
			y=radius;
  		set_start_position();
  	}
    else
    {

    	if(y>maximumHeight)
  		{
  			  v.y=0.0;
  			set_start_position();
  		}
    }

    if(flag==1)
  	{
  		time=0.0;
  		flag=0;
  		starting.x=this->x;
  		starting.y=this->y;
  		starting.z=this->z;
  		starting_v=v;
  	}

	  	glPushMatrix();
	    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	    glTranslated(x, y, z);
	    //glRotated(10,0,1.0,0);

	    glutSolidSphere(radius, 30, 30);
	    glPopMatrix();
  }
*/

void Ball::rolling(int i,Ball balls[],int no_of_balls,double width,double height)  //where the integer i represents the index of the ball in the balls array
  {

    intersection_with_walls(width,height);
  	intersection_with_balls(i,balls,no_of_balls);

    if(y<radius)
   	{
   		  v.y=-factor*v.y;
   		  maximumHeight=(v.y*v.y)/(2*9.806);
 		  y=radius;
   		  set_start_position();
   	}
     else
     {

     	if(y>maximumHeight)
   		{
   			  v.y=0.0;
   			set_start_position();
   		}
     }

    if(flag==1)
  	{
  		this->time=0.0;
  		flag=0;
  		starting.x=this->x;
  		starting.y=this->y;
  		starting.z=this->z;
  		starting_v=v;
  	}

    this->time=this->time+time_inc;
  	double t=this->time;

  	v=starting_v + acc.multiply_scalar(t);

  	Vector n1=starting + ((starting_v.multiply_scalar(t)) + (acc.multiply_scalar(0.5*t*t)));
    x=n1.x;
    y=n1.y;
    z=n1.z;

//    intersection_with_walls(width,height);
 // 	intersection_with_balls(i,balls,no_of_balls);



	  	glPushMatrix();
	    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	    glTranslated(x, y, z);
	    //glRotated(10,0,1.0,0);

	    glutSolidSphere(radius, 30, 30);
	    glPopMatrix();
  }



void Ball::intersection_with_walls(double width,double height)
{
		Vector ret=v;




		// collision with the side wall Z plane
		if(z<=radius)
		{
			v.z=-1*v.z;
			z=radius+0.001;

			set_start_position();
		}

		//collision with other side wall Z plane
		if((z+radius)>=(height-1))
		{
			v.z=-1*v.z;
			z=(height-1)-radius-0.001;

			  set_start_position();
		}

		//collision with the X Plane
		if(x<=radius)
		{
			v.x=-1*v.x;
			x=radius+0.001;

			  set_start_position();

		}

		//collision with the other X Plane
		if((x+radius)>=(width-1))
		{
			x=(width-1)-radius-0.001;
			v.x=-1*v.x;

			set_start_position();
		}
}

void Ball::intersection_with_balls(int index,Ball balls[],int no_of_balls)
{

	  double radius1=balls[index].radius;
	  Vector r1(balls[index].x,balls[index].y,balls[index].z);
	  for (int i = 0; i < no_of_balls; i++)
	  {
		  double radius2=balls[i].radius;
		  Vector r2(balls[i].x,balls[i].y,balls[i].z);
		  if(i!=index)
		  {
			  //Vector dir_centers=r1 - r2;
			  Vector dir_centers=r2 - r1;
			  double dis=dir_centers.magnitude();
			  if((radius1+radius2)>=dis)
			  {
				  alSourcePlay(Source);

				  set_start_position();

			  	  Vector dir=dir_centers.normalize();

/*
 * Code to set the two colliding balls apart from each other
 */
			  	  	  Vector t=r1.subtract(dir.multiply_scalar(radius1+radius2-dis+0.001));
				  	  balls[index].x=t.x;
				  	  balls[index].y=t.y;
				  	  balls[index].z=t.z;


				  	  t=r2.subtract(dir.multiply_scalar(-1*(radius1+radius2-dis+0.001)));
				  	  balls[i].x=t.x;
				  	  balls[i].y=t.y;
				  	  balls[i].z=t.z;

				  	  double x1=dir.dot_product(balls[index].v);
				  	  Vector v1x=dir.multiply_scalar(x1);
				  	  Vector v1z=balls[index].v - v1x;
				  	  double m1=balls[index].mass;

				  	  dir=dir.multiply_scalar(-1);
				  	  double x2=dir.dot_product(balls[i].v);
				  	  Vector v2x=dir.multiply_scalar(x2);
				  	  Vector v2z=balls[i].v - v2x;
				  	  double m2=balls[i].mass;

				  	  //balls[index].v=v1z.add(v1x.multiply_scalar(-1));
				  	  //balls[index].v=balls[index].v.normalize();
				  	  //balls[i].v=v2z.add(v2x.multiply_scalar(-1));
				  	  //balls[i].v=balls[i].v.normalize();


				  	  //conserving the momentum when the balls have different masses
				  	  //balls[index].v=v1z.add((v1x.multiply_scalar((m1-m2)/(m1+m2))).add(v2x.multiply_scalar(2*m2/(m1+m2))));
				  	  //balls[i].v=v2z.add((v2x.multiply_scalar((m2-m1)/(m1+m2))).add(v1x.multiply_scalar(2*m1/(m1+m2))));

				  	  balls[i].v=v2z + ((v2x.multiply_scalar((m2-m1)/(m1+m2))) + (v1x.multiply_scalar(2*m1/(m1+m2))));
				  	  balls[index].v=v1z + ((v1x.multiply_scalar((m1-m2)/(m1+m2))) + (v2x.multiply_scalar(2*m2/(m1+m2))));
			  }
		  }

	  }
}


/*
void Ball::update() {
    y += direction * 0.05;
	if(maximumHeight<=radius)
	{
		direction=0;
		y=radius;
		motion=0;
	}
	else
	{
		if (y > maximumHeight) {
		  y = maximumHeight;
		  direction = -1;
		}
		else if (y < radius) {

				y = radius;
				direction = 1;
				  maximumHeight=maximumHeight*factor;
		}
	}

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);


    //for texture

    glBindTexture(GL_TEXTURE_2D,this->g_Texture);
    //finish texture
    //glutSolidTeapot(1);

    glTranslated(x, y, z);
    glutSolidSphere(radius, 30, 30);
    glPopMatrix();
  }
*/





/*
 * ALboolean LoadALData()
 *
 *	This function will load our sample data from the disk using the Alut
 *	utility and send the data into OpenAL as a buffer. A source is then
 *	also created to play that buffer.
 */
ALboolean Ball::LoadALData()
{
	// Variables to load into.

	ALenum format;
	ALsizei size;
	ALvoid* data;
	ALsizei freq;
	ALboolean loop;

	// Load wav data into a buffer.

	alGenBuffers(1, &Buffer);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alutLoadWAVFile((ALbyte*)"wavdata/mysound3.wav", &format, &data, &size, &freq, &loop);
	alBufferData(Buffer, format, data, size, freq);
	alutUnloadWAV(format, data, size, freq);

	// Bind the buffer with the source.

	alGenSources(1, &Source);

	if(alGetError() != AL_NO_ERROR)
		return AL_FALSE;

	alSourcei (Source, AL_BUFFER,   Buffer   );
	alSourcef (Source, AL_PITCH,    1.0      );
	alSourcef (Source, AL_GAIN,     1.0      );
	alSourcefv(Source, AL_POSITION, SourcePos);
	alSourcefv(Source, AL_VELOCITY, SourceVel);
	alSourcei (Source, AL_LOOPING,  loop     );

	// Do another error check and return.

	if(alGetError() == AL_NO_ERROR)
		return AL_TRUE;

	return AL_FALSE;
}


/*
 * void SetListenerValues()
 *
 *	We already defined certain values for the Listener, but we need
 *	to tell OpenAL to use that data. This function does just that.
 */
void Ball::SetListenerValues()
{
	alListenerfv(AL_POSITION,    ListenerPos);
	alListenerfv(AL_VELOCITY,    ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}



/*
 * void KillALData()
 *
 *	We have allocated memory for our buffers and sources which needs
 *	to be returned to the system. This function frees that memory.
 */
void Ball::KillALData()
{
	alDeleteBuffers(1, &Buffer);
	alDeleteSources(1, &Source);
	alutExit();
}

