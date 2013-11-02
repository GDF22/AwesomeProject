/* 
 * File:   Panel.cpp
 * Author: GDF
 * 
 * Created on 2 novembre 2013, 16:36
 */

#include "Panel.h"

Panel::Panel() {
}

Panel::Panel(Coord3D cp , int width , int height) {
    this->position = cp;
    this->width = width;
    this->height = height;
}

Panel::Panel(SDL_Surface* screen) {
    this->sdlPanel = screen;
}


Panel::~Panel() {
}

void Panel::addComponent(Component toAdd){
    componentList.push_back(toAdd);
}

void Panel::draw(Panel* par){
    SDL_Surface* parent = par->sdlPanel;
    sdlPanel = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
    SDL_FillRect(sdlPanel, NULL, SDL_MapRGB(parent->format, 255, 255, 255));
    SDL_Rect sdlp = position.toSDL_Rect();
    SDL_BlitSurface(sdlPanel, NULL, parent, &sdlp);
    
    for(unsigned int i=0; i<componentList.size(); ++i)
        {
               Component& el = componentList[i];
               //el.draw(this);
        }
    
    SDL_Flip(parent);
    
}
