/* 
 * File:   Color.cpp
 * Author: GDF
 * 
 * Created on 2 novembre 2013, 19:58
 */

#include "Color.h"

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(int r, int g, int b) {
    this->setR(r);
    this->setG(g);
    this->setB(b);
    cout << "constr couleur " << this->r << endl;
}

Color::Color(const Color& orig) {
}

Color::~Color() {
}


int Color::getR(){
    return(this->r);
}
int Color::getG(){
    return(this->g);
}
int Color::getB(){
    return(this->b);
}

void Color::setR(int r){   
    this->r = (r < 0)? 0 :r;
    this->r = (r > 255)? 255 :r;
}

void Color::setG(int g){
    this->g = (g < 0)? 0 :g;
    this->g = (g > 255)? 255 :g;
}

void Color::setB(int b){
    this->b = (b < 0)? 0 :b;
    this->b = (b > 255)? 255 :b;
}