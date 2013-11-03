/* 
 * File:   Component.cpp
 * Author: GDF
 * 
 * Created on 2 novembre 2013, 16:34
 */

#include "Component.h"

Component::Component() {
    this->visible = true;
    this->name ="";
    this->parent = this;
}

Component::Component(const Component& orig) {
}

Component::~Component() {
}

bool Component::isVisible(){
    return visible;
}

void Component::setVisible(bool isVisible){
    this->visible = isVisible;
}

void Component::setName(string name){
    this->name = name;
}

string Component::getName(){
    return this->name;    
}

void Component::draw(Component* par){
    
}

void Component::setParent(Component* parent){
    this->parent = parent;
}

void Component::addComponent(Component* toAdd){
    toAdd->setParent(this);
    componentList.push_back(toAdd);
}