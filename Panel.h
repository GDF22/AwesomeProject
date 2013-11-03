/* 
 * File:   Panel.h
 * Author: GDF
 *
 * Created on 2 novembre 2013, 16:36
 */

#ifndef PANEL_H
#define	PANEL_H

#include <vector>
#include "Component.h"
#include "Color.h"
#include <SDL/SDL.h>
#include <gl/gl.h>
#include <gl/glu.h>

class Panel : public Component {
public:
    Panel();
    Panel(Coord3D cp , int width , int height, Color color);
    Panel(SDL_Surface* parent);
    void addComponent(Component* toAdd);
    virtual ~Panel();
    void draw();

private:
    
    int width;
    int height;
    SDL_Surface* sdlPanel;
    Color c;
       
};

#endif	/* PANEL_H */

