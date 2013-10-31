/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 9 octobre 2013, 10:22
 */

#include "Controler.h"

int main(int argc, char *argv[])
{
    freopen("CON", "w", stdout);    // redirection des flux
    freopen("CON", "w", stderr);
    
    Fenetre fenetre(1600, 900);
    
    Controler controler = Controler();
    controler.run();
 
    return 0;
}
 
