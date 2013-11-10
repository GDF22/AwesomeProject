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
    /*if(TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }*/
    
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

    // Debut de la boucle principale
    while(event.EventManager()) {
        ka.useKey(event, this);

        // Affichage 3D
        glEnable3D();
            camera->placeCamera();
            Dessiner();
            world.draw();
         glDisable3D();
        
        // Affichage 2D
        glEnable2D();
           twoDim->draw();
        glDisable2D();
           
        // Mise à jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(pWindow);
        
        // Gestion des frames
        frame.manageFrame();
    }
}

// Active l'affichage 3D (à modifier)
void Controler::glEnable3D() {
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
}

// Désactive l'affichage 3D (à modifier)
void Controler::glDisable3D() {
    glDisable(GL_DEPTH_TEST);
}
 
// Active l'affichage 2D
void Controler::glEnable2D() {
    /*GLint iViewport[4];

    // Get a copy of the viewport
    glGetIntegerv(GL_VIEWPORT, iViewport);*/

    // Save a copy of the projection matrix so that we can restore it 
    // when it's time to do 3D rendering again.
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();

    // Set up the orthographic projection
    gluOrtho2D(0.0, 1600, 900, 0);
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();

    // Make sure depth testing and lighting are disabled for 2D rendering until
    // we are finished rendering in 2D
    glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );
}

// Désctive l'affichage 2D
void Controler::glDisable2D() {
        glPopAttrib();
        glMatrixMode( GL_PROJECTION );
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();
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
















void Dessiner() {
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
