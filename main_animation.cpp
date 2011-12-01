// This application shows balls bouncing on a checkerboard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>
#include "intersection_point.h"
#include "ray.h"
#include "vector.h"
#include "Ball.h"
#include "Checkerboard.h"
#include "Camera.h"
#include <stdio.h>
#include <iostream>
using namespace std;

GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};


#define factor 0.1000
#define width 20
#define height 20


// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(width,height);
double v_w;
double v_h;
Camera camera;

Ball balls[] = {
  Ball(0.4, GREEN, 3.0, 6, 5,40,1.0),

  Ball(0.4, MAGENTA, 4, 3, 4,200,2.0),
  Ball(0.4, WHITE, 4.5, 7, 5,10,3.0),


  Ball(0.4, RED, 2, 5, 4,0,1.24),
  Ball(0.4, WHITE, 3.5, 12, 4,0,1.9),
  Ball(0.4, WHITE, 3.6, 11.9, 4,0,2.5),
//  Ball(0.25, RED, 3.5, 1.4, 4,0),

 //*/
};


// Application-specific initialization: Set up global lighting parameters
// and create display lists.
void init() {
  glEnable(GL_DEPTH_TEST);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
  glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
  glMaterialf(GL_FRONT, GL_SHININESS, 30);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);




  // for texture


	// enable texturing
	glEnable(GL_TEXTURE_2D);

	// tell openGL to generate the texture coords for a sphere map
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

	// enable automatic texture coordinate generation
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);












  checkerboard.create();
}



// Draws one frame, the checkerboard then the balls, from the current camera
// position.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
            checkerboard.centerx(), 0.0, checkerboard.centerz(),
            0.0, 1.0, 0.0);
  checkerboard.draw();
	  for (int i = 0; i < sizeof balls / sizeof(Ball); i++) {
/*
		  if(balls[i].motion)
		  {
			  balls[i].update();
		  }
		  else
		  {
*/
		  	//  printf("calling rolling\n");
			  balls[i].rolling(i,balls,(sizeof balls / sizeof(Ball)),width,height);
//		  }
	  }


  glFlush();
  glutSwapBuffers();
}

void Accelerate(double x,double y)
{
	  for (int i = 0; i < sizeof balls / sizeof(Ball); i++)
	  {
		  	  balls[i].check_inside(x,y);
	  }

}

// On reshape, constructs a camera that perfectly fits the window.
void reshape(GLint w, GLint h) {
	v_w=w;
	v_h=h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
  glMatrixMode(GL_MODELVIEW);
}

// Requests to draw the next frame.
void timer(int v) {
  glutPostRedisplay();
  glutTimerFunc(1000/100, timer, v);
}

void MouseClick(int button, int state, int x, int y){

  if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
        {
        	//eye_z = eye_z - 0.1;
        	//LookAt(eye_x,eye_y,eye_z,centre_x,centre_y,centre_z, up_x, up_y, up_z);
        	double h =2*tan(20*M_PI/180);
        	double w=(v_w/v_h)*h;
        	double x1=h*(x/v_w);
        	double y1=w*(y/v_h);

        	cout<<"you clicked at x="<<x1<<"  and y= "<<y1<<"\n";
        	//printf("you clicked at x= %   and y= %")
        	for (int i = 0; i < sizeof balls / sizeof(Ball); i++)
        	{
        		cout<<"Ball no "<<(i+1)<<endl;
        		cout<<"the center  x="<<balls[i].x<<"  and y= "<<balls[i].y<<"\n";

        		balls[i].check_inside(x,y);
        	}
        	cout<<"\n\n\n";

        	Accelerate(x,y);


        	glutPostRedisplay();
        }
        else if(button == GLUT_MIDDLE_BUTTON)
        {
            //middle button code
        }
        else if(button == GLUT_RIGHT_BUTTON)
        {
        	/*
        	eye_z = eye_z + 0.1;
        	LookAt(eye_x,eye_y,eye_z,centre_x,centre_y,centre_z, up_x, up_y, up_z);
        	glutPostRedisplay();
        	*/
        }
    }
    else
    {
        //alternate code
    }

}

void set_texture()
{
	  for (int i = 0; i < sizeof balls / sizeof(Ball); i++)
	  {
		  balls[i].initialize_texture();
	  }

}

// Moves the camera according to the key pressed, then ask to refresh the
// display.
void special(int key, int, int) {
  switch (key) {
    case GLUT_KEY_LEFT: camera.moveLeft(); break;
    case GLUT_KEY_RIGHT: camera.moveRight(); break;
    case GLUT_KEY_UP: camera.moveUp(); break;
    case GLUT_KEY_DOWN: camera.moveDown(); break;
  }
  glutPostRedisplay();
}

// Initializes GLUT and enters the main loop.
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Bouncing Balls");
  init();
  set_texture();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(MouseClick);
  glutSpecialFunc(special);
  glutTimerFunc(1000.0/60.0, timer, 0);
  glutMainLoop();
}
