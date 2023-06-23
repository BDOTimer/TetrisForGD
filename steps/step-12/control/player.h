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

    void set(Game* g){ game = g; }

    void to_toplist() const
    {
        std::string nm; nm << name;

        Toplist* tl =   (Toplist*)res ->get(Resurces::E_TOPLIST);
                 tl->add(nm,      game->get_counted());
    }



private:
    Game* game = nullptr;
};

#endif // PLAYER_H
