/* 
 * File:   Component.h
 * Author: GDF
 *
 * Created on 2 novembre 2013, 16:34
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include "Coord3D.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>

class Component {
public:
    Component();
    Component(string name);
    Component(const Component& orig);
    virtual ~Component();
    virtual void draw(Component* par);
    void setName(string name);
    string getName();
    void setParent(Component* parent);
    void addComponent(Component* toAdd);
    bool isVisible();
    void toggleVisible();
    Component* getElementByName(string name);
    void setVisible(bool isVisible);
protected:
    vector<Component*> componentList;
    string name;
    Coord3D position;
    bool visible;
    Component* parent;
};

#endif	/* COMPONENT_H */

