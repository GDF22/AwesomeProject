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
    init();
    event.initMousePosition(pWindow);
    this->camera = new Camera(Coord3D(-5, 0, 2), Coord3D(0, 0, 0), Coord3D(0, 0, 1));
    this->twoDim = new Panel(string("2D"), Coord3D(0,0,0),1900,1900, NULL);  // HERE SCREEN DIMENSIONS
    ka.chooseConfig();
}

Controler::~Controler() {
}

// Initialisation de la SDL et de la fenetre
void Controler::init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_EVENTS);
    
    SDL_Renderer* displayRenderer;
    SDL_RendererInfo displayRendererInfo;
    SDL_CreateWindowAndRenderer(1600, 900, SDL_WINDOW_OPENGL, &pWindow, &displayRenderer);
    SDL_SetWindowFullscreen(pWindow, 0);
    SDL_SetWindowTitle(pWindow, "AwesomeProject");

    SDL_GetRendererInfo(displayRenderer, &displayRendererInfo);
    SDL_GLContext context;
    context = SDL_GL_CreateContext(pWindow);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}


void Controler::quit() {
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    exit(0);
}

void Controler::run() {
    World world;
    

    //*-----------------CREATION-DU-MENU-----------------------------
 
    Panel* menu = new Panel(string("menu"), Coord3D(400,100,0), 700, 500, new Color(0,0,255));
    twoDim->addComponent(menu);    
    Button* but = new Button(string("Button"),string("Resume"), Coord3D(400,100,0), 20, 20, new Color(255,0,0), PAUSE_MENU);
    Button* but2 = new Button(string("Button2"),string("Quit"), Coord3D(500,100,0), 20, 20, new Color(255,0,0), PAUSE_MENU);
    Panel* menu2 = new Panel(string("menu2"), Coord3D(500,200,0), 50, 50, new Color(0,0,100));
    menu->addComponent(but);
    menu->addComponent(but2);
    menu->addComponent(menu2);
    menu->setVisible(false);

    FrameManager frame = FrameManager(100);
   
    
    Object obj = Object("maison", new Coord3D(0, 0, 0));
    obj.addVertex(Coord3D(-1.0, -1.0, -1.0));
    obj.addVertex(Coord3D(-1.0, -1.0, 1.0));
    obj.addVertex(Coord3D(1.0, -1.0, 1.0));
    obj.addVertex(Coord3D(1.0, -1.0, -1.0));
    obj.addVertex(Coord3D(-1.0, 1.0, -1.0));
    obj.addVertex(Coord3D(-1.0, 1.0, 1.0));
    obj.addVertex(Coord3D(1.0, 1.0, 1.0));
    obj.addVertex(Coord3D(1.0, 1.0, -1.0));
    obj.addVertex(Coord3D(-1.0, 0, 2.0));
    obj.addVertex(Coord3D(1.0, 0, 2.0));
    
    vector<int> face;
    face.push_back(0);face.push_back(1);face.push_back(2);face.push_back(3);
    obj.addFace(new Face(face, new Color(255, 0, 0), new Color(242, 242, 242)));
    
    vector<int> face2;
    face2.push_back(4);face2.push_back(5);face2.push_back(6);face2.push_back(7);
    obj.addFace(new Face(face2, new Color(0, 0, 255), new Color(255, 255, 255)));
    
    vector<int> face3;
    face3.push_back(0);face3.push_back(1);face3.push_back(5);face3.push_back(4);
    obj.addFace(face3, new Color(0, 255, 0), new Color(255, 255, 255));
    
    vector<int> face4;
    face4.push_back(2);face4.push_back(3);face4.push_back(7);face4.push_back(6);
    obj.addFace(face4, new Color(255, 255, 0), new Color(255, 255, 255));
    
    vector<int> face5;
    face5.push_back(1);face5.push_back(2);face5.push_back(6);face5.push_back(5);
    obj.addFace(new Face(face5, new Color(255, 0, 255), new Color(255, 255, 255)));
    
    vector<int> face6;
    face6.push_back(0);face6.push_back(3);face6.push_back(7);face6.push_back(4);
    obj.addFace(new Face(face6, new Color(0, 255, 255), new Color(255, 255, 255)));
    
    vector<int> face7;
    face7.push_back(1);face7.push_back(2);face7.push_back(9);face7.push_back(8);
    obj.addFace(new Face(face7, new Color(128, 75, 0), new Color(255, 255, 255)));
    
    vector<int> face8;
    face8.push_back(5);face8.push_back(6);face8.push_back(9);face8.push_back(8);
    obj.addFace(new Face(face8, new Color(128, 75, 0), new Color(255, 255, 255)));

    // Debut de la boucle principale
    while(event.EventManager()) {
        ka.useKey(event, this);

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
    
        camera->placeCamera();
        
        Dessiner();
        //obj.drawFace();
        //obj.drawEdge();
        //world.draw();
        
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

                   twoDim->draw();

                glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glEnable(GL_DEPTH_TEST);
        // Fin de la 2D
        
        // Affichage
        glFlush();
        SDL_GL_SwapWindow(pWindow);
                
        frame.manageFrame();
    }
}

void Controler::action(Action action){
    // Si on appuie sur le bouton pause
    if(action == PAUSE_MENU){   // On rend visible/invisible le menu
        twoDim->getElementByName("menu")->toggleVisible();
        event.initMousePosition(pWindow);
    } else {    // Sinon
        if(!twoDim->getElementByName("menu")->isVisible()) {  // Si le menu n'est pas visible
            // On effectue les actions de déplacement de la caméra
            if(action == FORWARD){
                camera->forward();
            }
            else if(action == BACKWARD){
                camera->backward();
            }
            else if(action == LATERAL_LEFT){
                camera->lateralLeft();
            }
            else if(action == LATERAL_RIGHT){
                camera->lateralRight();
            }
            else if(action == UP){
                camera->up();
            }
            else if(action == DOWN){
                camera->down();
            }
            else if(action == UPDATEVIEW) {
                camera->updateView(event.notifyMouse());
            }
            else if(action == EXIT) {
                quit();
            }
            SDL_WarpMouseInWindow(pWindow, 800, 450);
        } else {  // Si le menu est visible
            // actions du menu...
        }
    }
}

void Controler::actionOnClick(pair<int,int> coord){
   Component* cpnt = twoDim->getElementByCoord(coord);
   if (cpnt != NULL){
       if(typeid(*cpnt) == typeid(Button)) action( ((Button*) cpnt)->getAction() );
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
    
    glColor3ub(255,0,0);
    glVertex2i(0,0);glVertex2i(1,0);
    glVertex3i(1,0,0);glVertex3f(0.9,0.1,0);
    glVertex3i(1,0,0);glVertex3f(0.9,-0.1,0);
    
    glColor3ub(0,255,0);
    glVertex2i(0,0);glVertex2i(0,1);
    glVertex3i(0,1,0);glVertex3f(0.1,0.9,0);
    glVertex3i(0,1,0);glVertex3f(-0.1,0.9,0);
    
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
          //  coordTab[i][j] = Coord3D(i,j,z);   classic 
           coordTab[i][j] = Coord3D(i,j,z+40*min(sin(M_PI *(j-25)/25),sin(M_PI *(i-25)/25)) );   
          //    coordTab[i][j] = Coord3D(i,j,i);  sin 
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
