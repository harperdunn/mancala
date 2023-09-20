//
//  main.cpp
//  Project3
//
//  Created by Harper Dunn on 5/17/23.
//
#include<iostream>
#include <cassert>
using namespace std;
#include "Board.h"
#include "Player.h"
#include "Game.h"

void waitForEnter(){
    cout<<"Press enter to continue.";
    string input;
    cin.ignore(100000, '\n');
    getline(cin, input);
}

void testgame(){
    Board gb(6, 4);//creates board with 4 holes 3
    HumanPlayer* human=new HumanPlayer("human");
    BadPlayer* badOne=new BadPlayer("badOne");
    SmartPlayer* smartie=new SmartPlayer("smartie");
    SmartPlayer* smartie2=new SmartPlayer("2nd");

    Game ggfam(gb, smartie, smartie2);
    ggfam.display();//should display a board with 4 holes per side
//    ggfam.move(SOUTH);
//    ggfam.move(SOUTH);
    ggfam.play();
    delete human;
    delete badOne;
    delete smartie;
    delete smartie2;
}
int main(){
    testgame();
    cerr<<"passed all "<<endl;
}



