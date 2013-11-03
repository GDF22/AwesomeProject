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

Color::Color(float r , float g , float b) {
    this->setR(r);
    this->setG(g);
    this->setB(b);
}

/*
Color::Color(int r, int g, int b) {
    Color( (float) r/255 , (float) g/255 ,(float)  b/255);
}*/

Color::Color(const Color& orig) {
}

Color::~Color() {
}

float Color::getR(){
    return r;
}
float Color::getG(){
    return g;
}
float Color::getB(){
    return b;
}

void Color::setR(float r){   
    this->r = (float) (r < 0.0)? 0.0 :r;
    this->r = (float) (r > 1.0)? 1.0 :r;
}
void Color::setG(float g){
    this->g = (float) (g < 0.0)? 0.0 :g;
    this->g = (float) (g > 1.0)? 1.0 :g;
}
void Color::setB(float b){
    
    this->b = (float) (b < 0.0)? 0.0 :b;
    this->b = (float) (b > 1.0)? 1.0 :b;
}