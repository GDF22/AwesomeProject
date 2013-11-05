/* 
 * File:   Panel.cpp
 * Author: GDF
 * 
 * Created on 2 novembre 2013, 16:36
 */

#include "Panel.h"
#include "Button.h"
#include "Color.h"
#include <typeinfo>
#include <string>

using namespace std;

Panel::Panel() {
}

Panel::Panel(string name ,Coord3D cp , int width , int height, Color* color) : Component(name) {
    this->position = cp;
    this->width = width;
    this->height = height;
    this->c = color;
    this->visible = true;

}

Panel::Panel(SDL_Surface* screen) {
    this->sdlPanel = screen;
}


Panel::~Panel() {
}

void Panel::addComponent(Component* toAdd) {
    toAdd->setParent(this);
    Component::addComponent(toAdd);
}

void Panel::draw(){
    if( visible ){
        if( c != NULL ){
            glBegin(GL_QUADS);
                glColor3ub(c->getR(), c->getG(), c->getB());
                glVertex2i(position.getX(), position.getY());
                glVertex2i(position.getX()+width, position.getY());
                glVertex2i(position.getX()+width, position.getY()+height);
                glVertex2i(position.getX(), position.getY()+height);
            glEnd();
        }
        for(unsigned int i=0; i<componentList.size(); ++i){
                   Component* el = componentList[i];
                   if ( el->isVisible() ){
                       if(typeid(*el) == typeid(Panel)) ((Panel*) el)->draw();
                       else if(typeid(*el) == typeid(Button)) ((Button*) el)->draw();
                      // else if(typeid(*el) == typeid(Label)) ((Label*) el)->draw();
                      // else if(typeid(*el) == typeid(TextField)) ((TextField*) el)->draw();
                   }
        }

    }
}
