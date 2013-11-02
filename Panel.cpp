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
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
    glEnd();


    for(unsigned int i=0; i<componentList.size(); ++i)
        {
               Component& el = componentList[i];
               el.draw(this);
        }
    
    
}
