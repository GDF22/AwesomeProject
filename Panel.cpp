/* 
 * File:   Panel.cpp
 * Author: GDF
 * 
 * Created on 2 novembre 2013, 16:36
 */

#include "Panel.h"
#include "Color.h"
#include <typeinfo>

Panel::Panel() {
}

Panel::Panel(Coord3D cp , int width , int height, Color color) {
    Component();
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

void Panel::addComponent(Component* toAdd){
    toAdd->setParent(this);
    Component::addComponent(toAdd);
}

void Panel::draw(){
    glBegin(GL_QUADS);
        glColor3ub(c.getR(), c.getG(), c.getB());
        glVertex2i(position.getX(), position.getY());
        glVertex2i(position.getX()+width, position.getY());
        glVertex2i(position.getX()+width, position.getY()+height);
        glVertex2i(position.getX(), position.getY()+height);
    glEnd();
    //cout<<"----------"<<this->getName()<<endl;
    for(unsigned int i=0; i<componentList.size(); ++i){
               Component* el = componentList[i];
               if ( el->isVisible() ){
                   if(typeid(*el) == typeid(Panel)) ((Panel*) el)->draw();
                  // else if(typeid(*el) == typeid(Button)) ((Button*) el)->draw(this);
                  // else if(typeid(*el) == typeid(Label)) ((Label*) el)->draw(this);
                  // else if(typeid(*el) == typeid(TextField)) ((TextField*) el)->draw(this);
               }
               //cout<<(el->isVisible()?"oui":"non")<<" : " << typeid(*el).name() <<" : '"<<el->getName()<<"'"<<endl;
    }
    //cout<<"----------"<<endl;
    
}
