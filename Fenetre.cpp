/* 
 * File:   Fenetre.cpp
 * Author: Administrator
 * 
 * Created on 18 octobre 2013, 10:30
 */

#include "Fenetre.h"
#include<SDL/SDL.h>

Fenetre::Fenetre(int hauteur, int largeur) {
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(hauteur, largeur, 32, SDL_OPENGL);

}


Fenetre::~Fenetre() {
    SDL_Quit();
}

