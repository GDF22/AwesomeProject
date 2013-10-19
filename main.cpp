/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 9 octobre 2013, 10:22
 */

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Coord3D.h"
#include "Fenetre.h"
#include "Camera.h"
#include "EvenementCLavier.h"


using namespace std;

void Dessiner();
void axe();
void grille();
 
int main(int argc, char *argv[])
{
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    
    Fenetre fenetre(900, 700);
    SDL_Event event;
 
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
    glEnable(GL_DEPTH_TEST);
    
    EvenementClavier clavier = EvenementClavier();
    Camera camera = Camera(Coord3D(0, 5, 1), Coord3D(0, 4, 1), Coord3D(0, 0, 1));
    
    Dessiner();
 
    for (;;)
    {
        SDL_PollEvent(&event);
        clavier.gereEvent(event);
        
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
 
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity( );
    
        camera.deplacement(clavier);
        camera.placeCamera();
        
        Dessiner();
 
    }
 
    return 0;
}
 
void Dessiner()
{
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
    
    grille();
    axe();
 
    glFlush();
    SDL_GL_SwapBuffers();
}

void axe() {
    glBegin(GL_LINES);
    
    glColor3ub(255,0,0);
    glVertex2i(0,0);glVertex2i(0,1);
    glVertex3i(0,1,0);glVertex3f(0.1,0.9,0);
    glVertex3i(0,1,0);glVertex3f(-0.1,0.9,0);
    
    glColor3ub(0,255,0);
    glVertex2i(0,0);glVertex2i(1,0);
    glVertex3i(1,0,0);glVertex3f(0.9,0.1,0);
    glVertex3i(1,0,0);glVertex3f(0.9,-0.1,0);
    
    glColor3ub(0,0,255);
    glVertex2i(0,0);glVertex3i(0,0,1);
    glVertex3i(0,0,1);glVertex3f(0.05,-0.05,0.9);
    glVertex3i(0,0,1);glVertex3f(-0.05,0.05,0.9);
    
    glEnd();
}

void grille() {
    glBegin(GL_LINES);
    
    glColor3ub(150,150,150);
    for(int i = -50; i <= 50; i++) {
        glVertex2i(i,-50);glVertex2i(i,50);
        glVertex2i(-50,i);glVertex2i(50,i);
    }
    
    glEnd();
}