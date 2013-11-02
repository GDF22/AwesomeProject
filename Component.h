/* 
 * File:   Component.h
 * Author: GDF
 *
 * Created on 2 novembre 2013, 16:34
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include "Coord3D.h"

class Component {
public:
    Component();
    Component(const Component& orig);
    virtual ~Component();
    void draw(Component* parent);
protected:
    Coord3D position;

};

#endif	/* COMPONENT_H */

