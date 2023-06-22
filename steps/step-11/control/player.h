#ifndef PLAYER_H
#define PLAYER_H

#include "../game.h"

///----------------------------------------------------------------------------|
/// Player.
///--------------------------------------------------------------------- Player:
struct  Player
{       Player()
        {

        }

    std::wstring name{L"???"};

    void set(Game* g){ game = g; }



private:
    Game* game = nullptr;
};

#endif // PLAYER_H
