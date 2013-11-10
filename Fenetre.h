/* 
 * File:   Fenetre.h
 * Author: Administrator
 *
 * Created on 18 octobre 2013, 10:30
 */

#ifndef FENETRE_H
#define	FENETRE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

class Fenetre {
public:
    Fenetre(int hauteur, int largeur);
    SDL_Surface* getScreen();
    virtual ~Fenetre();
private:
    SDL_Surface *screen;

};

#endif	/* FENETRE_H */

