/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 9 octobre 2013, 10:22
 */

#include "Controler.h"
#include "Panel.h"

int main(int argc, char *argv[])
{
    freopen("CON", "w", stdout);    // redirection des flux
    freopen("CON", "w", stderr);
    
    Fenetre fenetre(1600, 900);
    
    Panel screenPanel(fenetre.getScreen());
    
    Coord3D cp = Coord3D(20.0,20.0,0.0);
       
    Panel p =  Panel(cp,50,50);
    screenPanel.addComponent(p);
        
    screenPanel.draw(&screenPanel);
    
    Controler controler = Controler();
    
    controler.run();
 
    return 0;
}
 
