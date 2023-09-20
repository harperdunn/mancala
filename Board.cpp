//
//  Board.cpp
//  Project3
//
//  Created by Harper Dunn on 5/17/23.
//
//(Exception: if the compiler-generated bookkeeping functions (destructor, copy constructor, and assignment operator) don't do the right thing, declare and implement your own.) You may add any private data members and private member functions you like to those classes. You may add protected member functions to those classes if you wish, but you must not add any protected data members. (We haven't talked about protected members in this course.) The word friend must not appear in your program.
//The Board class is responsible for maintaining the board. A Board object knows about the holes, pots, and beans. For those functions that talk about specific holes, the holes are indicated by a Side and hole number. The holes are numbered as indicated in the diagrams above; a pot is considered hole #0. Thus, North's hole #1 is next to North's pot; South's hole #6 is next to South's pot. Notice that this numbering of holes is an aspect of the class's interface and our test code will depend on it. Of course, your implementations of the functions are free to map that numbering scheme into something more convenient for their internal use.
//i think represent the pots as hole 0 for south and north
#include "Side.h"
#include "Board.h"
#include<iostream>
using namespace std;
//MVS: private:
//int m_holesPerSide;
//int m_totalBeans;
//int* northHoles;
//int* southHoles;
//north pot is hole #0 south pot is hole #-4. but of course the arrays are filled at a[hole-1] with each value in each hole. pot values are NOT stored in the arrays they are stored in northPot and southPot.
Board::Board(int nHoles, int nInitialBeansPerHole){
    //create dynamic arrays of ints representing the holes on each side, with corresponding # of holes and initial beans. set pot values to 0.
    if(nHoles<=0)nHoles=1;
    if(nInitialBeansPerHole<0)nInitialBeansPerHole=0;
    //each array is number of holes per side and the values represent # of beans in each hole
    southHoles=new int[nHoles];
    northHoles=new int[nHoles];
    //set the holes to the correct amount of initial beans
    for(int i=0; i<nHoles; i++){
        southHoles[i]=nInitialBeansPerHole;
        northHoles[i]=nInitialBeansPerHole;
    }
    m_holesPerSide=nHoles; //set holes per side
    m_totalBeans=NSIDES*(nHoles*nInitialBeansPerHole);//nholes is holes per side so multiply by side and beans per hole
    //northpot and southpot both start at 0
    northPot=POT;
    southPot=POT;
    
}

Board::Board(const Board& other){
    m_holesPerSide=other.m_holesPerSide;
    northPot=other.northPot;
    southPot=other.southPot;
    m_totalBeans=other.m_totalBeans;
    southHoles=new int[m_holesPerSide];
    northHoles= new int[m_holesPerSide];
    for(int i=0; i<m_holesPerSide;i++){
        southHoles[i]=other.southHoles[i];
        northHoles[i]=other.northHoles[i];
    }
    
}
//destructor, deallocating dynamic memory
Board::~Board(){
    delete [] northHoles;
    delete [] southHoles;
}
// Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.*/
 int Board::holes() const{
     return m_holesPerSide;
 }
// Return the number of holes on a side (not counting the pot).

//pseudo: a hole #0 means pot, rest correspond to index-1 of array
int Board::beans(Side s, int hole) const{
    if(hole>0&&hole<=m_holesPerSide){
    //side NORTH=0,SOUTH=1
    if(s==NORTH){
        return northHoles[hole-1];
    }
    if(s==SOUTH){
        return southHoles[hole-1];
    }
    }
    //hole #0 means pot
    else if(hole==0){
        if(s==SOUTH)return southPot;
        else return northPot;
    }
    return -1;
}
 //Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
//pseudo: iterate through arrays returning sum of number of beans in each side's holes
int Board::beansInPlay(Side s) const{
    int countbeans=0;
    if(s==NORTH){
        //iterate through north's array, adding value at each index to total
        for(int i=0; i<m_holesPerSide; i++){
            countbeans+=northHoles[i];
        }
    }
    else{ //s==SOUTH
        for(int i=0; i<m_holesPerSide; i++){
            countbeans+=southHoles[i];
        }
    }
    return countbeans;
}
 //Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::totalBeans() const{
    //add beans in play for each side plus the beans in the 2 pots
    return beansInPlay(NORTH)+beansInPlay(SOUTH)+northPot+southPot;
}
 //Return the total number of beans in the game, including any in the pots.
//pseudo: if a valid hole is passed in, set holet to 0 beans, then add beans one by one to each hole of the array. in this function, south's holes are represented by negative numbers, and south's pot is -(#of holes)-1, north's pot is 0. at the end the endhole values are converted to positive numbers and 0 if it is a pot.
bool Board::sow(Side s, int hole, Side& endSide, int& endHole){
    //If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything.
    if(hole<=0||hole>m_holesPerSide)return false; //hole is invalid or a pot (0)
    if(beans(s, hole)<=0) return false; //hole is empty, invalid move
    //ok so the rules for changing the hole are gonna be very special. if negative, south. if zero, pot. if positive, north
    int beansInHand=beans(s, hole);
    if(s==NORTH){
        northHoles[hole-1]=0;
        hole--;
        while(beansInHand>0){
            if(hole==0) northPot++;
            else if(hole>0) northHoles[hole-1]++;
            //else hole<0
            else southHoles[(-1*hole)-1]++;
            //ok extremely important step. determining what to set the next hole to. consider ALL options
            beansInHand--;
            if(beansInHand==0)break;//so that we stop at the last hole that something was put in
            else{
                if(hole<0){
                    //if hole is at end of south's holes, you set it back to equal north's last hole on the right (positive ofc)
                    if((-1*hole+1)>m_holesPerSide) hole=m_holesPerSide;
                }
                hole--;
            }
        }
        
    }
    //s==SOUTH
    //southpot is hole # -m_holesperside
    else{
        southHoles[hole-1]=0;
        hole*=-1;//make hole negative to represent its on the south side
        hole--;
        while(beansInHand>0){
            if(hole==(-1*(m_holesPerSide+1)))southPot++;
            else if(hole<0){
                southHoles[(-1*hole) -1]++;
            }
            //hole>0, means we're on north
            else{
                northHoles[hole-1]++;
            }
            beansInHand--;
            if(beansInHand==0)break;
            //reassigning holes to next hole
            else{
                if(hole==(-1*(m_holesPerSide+1)))hole=m_holesPerSide;
                else if(hole==1)hole=-1;
                else hole--;
            }
        }
    }
    //setting endside and endhole, positive represents north negative is south
    //question- should i translate my numbers into like regular holes- turning south positive and the pots both being 0??? not sure how beneficial
    //ok translating numbers- making south number positive, and if it's south pot(-4) we return 0 for the hole
    if(hole>=0)endSide=NORTH;
    else{
        endSide=SOUTH;
        if(hole==-1*(m_holesPerSide+1))hole=0;
        else hole=(-1*hole);
    }
    endHole=hole;
    return true;

}
//  Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)

//set corresponding hole to have 0 beans. add value to the northPot or southPot member variable
bool Board::moveToPot(Side s, int hole, Side potOwner){
    if(hole<=0||hole>m_holesPerSide) return false;
    //move all beans in hole into the pot belonging to potowner and return true
    int beansInHand=beans(s, hole);
    if(s==NORTH){
        //set hole to have 0 beans
        northHoles[hole-1]=0;
        //add beans to given pot
    }
    //else we're taking beans from south hole
    else{
        southHoles[hole-1]=0;
    }
    //put beans in pots
    if (potOwner==NORTH){
        northPot+=beansInHand;
    }
    else {
        southPot+=beansInHand;
    }
    return true;
}
// If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.

//JUST FOR TESTING
bool Board::setBeans(Side s, int hole, int beans){
    //ok for now we're pretending the input has to be positive and if you put 0 its the pot
    if(hole<0||hole>m_holesPerSide)return false;
    if(beans<0)return false;
    if(hole==0){
        if(s==NORTH)northPot=beans;
        else southPot=beans;
    }
    else{
        if(s==NORTH)northHoles[hole-1]=beans;
        else southHoles[hole-1]=beans;
    }
    return true;
}
 //If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)

