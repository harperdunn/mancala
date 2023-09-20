//
//  Player.cpp
//  Project3
//
//  Created by Harper Dunn on 5/17/23.
//

#include "Player.h"
#include "Board.h"
#include <string>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

//Player is an abstract base class that defines a common interface that all kinds of players (human and various computer players) must implement. It must support these public member functions:

Player::Player(std::string name):m_name(name){};
//Create a Player with the indicated name.
std::string Player::name() const{
    return m_name;
}
//Return the name of the player.

//not sure what to do with this tbh
bool Player::isInteractive() const{return 0;}
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.

 Player::~Player(){}
//Since this class is designed as a base class, it should have a virtual destructor.

//Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
//A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)

HumanPlayer::HumanPlayer(string name):Player(name){
    
}
bool HumanPlayer::isInteractive() const{
    return true;
}


int HumanPlayer::chooseMove(const Board& b, Side s) const{
    //no valid move if there's no beans in play on the player's side
    if(b.beansInPlay(s)==0)return -1;
    int holenumber=0;
    if(s==NORTH) cout<<"NORTH, Choose move: ";
    else cout<<"SOUTH, Choose move:";
    cin>>holenumber;
    //if the input is an invalid hole or there are no beans at that hole, we ask for them to choose different move
    while(holenumber<0||holenumber>b.holes()||b.beans(s, holenumber)==0){
        cout<<"Invalid. Please choose different move: ";
        cin>>holenumber;
    }
    cout<<endl;
    return holenumber;
}
//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
HumanPlayer::~HumanPlayer(){}
//Since this class is designed as a base class, it should have a virtual destructor.

//Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.

BadPlayer::BadPlayer(string name):Player(name){}

bool BadPlayer::isInteractive() const{return false;}
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
int BadPlayer::chooseMove(const Board& b, Side s) const{
    for(int i=1; i<=b.holes();i++){
        if(b.beans(s, i)!=0)return i;
    }
    return -1;
}//if no beans in any hole, there's no valid move

//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
BadPlayer::~BadPlayer(){
    
}
//Since this class is designed as a base class, it should have a virtual destructor.
//Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
SmartPlayer::SmartPlayer(string name):Player(name){
    
}

bool SmartPlayer::isInteractive() const{return false;}
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
 

int SmartPlayer::chooseMove(const Board& b, Side s) const{
    //wtf do you initialize these to
    if(b.beansInPlay(s)==0)return -1;
    int bestHole=-1;
    int value;
    if(s==SOUTH) value=INT_MIN;
    else value=INT_MAX;
    Board bboard(b);
    minimax(bestHole, value, bboard, s, 1);
    if(bestHole<=0||b.beans(s, bestHole)<=0){
        int j=-1;
        for(int i=1; i<=b.holes();i++){
            if(b.beans(s, i)!=0)j=i;
        }
        return j;
    }
    return bestHole;
}
//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
SmartPlayer::~SmartPlayer(){}
//Since this class is designed as a base class, it should have a virtual destructor.
//Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.

//minimax function searches game tree and returns what the best possible move is
void SmartPlayer::minimax(int& bestHole, int& value, const Board b, Side s, int depth) const{
    //ok so we stop this function when we reach a "leaf node": when the player can't play or if criterion says we shouldn't search below the node
    if(b.beansInPlay(s)==0){//no beans on their board so they cant play, MEANS LEAF NODE
        bestHole=-1;
        //wait should the value returned be the difference in pots after or before sweep. i think after sweep.
        value=eval(b, s);//value = value of this position (i.e., +∞, -∞, or 0)
        return;}
       if(depth >=7) //criterion
       {
           //cerr << "searchDepth reached" << endl;
           bestHole = -1;
           value = eval(b, s);
           return;
       }
    Side otherside=SOUTH;
    if(s==SOUTH)otherside=NORTH;
    //we're gonna do minimax on all the possible moves you can make on this copy board, and take the largest value for eval if the side is south, smallest if it's north's turn
    for(int i=1; i<=b.holes(); i++)
    {
        //for each hole that has beans in it, we "test" a move
        if(b.beans(s, i)>0){
            //create entirely new copy of the board.
            Board boardcopy(b);
            Side endSide;
            int endHole;
            //"make" move now
          boardcopy.sow(s, i, endSide, endHole); //now copy looks like the board after you make the move
            //if we end on players own pot, they get to go again, so you actually call minimax on the NEXT moves possible
            if(endSide==s&&endHole==0) {minimax(bestHole, value, boardcopy, s, depth+1); return;}
                
            //if we didn't land on own pot, we check if the move would result in a capture, and change the copy's values accordingly:
            else if(endSide==s&&boardcopy.beans(endSide, endHole)==1&&boardcopy.beans(otherside, endHole)!=0){
                //then that last bean and all beans in the opponent's hole directly opposite from that hole are put into the player's pot, and the turn ends.){
                boardcopy.moveToPot(endSide, endHole, s);
                boardcopy.moveToPot(otherside, endHole, s);
                //the turn is over now, so assign the eval.
            //turn is over, so evaluate opponent's minimax
            }
            int opponentHole=-1;
            int opponentVal;
            if(s==SOUTH)opponentVal=INT_MIN;
            else opponentVal=INT_MAX;
            //finds best response move by opponent
               minimax(opponentHole, opponentVal, boardcopy, otherside, depth+1);
            //if below node has a "better" value than this node has seen, assign this as the best move
            if(s==SOUTH) {if(opponentVal>=value) {value=opponentVal;bestHole=i;}}
            else{
                if(opponentVal<=value){value=opponentVal; bestHole=i;}}
            }
        }
}
                
     
    
//evaluation function returns a number based on how good the position is in general. high if good for south low if good for north. side parameter shows whose turn it is
int SmartPlayer::eval(const Board& b, Side s) const{
    //it is s's turn. evaluating how good this position is.
    //if one move to win for south
    int value;
    Board copyb(b); //creates copy of the current board.
//
    if(b.beansInPlay(s)==0){ //game is over because it's s's turn and their beans are 0.
        int sweptbeans=0;
        for(int i=1; i<=b.holes(); i++){
            sweptbeans+=copyb.beans(opponent(s), i);
        }
        //adding the swept beans to the value calculation
        if(s==SOUTH) value= (copyb.beans(SOUTH,0)-b.beans(NORTH,0)-sweptbeans);//beans were swept to north's pot
        else value= copyb.beans(SOUTH,0)+sweptbeans-copyb.beans(NORTH,0);//beans were swept to souths pot
        //if south won, eval is infinity, if north won, it's -infinity
        if(value>0) return INT_MAX; //because its super desirable because it's a win for SOUTH
        else if(value<0)return INT_MIN;
        if(value==0) return 0;//tie
    }
//    else {
//        Side endSide;
//        int endHole;
//        for(int i=1; i<copyb.holes();i++){
//            Board copyb2(b);
//            if(copyb.beans(s, i)>0){
//                copyb.sow(s, i, endSide, endHole);
//                //one move to get another turn, so this board position is desirable
//                if(endSide==s&&endHole==0){
//                    if(s==SOUTH) return 100;
//                    else return -100; //good for north
//                }
//            }
//        }
//    }
    //all other cases just return difference between pots on the board.
    value= copyb.beans(SOUTH, 0)-copyb.beans(NORTH, 0);
    return value;
}
