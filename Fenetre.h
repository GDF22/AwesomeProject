/* 
 * File:   Fenetre.h
 * Author: Administrator
 *
 * Created on 18 octobre 2013, 10:30
 */

#ifndef FENETRE_H
#define	FENETRE_H

#include<SDL/SDL.h>
#include <SDL/SDL_getenv.h>

class Fenetre {
public:
    Fenetre(int hauteur, int largeur);
    virtual ~Fenetre();
private:

};

#endif	/* FENETRE_H */
