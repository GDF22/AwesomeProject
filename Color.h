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
    Color(int r, int g, int b);
    Color(const Color& orig);
    virtual ~Color();
    
    int getR();
    int getG();
    int getB();
    
    void setR(int r);
    void setG(int g);
    void setB(int b);
    
private:
    int r;
    int g;
    int b;
};

#endif	/* COLOR_H */

