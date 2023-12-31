//
//  Board.hpp
//  Project3
//
//  Created by Harper Dunn on 5/17/23.
//
//(Exception: if the compiler-generated bookkeeping functions (destructor, copy constructor, and assignment operator) don't do the right thing, declare and implement your own.) You may add any private data members and private member functions you like to those classes. You may add protected member functions to those classes if you wish, but you must not add any protected data members. (We haven't talked about protected members in this course.) The word friend must not appear in your program.
//The Board class is responsible for maintaining the board. A Board object knows about the holes, pots, and beans. For those functions that talk about specific holes, the holes are indicated by a Side and hole number. The holes are numbered as indicated in the diagrams above; a pot is considered hole #0. Thus, North's hole #1 is next to North's pot; South's hole #6 is next to South's pot. Notice that this numbering of holes is an aspect of the class's interface and our test code will depend on it. Of course, your implementations of the functions are free to map that numbering scheme into something more convenient for their internal use.
#ifndef Board_h
#define Board_h
#include "Side.h"
class Board{
    //tentative
public:
    Board(int nHoles, int nInitialBeansPerHole);
   // Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
    //copy constructor
    Board(const Board& other);
    ~Board();
    int holes() const;
   // Return the number of holes on a side (not counting the pot).
    int beans(Side s, int hole) const;
    //Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
    int beansInPlay(Side s) const;
   // Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
    int totalBeans() const;
   // Return the total number of beans in the game, including any in the pots.
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    //If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
    bool moveToPot(Side s, int hole, Side potOwner);
   // If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
    bool setBeans(Side s, int hole, int beans);
private:
    int m_holesPerSide;
    int m_totalBeans;
    int northPot;
    int southPot;
    int* northHoles;
    int* southHoles;
    
};

#endif /* Board_h */
