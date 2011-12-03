// This application shows balls bouncing on a checkerboard, with no respect
// for the laws of Newtonian Mechanics.  There's a little spotlight to make
// the animation interesting, and arrow keys move the camera for even more
// fun.

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cmath>
#include "intersection_point.h"
#include "ray.h"
#include "Ball.h"
#include "Checkerboard.h"
#include "Camera.h"
#include "Vector.h"
using namespace std;

GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};

GLfloat cannon_dir[]={5.0,-5.0,3.0};
//Vector ball_dir(1.0,1.0,-1.0);
Vector ball_dir(cannon_dir[0],cannon_dir[1],cannon_dir[2]);
float  initial[16] = { 1.0, 0.0, 0.0, 0.0,0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0,  0.0, 0.0, 0.0, 1.0 };



string s_colors[]={"White","Silver","Gray","Black","Red","Maroon","Yellow","Olive","Lime","Green","Aqua","Teal","Blue","Navy","Fuchsia","Purple"};

GLfloat color_rgb[][3]={{1, 1, 1},{0.75, 0.75, 0.75},{0.5, 0.5, 0.5},{0.0, 0.0, 0.0},{1, 0.0, 0.0}
,{0.5, 0.0, 0.0},{1, 1, 0.0},{0.5, 0.5, 0.0},{0.0, 1, 0.0},{0.0, 0.5,0.0},{0.0, 1, 1},{0.0, 0.5, 0.5}
,{0.0, 0.0, 1},{0.0, 0.0, 0.5},{1, 0.0, 1},{0.5, 0.0, 0.5}};



int no_of_colors=16;


/*
 * initialising GLUI objects
 */

GLUI_Panel *obj_panel;

GLUI_Spinner *spinner_mass;

GLUI_Spinner *spinner_radius;
GLUI_Spinner *spinner_speed;


float orientation[16];

GLUI_Rotation *direction;
GLUI_Listbox *color_list;
GLUI_Button *button;


/*
White	#FFFFFF	100%	100%	100%	0°	0%	100%	0%	100%	15 (white)
Silver	#C0C0C0	75%	75%	75%	0°	0%	75%	0%	75%	7 (light gray)
Gray	#808080	50%	50%	50%	0°	0%	50%	0%	50%	8 (dark gray)
Black	#000000	0%	0%	0%	0°	0%	0%	0%	0%	0 (black)
Red	#FF0000	100%	0%	0%	0°	100%	50%	100%	100%	12 (high red)
Maroon	#800000	50%	0%	0%	0°	100%	25%	100%	50%	4 (low red)
Yellow	#FFFF00	100%	100%	0%	60°	100%	50%	100%	100%	14 (yellow)
Olive	#808000	50%	50%	0%	60°	100%	25%	100%	50%	6 (brown)
Lime	#00FF00	0%	100%	0%	120°	100%	50%	100%	100%	10 (high green); green
Green	#008000	0%	50%	0%	120°	100%	25%	100%	50%	2 (low green)
Aqua	#00FFFF	0%	100%	100%	180°	100%	50%	100%	100%	11 (high cyan); cyan
Teal	#008080	0%	50%	50%	180°	100%	25%	100%	50%	3 (low cyan)
Blue	#0000FF	0%	0%	100%	240°	100%	50%	100%	100%	9 (high blue)
Navy	#000080	0%	0%	50%	240°	100%	25%	100%	50%	1 (low blue)
Fuchsia	#FF00FF	100%	0%	100%	300°	100%	50%	100%	100%	13 (high magenta); magenta
Purple	#800080	50%	0%	50%	300°	100%	25%	100%	50%	5 (low magenta)
*/

#define factor 0.1000
#define width 30
#define height 30


// Global variables: a camera, a checkerboard and some balls.
Checkerboard checkerboard(width,height);
double v_w;
double v_h;
Camera camera;

int no_of_balls=0;

Ball balls[30];


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

/*
  // for texture

	// enable texturing
	glEnable(GL_TEXTURE_2D);

	// tell openGL to generate the texture coords for a sphere map
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

	// enable automatic texture coordinate generation
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
*/

  checkerboard.create();
}
GLfloat cannon_color[]={0.3,0.7,0.9};


void find_cannon_dir(int id)
{
//	float *fl;
//	direction->get_float_array_val(fl);


	double x_dir=cannon_dir[0]*initial[0]+cannon_dir[1]*initial[1]+cannon_dir[2]*initial[2];
	double y_dir=cannon_dir[0]*initial[4]+cannon_dir[1]*initial[5]+cannon_dir[2]*initial[6];
	double z_dir=cannon_dir[0]*initial[8]+cannon_dir[1]*initial[9]+cannon_dir[2]*initial[10];
/*
	double x_dir=cannon_dir[0]*fl[0]+cannon_dir[1]*fl[1]+cannon_dir[2]*fl[2];
	double y_dir=cannon_dir[0]*fl[4]+cannon_dir[1]*fl[5]+cannon_dir[2]*fl[6];
	double z_dir=cannon_dir[0]*fl[8]+cannon_dir[1]*fl[9]+cannon_dir[2]*fl[10];
*/
	Vector v(x_dir,y_dir,z_dir);
	v=v.normalize();
	ball_dir=v;

	//cout<<"Cannon direction is X:- "<<ball_dir.x<<" "<<ball_dir.y<<" "<<ball_dir.z<<" "<<endl;
}

void draw_cannon()
{
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,cannon_color);
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_FLAT);
    gluCylinder(qobj, 0.0005, 0.5, 3.0, 45, 15);

}

float  translate[16] = { 1.0, 0.0, 0.0, 1.0,0.0, 1.0, 0.0, 0.0,  0.0, 0.0, 1.0, 0.0,  0.0, 0.0, 0.0, 1.0 };

// Draws one frame, the checkerboard then the balls, from the current camera position.
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
            checkerboard.centerx(), 0.0, checkerboard.centerz(),
            0.0, 1.0, 0.0);
  checkerboard.draw();

  glPushMatrix();
//  glMultMatrixf(translate);
  glMultMatrixf(initial);
  draw_cannon();
  glPopMatrix();
//  find_cannon_dir();

  for (int i = 0; i < no_of_balls; i++)
  {
	  balls[i].rolling(i,balls,no_of_balls,width,height);
  }

  glFlush();
  glutSwapBuffers();
}

/*
void Accelerate(double x,double y)
{
	  for (int i = 0; i < no_of_balls; i++)
	  {
		  	  balls[i].check_inside(x,y);
	  }
}
*/

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



/*
 * function to insert a new ball as specified by the user
 */
void launch_ball(int ID)
{
	if(ID==1)
	{
			float *dir;
			direction->get_float_array_val( dir );

		  //no_of_balls;
			float radius=spinner_radius->get_float_val();
			float mass=spinner_mass->get_float_val();
			int id=color_list->get_int_val();
			//cout<<"id = "<<id<<endl;
			id=id-1;
//			  find_cannon_dir();
			cout<<ball_dir.x<<" "<<ball_dir.y<<" "<<ball_dir.z<<endl;
		  balls[no_of_balls++]=Ball(radius, color_rgb[id], 3.0, 6, 5,ball_dir,mass,spinner_speed->get_int_val());
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
  int window_id = glutCreateWindow( "Colliding Balls" );
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
//  glutMouseFunc(MouseClick);
  glutSpecialFunc(special);


  GLUI_Master.set_glutIdleFunc (NULL);
  /** Now create a GLUI user interface window and add controls **/
  GLUI *glui = GLUI_Master.create_glui( "GLUI", 0 );
  glui->set_main_gfx_window( window_id );

  glui->add_statictext( "Simple GLUI Example" );
  glui->add_separator();
  obj_panel = glui->add_panel("Parameters for the balls" );

  spinner_mass=glui->add_spinner_to_panel(obj_panel,"Mass",GLUI_SPINNER_FLOAT);
  spinner_mass->set_float_limits( 0.3, 3.0,GLUI_LIMIT_CLAMP );
  spinner_mass->set_speed(0.1);

  spinner_radius=glui->add_spinner_to_panel(obj_panel,"Radius",GLUI_SPINNER_FLOAT);
  spinner_radius->set_float_limits( 0.4, 0.7,GLUI_LIMIT_CLAMP );
  spinner_radius->set_speed(0.1);


  spinner_speed=glui->add_spinner_to_panel(obj_panel,"Speed",GLUI_SPINNER_INT);
  spinner_speed->set_float_limits( 1, 20,GLUI_LIMIT_CLAMP );
  spinner_speed->set_speed(1);


  direction=glui->add_rotation_to_panel(obj_panel,"direction",initial,2,find_cannon_dir);
  //direction->

  color_list = glui->add_listbox_to_panel(obj_panel,"Color of the Ball");

/*
  char *p;

  for(int i=0;i<no_of_colors;i++)
  {
	  string l=s_colors[i];
	  p=&l[0];
	  color_list->add_item(i+1,p);
  }
*/

color_list->add_item(1,"White");
color_list->add_item(2,"Silver");
color_list->add_item(3,"Gray");
color_list->add_item(4,"Black");
color_list->add_item(5,"Red");
color_list->add_item(6,"Maroon");
color_list->add_item(7,"Yellow");
color_list->add_item(8,"Olive");
color_list->add_item(9,"Lime");
color_list->add_item(10,"Green");
color_list->add_item(11,"Aqua");
color_list->add_item(12,"Teal");
color_list->add_item(13,"Blue");
color_list->add_item(14,"Navy");
color_list->add_item(15,"Fuchsia");
color_list->add_item(16,"Purple");
color_list->set_int_val(3);

//  string s_colors[]={"White","Silver","Gray","Black","Red","Maroon","Yellow","Olive","Lime","Green","Aqua","Teal","Blue","Navy","Fuchsia","Purple"};

  button = glui->add_button_to_panel(obj_panel,"Launch the ball",1,launch_ball);

  glutTimerFunc(1000.0/60.0, timer, 0);
  glutMainLoop();
}
