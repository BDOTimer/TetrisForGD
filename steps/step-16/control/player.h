#ifndef PLAYER_H
#define PLAYER_H

#include "../game.h"
#include "toplist.h"

///----------------------------------------------------------------------------|
/// Player.
///--------------------------------------------------------------------- Player:
struct  Player : protected ResurcesHolder
{       Player()
        {

        }

    std::wstring name{L"???"};
    int          win = 0;

    void set(Game* g){ game = g; }

    void to_toplist() const
    {
        Toplist* tl =   (Toplist*)res ->get(Resurces::E_TOPLIST);
                 tl->add(name,    game->get_counted());
    }


    Game* game = nullptr;
};

#endif // PLAYER_H
