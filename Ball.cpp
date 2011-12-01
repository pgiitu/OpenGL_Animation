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
#include "vector.h"
#include "Ball.h"
using namespace std;

#define factor 1.000
#define gravity_factor 0.008
#define gravity_up 0.8
#define gravity_down 1.4
#define time_inc 1.0/60.0
//#define grav 9.806

vector acc(0.0,-9.806,0.0);

// A ball.  A ball has a radius, a color, and bounces up and down between
// a maximum height and the xz plane.  Therefore its x and z coordinates
// are fixed.  It uses a lame bouncing algorithm, simply moving up or
// down by 0.05 units at each frame.

Ball::Ball(double r, GLfloat* c, double h, double x, double z,double t,double m):
      radius(r), color(c), maximumHeight(h), direction(1),
      y(h), x(x), z(z),minimumHeight(r),theta(t),motion(1) {
	  v.x=8*cos(t*M_PI/180);
//	  v.x=0.0;
	  v.y=0.0;
//	  v.z=0.0;
	  v.z=8*sin(t*M_PI/180);
	  inc_factor=0.08;
	  gravity=inc_factor;
	  mass=m;
	  time =0.0;
	  flag=0;

	  starting.x=x;
	  starting.y=h;
	  starting.z=z;
	  starting_v.x=v.x;
	  starting_v.y=v.y;
	  starting_v.z=v.z;
	  //finish texture

	  for(int k=0;k<3;k++)
	  {
		  SourcePos[k]=0.0;

		  SourceVel[k]=0.0;

		  ListenerPos[k]=0.0;

		  ListenerVel[k]=0.0;

	  }
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

void Ball::check_inside(double x1,double y1)
{
	vector r1(this->x-x1,this->y-y1,0);
	if(r1.magnitude()<this->radius)
	{
		this->maximumHeight=this->maximumHeight+2;
		this->inc_factor=0.3;
	}
}
void Ball::set_start_position()
{
	//cout<<"set start position\n";
//	vector v(this->x,this->y,this->z);
	flag=1;
//	this->time=0.0;

	//return v;
}

void Ball::rolling(int i,Ball balls[],int no_of_balls,double width,double height)  //where the integer i represents the index of the ball in the balls array
  {


//	  	cout<<"before time is "<<time<<endl;
//	  	cout<<"time is "<<time<<endl;


    intersection_with_walls(width,height);
  	intersection_with_balls(i,balls,no_of_balls);

  	this->time=this->time+time_inc;
  	double t=this->time;
    //v.y=v.y+acc.y*time_inc;
  	v=starting_v.add(acc.multiply_scalar(t));
//  	vector temp();
  	vector n1=starting.add((starting_v.multiply_scalar(t)).add(acc.multiply_scalar(0.5*t*t)));
    x=n1.x;
    y=n1.y;
    z=n1.z;

    intersection_with_walls(width,height);
  	intersection_with_balls(i,balls,no_of_balls);

    if(y<radius)
  	{
  		  v.y=-factor*v.y;
  		  maximumHeight=(v.y*v.y)/(2*9.806);
			//cout<<"setting zero and velocity in y direction is"<<v.y<<" \n";
			//cout<<"maximum height is"<<maximumHeight<<endl;
			y=radius;
		  //cout<<"start pos 2\n";
  		set_start_position();
  	}
    else
    {

    //if((v.y>0.0) &&(v.y+acc.y*t <=0.0))
    	if(y>maximumHeight)
  		{
  			//cout<<"setting zero\n";
  			  v.y=0.0;
  			set_start_position();
  		}
    }
  	/*
  	x=starting.x+v.x*t;
  	if(direction==-1)
  	{
  		y=starting.y+(v.y*t-0.5*t*t*grav);
  	}
  	else
  	{
  		y=starting.y-(v.y*t+0.5*t*t*grav);
  	}
  	z=starting.z+v.z*t;

*/
  	if(flag==1)
  	{
  		time=0.0;
  		flag=0;
  		starting.x=this->x;
  		starting.y=this->y;
  		starting.z=this->z;
  		starting_v=v;
  	}





	//double t=this->time;
/*
	  if(direction==1)
	  {
	  	if(y<radius)
	  	{
	  		direction=-1;
	  		v.y=factor*v.y;
			  cout<<"start pos 2\n";

	  		set_start_position();
	  	}
	  }

	  	if(direction==-1)
	  	{
	  		if((v.y!=0.0) &&(v.y-grav*t <=0.0))
	  		{
	  			  v.y=0.0;
				  cout<<"start pos 3\n";

	  			set_start_position();
	  			direction=1;
	  		}
	  	}
*/

//	  	cout<<"the x is "<<x<<"  the y is "<<y<<"  The Z is"<<z<<endl;

/*
//	  	x=x+inc_factor*v.x;

//	    y=y+direction*inc_factor;
		if(maximumHeight<=radius)
		{
			direction=1;
			v.z=0;
			y=radius;
			gravity=0;
//			motion=0;
		}
		else
		{
			if (y > maximumHeight)
			{
			  y = maximumHeight;
			  direction = -1;
			  set_start_position();
			  //gravity=0.008;
			}
			else if (y < radius) {

					y = radius;
					direction = 1;
					  maximumHeight=maximumHeight*factor;
					  gravity=inc_factor;
					  set_start_position();
			}

			if(direction==1)
			{
//				gravity=gravity*gravity_up;
				gravity=gravity- 0.0008;

			}
			else if(direction==-1)
			{

				gravity=gravity +0.03;
			}


		}
	end old	*/

	    //z=z+inc_factor*v.z;

	  	glPushMatrix();
	    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

	    glTranslated(x, y, z);
	    //glRotated(10,0,1.0,0);

	    glutSolidSphere(radius, 30, 30);
	    glPopMatrix();
  }

void Ball::initialize_texture()
{

		  //for texture
		  g_Texture=0;
		  g_Texture = LoadTexture("spheremap.bmp");
		  //printf("done \n");



}

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

	void Ball::intersection_with_walls(double width,double height)
	{
		vector ret=v;
		if(z<=radius)
		{
			v.z=-1*v.z;
			z=radius+0.001;

			set_start_position();
		}

		if((z+radius)>=(height-1))
		{
			v.z=-1*v.z;
			z=(height-1)-radius-0.001;

			  set_start_position();
		}

		if(x<=radius)
		{
			v.x=-1*v.x;
			x=radius+0.001;

			  set_start_position();

		}


		if((x+radius)>=(width-1))
		{
			x=(width-1)-radius-0.001;
			v.x=-1*v.x;
			//  cout<<"start pos 7\n";

			  set_start_position();
		}
	}

void Ball::intersection_with_balls(int index,Ball balls[],int no_of_balls)
{

	  double radius1=balls[index].radius;
	  vector r1(balls[index].x,balls[index].y,balls[index].z);
	  for (int i = 0; i < no_of_balls; i++)
	  {
		  double radius2=balls[i].radius;
		  vector r2(balls[i].x,balls[i].y,balls[i].z);
		  if(i!=index)
		  {
			  vector dir_centers=r1.subtract(r2);
			  double dis=dir_centers.magnitude();
			  if((radius1+radius2)>=dis)
			  {

				  alSourcePlay(Source);
				  //cout<<"start pos 1\n";
				  set_start_position();

			  	  vector dir=dir_centers.normalize();
/*
			  	  	  vector t=r1.subtract(dir.multiply_scalar(radius1+radius2-dis+0.001));
				  	  balls[index].x=t.x;
				  	  balls[index].y=t.y;
				  	  balls[index].z=t.z;


				  	  t=r2.subtract(dir.multiply_scalar(-1*(radius1+radius2-dis+0.001)));
				  	  balls[i].x=t.x;
				  	  balls[i].y=t.y;
				  	  balls[i].z=t.z;
*/
				  	  double x1=dir.dot_product(balls[index].v);
				  	  //if(x1>0)
				  	  vector v1x=dir.multiply_scalar(x1);
				  	  vector v1z=(balls[index].v).subtract(v1x);
				  	  double m1=balls[index].mass;

				  	  dir=dir.multiply_scalar(-1);
				  	  double x2=dir.dot_product(balls[i].v);
				  	  vector v2x=dir.multiply_scalar(x2);
				  	  vector v2z=(balls[i].v).subtract(v2x);
				  	  double m2=balls[i].mass;

				  	  //balls[index].v=v1z.add(v1x.multiply_scalar(-1));
				  	  //balls[index].v=balls[index].v.normalize();
				  	  //balls[i].v=v2z.add(v2x.multiply_scalar(-1));
				  	  //balls[i].v=balls[i].v.normalize();


						//conserving the momentum when the balls have different masses
				  	   balls[index].v=v1z.add((v1x.multiply_scalar((m1-m2)/(m1+m2))).add(v2x.multiply_scalar(2*m2/(m1+m2))));
				  	   balls[i].v=v2z.add((v2x.multiply_scalar((m2-m1)/(m1+m2))).add(v1x.multiply_scalar(2*m1/(m1+m2))));



			  }
		  }

	  }
}



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

	alutLoadWAVFile((ALbyte*)"wavdata/FancyPants.wav", &format, &data, &size, &freq, &loop);
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

