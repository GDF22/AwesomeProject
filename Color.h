/* 
 * File:   Color.h
 * Author: GDF
 *
 * Created on 2 novembre 2013, 19:58
 */

#ifndef COLOR_H
#define	COLOR_H

#include <iostream>

using namespace std;

class Color {
public:
    Color();
    Color(float r , float g , float b);
//    Color(int r, int g, int b);
    Color(const Color& orig);
    virtual ~Color();
    float getR();
    float getG();
    float getB();
    
    void setR(float r);
    void setG(float g);
    void setB(float b);
    
private:
    float r;
    float g;
    float b;
};

#endif	/* COLOR_H */

