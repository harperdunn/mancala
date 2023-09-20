//
//  Player.hpp
//  Project3
//
//  Created by Harper Dunn on 5/17/23.
//

#ifndef Player_h
#define Player_h
#include<string>
#include <vector>
#include "Board.h"
#include "Side.h"
class Player{
public:
    Player(std::string name);
    //Create a Player with the indicated name.
    std::string name() const;
    //Return the name of the player.
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    //Since this class is designed as a base class, it should have a virtual destructor.
    //Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
private:
   std::string m_name;

};

class HumanPlayer : public Player{
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~HumanPlayer();
    //Since this class is designed as a base class, it should have a virtual destructor.
    //Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
};
class BadPlayer : public Player{
public:
    BadPlayer(std::string name);
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~BadPlayer();
    //Since this class is designed as a base class, it should have a virtual destructor.
    //Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
};

class SmartPlayer: public Player{
public:
    SmartPlayer(std::string name);
    virtual bool isInteractive() const;
    //Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const;
    //Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~SmartPlayer();
    //Since this class is designed as a base class, it should have a virtual destructor.
    //Each concrete class derived from Player will implement the chooseMove function in its own way. Of the classes listed here, only HumanPlayer::isInteractive should return true. (When testing, we may supply other kinds of interactive players.) Each of the three classes listed here must have a constructor taking a string representing the name of the player.
private:
    void minimax(int& bestHole, int& value, const Board b, Side s, int depth) const;
        int eval(const Board& b, Side s) const;
    Side opponent(Side s) const{
        if(s==NORTH) return SOUTH;
        else return NORTH;
    }
};

#endif /* Player_h */

