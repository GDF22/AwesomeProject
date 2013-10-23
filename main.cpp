/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 9 octobre 2013, 10:22
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <glm/glm.hpp>

#include "Coord3D.h"
#include "Fenetre.h"
#include "Camera.h"
#include "EvenementCLavier.h"


using namespace std;
//using namespace glm;

void Dessiner();
void axe();
void grille();
void carre(float x, float y, float z, float taille);
void triangle(float x, float y, float z, float hauteur, float rayonBase);
void pyramide(float x, float y, float z, float hauteur, float rayonBase, int nbSommetBase);
 
int main(int argc, char *argv[])
{
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    
    
    /*vec4 myVector = vec4(10.0, 10.0, 10.0, 1.0);
    mat4 myMatrix = mat4(vec4(1.0, 0.0, 0.0, 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(0.0, 0.0, 1.0, 0.0), vec4(10.0, 0.0, 0.0, 1.0));
    
    vec4 transformedVector = myMatrix * myVector; // Again, in this order ! this is important.
    
    printf("%f\n", transformedVector[0]);*/
    
    Fenetre fenetre(1600, 900);
    SDL_Event event;
 
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    
    EvenementClavier clavier = EvenementClavier();
    Camera camera = Camera(Coord3D(-5, 0, 2), Coord3D(0, 0, 0), Coord3D(0, 0, 1));
    
    Dessiner();
 
    for (;;)
    {        
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity( );
    
        SDL_PollEvent(&event);
        SDL_WarpMouse(800, 450);
        clavier.gereEvent(event);
        
        camera.deplacement(clavier);
        camera.placeCamera();
        
        Dessiner();
    }
 
    return 0;
}
 
void Dessiner()
{
    carre(2, 5, -3, 1);
    carre(5, 2, 5, 1);
    carre(2, 5, 3, 1);
    triangle(-5, -3, 5, 4, 3);
    //pyramide(20, 20, 2, 5, 5, 6);
    
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


void carre(float x, float y, float z, float taille) {
    glBegin(GL_QUADS);
        glColor3ub(0,0,255);
        glVertex3f(x+(taille/2),y+(taille/2),z+(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z+(taille/2));

        glVertex3f(x+(taille/2),y-(taille/2),z+(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z+(taille/2));

        glVertex3f(x-(taille/2),y-(taille/2),z+(taille/2));
        glVertex3f(x-(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z+(taille/2));

        glVertex3f(x-(taille/2),y-(taille/2),z+(taille/2));
        glVertex3f(x-(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z+(taille/2));

        glVertex3f(x-(taille/2),y-(taille/2),z+(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z+(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z+(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z+(taille/2));

        glVertex3f(x-(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z-(taille/2));
    glEnd();
    
    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        glVertex3f(x-(taille/2),y-(taille/2),z+(taille/2));glVertex3f(x+(taille/2),y-(taille/2),z+(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z+(taille/2));glVertex3f(x+(taille/2),y+(taille/2),z+(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z+(taille/2));glVertex3f(x-(taille/2),y+(taille/2),z+(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z+(taille/2));glVertex3f(x-(taille/2),y-(taille/2),z+(taille/2));

        glVertex3f(x-(taille/2),y-(taille/2),z-(taille/2));glVertex3f(x+(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z-(taille/2));glVertex3f(x+(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z-(taille/2));glVertex3f(x-(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z-(taille/2));glVertex3f(x-(taille/2),y-(taille/2),z-(taille/2));
        
        glVertex3f(x-(taille/2),y-(taille/2),z+(taille/2));glVertex3f(x-(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y-(taille/2),z+(taille/2));glVertex3f(x+(taille/2),y-(taille/2),z-(taille/2));
        glVertex3f(x+(taille/2),y+(taille/2),z+(taille/2));glVertex3f(x+(taille/2),y+(taille/2),z-(taille/2));
        glVertex3f(x-(taille/2),y+(taille/2),z+(taille/2));glVertex3f(x-(taille/2),y+(taille/2),z-(taille/2));
    glEnd();
}



void triangle(float x, float y, float z, float hauteur, float rayonBase) {
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,255);
        Coord3D s1 = Coord3D(x, y, z+hauteur);
        Coord3D s2 = Coord3D(x + cos(0)*rayonBase, y + sin(0)*rayonBase, z);
        Coord3D s3 = Coord3D(x + cos(90)*rayonBase, y + sin(90)*rayonBase, z);
        Coord3D s4 = Coord3D(x + cos(180)*rayonBase, y + sin(180)*rayonBase, z);

        glVertex3f(s1.getX(), s1.getY(), s1.getZ());
        glVertex3f(s2.getX(), s2.getY(), s2.getZ());
        glVertex3f(s3.getX(), s3.getY(), s3.getZ());

        glVertex3f(s1.getX(), s1.getY(), s1.getZ());
        glVertex3f(s2.getX(), s2.getY(), s2.getZ());
        glVertex3f(s4.getX(), s4.getY(), s4.getZ());
        
        glVertex3f(s1.getX(), s1.getY(), s1.getZ());
        glVertex3f(s4.getX(), s4.getY(), s4.getZ());
        glVertex3f(s3.getX(), s3.getY(), s3.getZ());
        
        glVertex3f(s4.getX(), s4.getY(), s4.getZ());
        glVertex3f(s2.getX(), s2.getY(), s2.getZ());
        glVertex3f(s3.getX(), s3.getY(), s3.getZ());

    glEnd();
    
    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        
        glVertex3f(s1.getX(), s1.getY(), s1.getZ());glVertex3f(s2.getX(), s2.getY(), s2.getZ());
        glVertex3f(s1.getX(), s1.getY(), s1.getZ());glVertex3f(s3.getX(), s3.getY(), s3.getZ());
        glVertex3f(s1.getX(), s1.getY(), s1.getZ());glVertex3f(s4.getX(), s4.getY(), s4.getZ());

        glVertex3f(s2.getX(), s2.getY(), s2.getZ());glVertex3f(s3.getX(), s3.getY(), s3.getZ());
        glVertex3f(s3.getX(), s3.getY(), s3.getZ());glVertex3f(s4.getX(), s4.getY(), s4.getZ());
        glVertex3f(s4.getX(), s4.getY(), s4.getZ());glVertex3f(s2.getX(), s2.getY(), s2.getZ());
        
    glEnd();
}


void pyramide(float x, float y, float z, float hauteur, float rayonBase, int nbSommetBase) {
    Coord3D sommets[nbSommetBase+1];
    sommets[0] = Coord3D(x, y, z+hauteur);
    int i;
    for(i = 0; i < nbSommetBase; i++) {
        float angle = i*(180/(nbSommetBase-1));
        sommets[i+1] = Coord3D(x + cos(angle)*rayonBase, y + sin(angle)*rayonBase, z);
        printf("%f, %f\n", cos(angle), sin(angle));
    }
    printf("\n\n");
    
    glBegin(GL_TRIANGLES);
        glColor3ub(0,0,255);

        for(i = 0; i <= nbSommetBase; i++) {
            glVertex3f(sommets[0].getX(), sommets[0].getY(), sommets[0].getZ());
            glVertex3f(sommets[i].getX(), sommets[i].getY(), sommets[i].getZ());
            glVertex3f(sommets[i+1].getX(), sommets[i+1].getY(), sommets[i+1].getZ());
        }
        glVertex3f(sommets[0].getX(), sommets[0].getY(), sommets[0].getZ());
        glVertex3f(sommets[1].getX(), sommets[1].getY(), sommets[1].getZ());
        glVertex3f(sommets[nbSommetBase].getX(), sommets[nbSommetBase].getY(), sommets[nbSommetBase].getZ());  
    glEnd();
        
    glBegin(GL_POLYGON);
         for(i = 1; i <= nbSommetBase; i++) {
             glVertex3f(sommets[i].getX(), sommets[i].getY(), sommets[i].getZ());
         }
    glEnd();
    
    glBegin(GL_LINES);
        glColor3ub(255,255,255);
        
        for(i = 0; i <= nbSommetBase; i++) {
            glVertex3f(sommets[0].getX(), sommets[0].getY(), sommets[0].getZ());
            glVertex3f(sommets[i].getX(), sommets[i].getY(), sommets[i].getZ());
        }
        
        for(i = 1; i <= nbSommetBase; i++) {
            glVertex3f(sommets[i].getX(), sommets[i].getY(), sommets[i].getZ());
            glVertex3f(sommets[i+1].getX(), sommets[i+1].getY(), sommets[i+1].getZ());
        }
        glVertex3f(sommets[1].getX(), sommets[1].getY(), sommets[1].getZ());
        glVertex3f(sommets[nbSommetBase].getX(), sommets[nbSommetBase].getY(), sommets[nbSommetBase].getZ());
    glEnd();
}