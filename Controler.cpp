/* 
 * File:   Controler.cpp
 * Author: Administrator
 * 
 * Created on 28 octobre 2013, 18:13
 */

#include "Controler.h"

void Dessiner();
void axe();
void grille();
void carre(float x, float y, float z, float taille);
void triangle(float x, float y, float z, float hauteur, float rayonBase);
void pyramide(float x, float y, float z, float hauteur, float rayonBase, int nbSommetBase);
void grilleModulaire();

Controler::Controler() {
    this->keyboard = KeyboardEvent();
    this->mouse = MouseEvent();
    this->camera = Camera(Coord3D(-5, 0, 2), Coord3D(0, 0, 0), Coord3D(0, 0, 1));
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(70,(double)640/480,1,1000);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

Controler::~Controler() {
}

void Controler::run() {
    SDL_Event event;
    FrameManager frame = FrameManager(60);
    
    for (;;)
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glLoadIdentity( );
    
        SDL_PollEvent(&event);
        SDL_WarpMouse(800, 450);
        keyboard.EventManager(event);
        mouse.EventManager(event);
        
        camera.deplacement(keyboard, mouse);
        camera.placeCamera();
        
        Dessiner();
        
        frame.manageFrame();
    }
}

void Dessiner()
{
    carre(2, 5, -3, 1);
    carre(5, 2, 5, 1);
    carre(2, 5, 3, 1);
    triangle(-5, -3, 5, 4, 3);
    //pyramide(20, 20, 2, 5, 5, 6);
    
    grille();
    grilleModulaire();
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



void grilleModulaire() {
    int I,J;
    I = 200; J = 200;
    Coord3D coordTab[I][J];
   int z = 5; 
   for(int i = 0; i < I; i++) {
        for(int j = 0; j < J; j++) {
          //  coordTab[i][j] = Coord3D(i,j,z);  /* classic */
            coordTab[i][j] = Coord3D(i,j,z+40*min(sin(M_PI *(j-25)/25),sin(M_PI *(i-25)/25)) );  /* sin */
          //    coordTab[i][j] = Coord3D(i,j,i);  /* sin */
        }
    }
    glBegin(GL_LINES);
    glColor3ub(150,150,150);
    
    for(int i = 0; i < I-1; i++) {
        for(int j = 0; j < J-1; j++) {
            
            glVertex3i(coordTab[i][j].getX(),coordTab[i][j].getY(),coordTab[i][j].getZ());
            glVertex3i(coordTab[i][j+1].getX(),coordTab[i][j+1].getY(),coordTab[i][j+1].getZ());
            
            glVertex3i(coordTab[i][j].getX(),coordTab[i][j].getY(),coordTab[i][j].getZ());
            glVertex3i(coordTab[i+1][j].getX(),coordTab[i+1][j].getY(),coordTab[i+1][j].getZ());
            
        }
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
    sommets[0] =  Coord3D(x, y, z+hauteur);
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