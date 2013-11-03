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
    this->event = Event();
    this->ka = KeyAssignment();
    this->camera = Camera(Coord3D(-5, 0, 2), Coord3D(0, 0, 0), Coord3D(0, 0, 1));
}

Controler::~Controler() {
}

void Controler::run() {
    
    

    Panel p =  Panel(Coord3D(100,100,0),100,100,Color(1.0f, 0.5f , 0.0f));
    Panel partOne =  Panel(Coord3D(110,110,0),50,50,Color(0.9f, 0.0f , 0.0f));
   
    
    partOne.setName("sous-menu1");
    
    
    Panel partTwo =  Panel(Coord3D(310,310,0),50,50,Color(0.0f, 0.0f , 1.0f));
    
    
    partTwo.setName("sous-menu2");
    
    
    p.addComponent(&partOne);
    p.addComponent(&partTwo);
    
    
    
    FrameManager frame = FrameManager(60);
        
    Object obj = Object();
    obj.addVertex(Coord3D(1.0, 1.0, 1.0));
    obj.addVertex(Coord3D(1.0, 1.0, 4.0));
    obj.addVertex(Coord3D(4.0, 1.0, 4.0));
    obj.addVertex(Coord3D(4.0, 1.0, 1.0));
    obj.addVertex(Coord3D(1.0, 4.0, 1.0));
    obj.addVertex(Coord3D(1.0, 4.0, 4.0));
    obj.addVertex(Coord3D(4.0, 4.0, 4.0));
    obj.addVertex(Coord3D(4.0, 4.0, 1.0));
    
    vector<int> face;
    face.push_back(0);face.push_back(1);face.push_back(2);face.push_back(3);
    obj.addFace(Face(face, Coord3D(255, 255, 0), Coord3D(255, 255, 255)));
    vector<int> face2;
    face2.push_back(4);face2.push_back(5);face2.push_back(6);face2.push_back(7);
    obj.addFace(Face(face2, Coord3D(0, 0, 255), Coord3D(255, 255, 255)));
    vector<int> face3;
    face3.push_back(0);face3.push_back(1);face3.push_back(5);face3.push_back(4);
    obj.addFace(Face(face3, Coord3D(0, 255, 0), Coord3D(255, 255, 255)));
    vector<int> face4;
    face4.push_back(2);face4.push_back(3);face4.push_back(7);face4.push_back(6);
    obj.addFace(Face(face4, Coord3D(255, 0, 0), Coord3D(255, 255, 255)));
    vector<int> face5;
    face5.push_back(1);face5.push_back(2);face5.push_back(6);face5.push_back(5);
    obj.addFace(Face(face5, Coord3D(255, 0, 255), Coord3D(255, 255, 255)));
    vector<int> face6;
    face6.push_back(0);face6.push_back(3);face6.push_back(7);face6.push_back(4);
    obj.addFace(Face(face6, Coord3D(0, 255, 255), Coord3D(255, 255, 255)));
    
    obj.removeVertex(0);
    
    
    
    while (event.EventManager())
    {
        ka.useKey(event.notifyKeyboard(), &camera);
        camera.updateView(event.notifyMouse());
                
        // Début de la 3D
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70,(double)640/480,1,1000);
        glEnable(GL_DEPTH_TEST);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_BLEND) ;
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ; 
    
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity( );
    
        camera.placeCamera();
        
        Dessiner();
        obj.drawFace();
        obj.drawEdge();
        // Fin de la 3D
        
        // Début de la 2D
        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            glLoadIdentity();
            gluOrtho2D(0.0, 1600, 900, 0);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
                glLoadIdentity();

                   p.draw();

                glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glEnable(GL_DEPTH_TEST);
        // Fin de la 2D
        
        // Affichage
        glFlush();
        SDL_GL_SwapBuffers();
                
        frame.manageFrame();
    }
}





void Dessiner()
{
    carre(2, 5, -3, 1);
    carre(5, 2, 5, 1);
    carre(2, 5, 3, 1);
    //triangle(-5, -3, 5, 4, 3);
    
    grille();
    grilleModulaire();
    axe();
}

void axe() {
    glBegin(GL_LINES);
    
    glColor3i(255,0,0);
    glVertex2i(0,0);glVertex2i(0,1);
    glVertex3i(0,1,0);glVertex3f(0.1,0.9,0);
    glVertex3i(0,1,0);glVertex3f(-0.1,0.9,0);
    
    glColor3i(0,255,0);
    glVertex2i(0,0);glVertex2i(1,0);
    glVertex3i(1,0,0);glVertex3f(0.9,0.1,0);
    glVertex3i(1,0,0);glVertex3f(0.9,-0.1,0);
    
    glColor3i(0,0,255);
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
