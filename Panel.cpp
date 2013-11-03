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
        glColor4f(255, 255, 255, 0.8); 
        glVertex2f(position.getX(), position.getY());
        glVertex2f(position.getX() + width, position.getY());
        glVertex2f(position.getX() + width, position.getY() + height);
        glVertex2f(position.getX(), position.getY() + height);
    glEnd();

    for(unsigned int i=0; i<componentList.size(); ++i)
    {
        Component& el = componentList[i];
        el.draw(this);
    }

}
