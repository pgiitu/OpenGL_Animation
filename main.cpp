
/*
//------------------------------------------------------------
/// \file	Main.cpp
/// \author	Rob Bateman
/// \date	9-feb-2005
/// \brief	A simple example demonstrates how to apply 
///			environment mapping to an object. This approach uses
///			a sphere map which is probably the easiest method 
///			available. 
//------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "texture.h"

/// this will hold the openGL texture object for the loaded texture
unsigned int g_Texture=0;


/// maya camera attributes
float zoom = 15.0f;
float rotx = 0;
float roty = 0.001f;
float tx = 0;
float ty = 0;
int lastx=0;
int lasty=0;
unsigned char Buttons[3] = {0};

//------------------------------------------------------------	Draw()
//
void OnDraw() {

	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	// clear previous transformations
	glLoadIdentity();

	// set camera position
	glTranslatef(0,0,-zoom);
	glTranslatef(tx,ty,0);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);	

	// bind the environment map texture
	glBindTexture(GL_TEXTURE_2D,g_Texture);
	
	// draw the teapot
	glutSolidTeapot(1);

	glutSwapBuffers();
}

//------------------------------------------------------------	OnInit()
//
void OnInit() {

	// enable depthe testing
	glEnable(GL_DEPTH_TEST);

	// enable texturing
	glEnable(GL_TEXTURE_2D);

	// tell openGL to generate the texture coords for a sphere map
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);

	// enable automatic texture coordinate generation
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	// enable the default light
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// load texture as compressed
	g_Texture = LoadTexture("spheremap.bmp");

	// print some info about it
	std::cout << "Texture Size=" << (GetTextureSize(g_Texture)/1024.0f) << "Kb"<< std::endl;
}

//------------------------------------------------------------	Reshape()
void OnReshape(int w, int h)
{
	// prevent division by zero when minimised
	if (h==0) 
		h=1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//------------------------------------------------------------	OnExit()
//
void OnExit() {
	DeleteAllTextures();
}



//------------------------------------------------------------	OnMotion()
//
void OnMotion(int x,int y)
{
	int diffx=x-lastx;
	int diffy=y-lasty;
	lastx=x;
	lasty=y;

	if( Buttons[0] && Buttons[1] )
	{
		zoom -= (float) 0.05f * diffx;
	}
	else
		if( Buttons[0] )
		{
			rotx += (float) 0.5f * diffy;
			roty += (float) 0.5f * diffx;		
		}
		else
			if( Buttons[1] )
			{
				tx += (float) 0.05f * diffx;
				ty -= (float) 0.05f * diffy;
			}
			glutPostRedisplay();
}

//------------------------------------------------------------	OnMouse()
//
void OnMouse(int b,int s,int x,int y)
{
	lastx=x;
	lasty=y;
	switch(b)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = ((GLUT_DOWN==s)?1:0);
		break;
	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = ((GLUT_DOWN==s)?1:0);
		break;
	case GLUT_RIGHT_BUTTON:
		Buttons[2] = ((GLUT_DOWN==s)?1:0);
		break;
	default:
		break;		
	}
	glutPostRedisplay();
}


//------------------------------------------------------------	main()
//
int main(int argc,char** argv) {

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(640,480);
	glutCreateWindow("Sphere Mapping Example");

	glutDisplayFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutMouseFunc(OnMouse);
	glutMotionFunc(OnMotion);
	
	OnInit();

	atexit(OnExit);

	glutMainLoop();
	return 0;
}
*/
