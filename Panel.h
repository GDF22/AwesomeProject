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
#include <SDL/SDL.h>

class Panel : public Component {
public:
    Panel();
    Panel(Coord3D cp , int width , int height);
    Panel(SDL_Surface* parent);
    void addComponent(Component toAdd);
    virtual ~Panel();
    void draw(Panel* parent);
private:
    vector<Component> componentList;
    int width;
    int height;
    SDL_Surface* sdlPanel;

};

#endif	/* PANEL_H */

