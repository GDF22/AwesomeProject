/* 
 * File:   Color.cpp
 * Author: GDF
 * 
 * Created on 2 novembre 2013, 19:58
 */

#include "Color.h"

using namespace std;

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
}

Color::Color(int r, int g, int b) {
    this->setR(r);
    this->setG(g);
    this->setB(b);
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

void Color::setRGB(int r, int g, int b) {
    this->setR(r);
    this->setG(g);
    this->setB(b);
}

void Color::setColor(Color* color) {
    this->setR(color->getR());
    this->setG(color->getG());
    this->setB(color->getB());
}

string Color::toString() {
    string out = "";
    std::ostringstream ossr, ossg, ossb;
    
    out += "(";
    ossr << getR();
    out += ossr.str();
    out += ", ";
    ossg << getG();
    out += ossg.str();
    out += ", ";
    ossb << getB();
    out += ossb.str();
    out += ")";
    return(out);
}