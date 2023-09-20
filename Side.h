//
//  Side.h
//  Project3
//
//  Created by Harper Dunn on 5/17/23.
//

#ifndef Side_h
#define Side_h
enum Side { NORTH, SOUTH };

    const int NSIDES = 2;
    const int POT = 0;

    inline
    Side opponent(Side s)
    {
        return Side(NSIDES - 1 - s);
    }
//nonmember function to wait for user to press enter to continue
void waitForEnter();
//north is 0 south is 1
//If you want to add publicly accessible functionality to a class, do it through non-member functions declared in Side.h and implemented in Main.cpp. For example, given a board, both Game::move and SmartPlayer::chooseMove may want to take some similar actions on that board for a player. You could have them both call a non-member function that takes a Board& parameter and uses only the public interface of Board.

#endif /* Side_h */
