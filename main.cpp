/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 9 octobre 2013, 10:22
 */

#include <cstdlib>
#include<SDL/SDL.h>
#include <stdlib.h>
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include <math.h> 

void Dessiner(float x,float y);
 
int main(int argc, char *argv[])
{
    SDL_Event event;
 
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(640, 480, 32, SDL_OPENGL);
 
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
    glEnable(GL_DEPTH_TEST);
  float x = 3;
  float y = 3;
  float ray = 3;
  float angle = 0;
    Dessiner(x,y);
 
    for (;;)
    {
        SDL_PollEvent(&event);
 
        switch(event.type)
        {
            case SDL_QUIT:
            exit(0);
            break;
        }
        angle+= 0.001;
            x = ray*cos(angle);
            y = ray*sin(angle);
        Dessiner(x,y);
 
    }
 
    return 0;
}
 
void Dessiner(float x , float y)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
 
    gluLookAt(x,y,2,0,0,0,0,0,1);
 
    glBegin(GL_QUADS);
 
    glColor3ub(255,0,0); //face rouge
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);
 
    glColor3ub(0,255,0); //face verte
    glVertex3d(1,-1,1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,1,-1);
    glVertex3d(1,1,1);
 
    glColor3ub(0,0,255); //face bleue
    glVertex3d(-1,-1,1);
    glVertex3d(-1,-1,-1);
    glVertex3d(1,-1,-1);
    glVertex3d(1,-1,1);
 
    glEnd();
 
    glFlush();
    SDL_GL_SwapBuffers();
}