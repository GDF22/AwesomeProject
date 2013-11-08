/* 
 * File:   Fenetre.cpp
 * Author: Administrator
 * 
 * Created on 18 octobre 2013, 10:30
 */

#include "Fenetre.h"

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

Fenetre::Fenetre(int hauteur, int largeur) {
    SDL_Init(SDL_INIT_VIDEO);
  //  TTF_Init();
    atexit(SDL_Quit);
    putenv("SDL_VIDEO_WINDOW_POS==0,0");
    SDL_WM_SetCaption("SDL GL Application", NULL);
    this->screen = SDL_SetVideoMode(hauteur, largeur, 32, SDL_OPENGL);
}

SDL_Surface* Fenetre::getScreen(){
    return screen;
}

Fenetre::~Fenetre() {
    SDL_Quit();
}

