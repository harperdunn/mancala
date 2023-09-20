//
//  Game.cpp
//  Project3
//
//  Created by Harper Dunn on 5/21/23.
//

#include "Game.h"
#include "Player.h"
#include <iostream>
#include<climits>
using namespace std;
Game::Game(const Board& b, Player* south, Player* north):m_board(Board(b)), m_southPlayer(south), m_northPlayer(north){
    //1. construct board copy into member variable
}
//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
//first display "north" to represent north's side. then on a new line, print out the hole numbers starting at #1 from left to right. on a new line, iterate through north's array of holes printing out the values at each index in order starting from 1. print out north pot values then southpot value on the same line. then on a new line, do the same thing as above but first print out the values at south's array, then the hole numbers, then south. this is also in order left to right starting at hole #1.
void Game::display() const{
    cout<<"                North               "<<endl;
    cout<<"              ";
    for(int i=1; i<=m_board.holes();i++){
        cout<<i<<" ";
    }
    cout<<endl; cout<<"              ";
    for(int i=0; i<m_board.holes();i++){
        cout<<m_board.beans(NORTH, i+1)<<" ";
    }
    cout<<endl;
    cout<<"North's Pot "<<m_board.beans(NORTH, 0)<<"              "<<m_board.beans(SOUTH, 0)<<"  South's Pot"<<endl;
    cout<<"              ";
    for(int i=0; i<m_board.holes();i++){
        cout<<m_board.beans(SOUTH, i+1)<<" ";
    }
    cout<<endl;
    cout<<"              ";
    for(int i=1; i<=m_board.holes();i++){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"                 South               "<<endl;    
}
//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.

void Game::status(bool& over, bool& hasWinner, Side& winner) const{
    //no beans on the board after calling move means the game has ended
    if (m_board.beansInPlay(SOUTH)==0&&m_board.beansInPlay(NORTH)==0) over=true;
    else {over=false; return;}
    //if over, set winner to the side whose pot has more beans
    if(m_board.beans(SOUTH, 0)>m_board.beans(NORTH, 0)){hasWinner=true;winner=SOUTH;}
    else if(m_board.beans(NORTH, 0)>m_board.beans(SOUTH, 0)){hasWinner=true; winner=NORTH;}
    else hasWinner=false;
    
}
//If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.

//Whenever the player whose turn it is can not make a move (because their side is empty), any beans remaining in their opponent's holes are put into that opponent's pot and the game is over. The winner is the player whose pot has the most beans.

bool Game::move(Side s){
    Side endSide;
    int endHole=-1;
    int chosenMove;
    if(s==SOUTH){
         chosenMove= m_southPlayer->chooseMove(m_board, s);
        if(chosenMove==-1){ //no possible move
            //sweep all opponent's beans into that opponents pot and return false
            for (int i=1; i<=m_board.holes();i++){
                m_board.moveToPot(NORTH, i, NORTH);
            }
            return false;
        }
    }
    else{ //player side is north
     chosenMove= m_northPlayer->chooseMove(m_board, s);
    if(chosenMove==-1){
        //sweep all opponent's beans into that opponents pot and return false
        for (int i=1; i<=m_board.holes();i++){
            //moving beans to south pot
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
        return false;
    }
}
    if(s==SOUTH)cout<<"SOUTH chose move: hole "<<chosenMove<<endl;
    else cout<<"NORTH chose move: hole "<<chosenMove<<endl;
    m_board.sow(s, chosenMove, endSide, endHole);
    
    //if the last bean was placed in players own pot, they get another turn.
    if(endSide==s&&endHole==0){
        display();
        if(s==SOUTH&&m_southPlayer->isInteractive()==false) waitForEnter();//if its south's turn and theyre not interactive, wait for enter so the human can follow along
        else if(m_northPlayer->isInteractive()==false) waitForEnter();//if its north's turn and theyre not interactive, wait for enter so the human can follow along
        move(s);
        return true;
    }
    else if(m_board.beansInPlay(s)!=0){
    //If the last bean was placed in one of the player's own holes that was empty just a moment before, and if the opponent's hole directly opposite from that hole is not empty,
        Side otherside=SOUTH;
        if(endSide==SOUTH) otherside=NORTH;
        if(endSide==s&&m_board.beans(endSide, endHole)==1&&m_board.beans(otherside, endHole)!=0){
        //then that last bean and all beans in the opponent's hole directly opposite from that hole are put into the player's pot, and the turn ends.
        m_board.moveToPot(endSide, endHole, s);
        m_board.moveToPot(otherside, endHole, s);
        cout<<"You have made a capture!"<<endl;
        display(); return true;//ends turn
    }
    }
        //if after the player sowed, there are no longer beans on their side, so sweep the opponents into opponents pot and return false.
//    if(m_board.beansInPlay(s)==0){
//        //Redefine otherside to mean the opposite side of the player
//        Side otherside=SOUTH;
//        if(s==SOUTH)otherside=NORTH;
//            for (int i=1; i<=m_board.holes();i++){
//                //moving beans to south pot
//                m_board.moveToPot(otherside, i, otherside);
//            }
//        return false;
    //}
    //all other cases, move was completed
    display();
    return true;
}


void Game::play(){
    bool over;
    bool hasWinner;
    Side sWinner;
    status(over, hasWinner, sWinner);
    //while over is not set to false
    while(!over){
        //if move function returns false, no more beans on that side so game is over.
        if(move(SOUTH)==false){status(over, hasWinner, sWinner);break;}
        status(over,  hasWinner, sWinner);
        //if games over after move then break as well
        if(over)break;
        if(!m_northPlayer->isInteractive()) waitForEnter();
        if(move(NORTH)==false){status(over, hasWinner, sWinner);break;}
        status(over, hasWinner, sWinner);
        if(over)break;
        if(!m_southPlayer->isInteractive()) waitForEnter();
        status(over, hasWinner, sWinner);
    }
    //game is over:
    if(hasWinner){
        display();
        if(sWinner==SOUTH)
            cout<<"And the winner is.... "+m_southPlayer->name()+"! Congratulations!"<<endl;
        else  cout<<"And the winner is.... "+m_northPlayer->name()+"! Congratulations!"<<endl;
    }
    else cout<<"It is a tie. "<<endl;
}
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.

//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
