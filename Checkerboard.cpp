/*
 * CheckerBoard.cpp
 *
 *  Created on: 19-Nov-2011
 *      Author: prateek
 */
#include <GLUT/glut.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
using namespace std;

#include "Checkerboard.h"

GLfloat color1[]={0.25,0.8,0.2};
GLfloat color2[]={0.9,0.3,0.1};

  Checkerboard::Checkerboard(int width1, int depth1)
  {
	  width=width1;
	  depth=depth1;
  }

  double Checkerboard::centerx() {return width / 2;}

  double Checkerboard::centerz() {return depth / 2;}

  void Checkerboard::create() {
    displayListId = glGenLists(2);
    glNewList(displayListId, GL_COMPILE);
    GLfloat lightPosition[] = {4, 3, 7, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glBegin(GL_QUADS);
    glNormal3d(0, 1, 0);
    for (int x = 0; x < width - 1; x++) {
      for (int z = 0; z < depth - 1; z++) {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
                     (x + z) % 2 == 0 ? color1 : color2);
        glVertex3d(x, 0, z);
        glVertex3d(x+1, 0, z);
        glVertex3d(x+1, 0, z+1);
        glVertex3d(x, 0, z+1);
      }
    }
    glEnd();


    glBegin(GL_QUADS);
    glNormal3d(0, 0,-1);

    for (int x = 0; x < width - 1; x++)
    {
    	for(int y=0;y<1;y++)
    	{
			for(int z=0;z<width;z+=(width-1))
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
							 (x+y) % 2 == 0 ? color1 : color2);
				glVertex3d(x, y, z);
				glVertex3d(x, y+1, z);
				glVertex3d(x+1, y+1, z);
				glVertex3d(x+1, y, z);
			}
    	}
    }

    for (int z = 0; z < depth - 1; z++)
    {
    	for(int y=0;y<1;y++)
    	{
			for(int x=0;x<=width;x+=(width-1))
			{
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
							 (y+z) % 2 == 0 ? color1 : color2);
				glVertex3d(x, y, z);
				glVertex3d(x, y+1, z);
				glVertex3d(x, y+1, z+1);
				glVertex3d(x, y, z+1);
			}
    	}
    }

    glEnd();
    glEndList();

//    int displayListId2 = glGenLists(2);
 //   glNewList(displayListId2, GL_COMPILE);
/*
    GLUquadricObj *qobj;
    qobj = gluNewQuadric();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,cannon_color);
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_FLAT);
    glTranslatef(2.0,3.0,5.0);
    gluCylinder(qobj, 0.0005, 0.5, 3.0, 45, 15);
    glEndList();
*/
  }
  void Checkerboard::draw() {
    glCallList(displayListId);
/*    glPushMatrix();
    glRotatef(300.0, 1.0, 0.0, 0.0);
    glCallList(displayListId+1);
    glPopMatrix();*/
  }

