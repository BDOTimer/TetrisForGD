#ifndef ARBITER_H
#define ARBITER_H

#include "resurces.h"
#include "player.h"

///----------------------------------------------------------------------------|
/// Arbiter.
///-------------------------------------------------------------------- Arbiter:
struct  Arbiter
{       Arbiter(VScreen& Scr)
            :   scr     (Scr)
        {
        }

    char start_game_one_play()
    {
        if( pp.size () != 1)
        {   pp.clear();
            pp.push_back(Player());

            auto name = input_name();

            if(name[0] == '?')
            {
                return '?';
            }

            pp.back().name = name ;
        }

        Game game     (scr, pp.back().name); pp.back().set(&game);
             game.add_to_name();
             game.init       ();
             game.run        ();

        to_toplist();

        return 'z';
    }

    void start_game_two_play()
    {

    }

private:
    VScreen&      scr;
    InputString input;

    std::vector<Player> pp;

    std::wstring input_name()
    {
        auto str = input.get(L"Ваше имя?");

        return str.empty() ? L"???" : str;
    }

    void to_toplist()
    {   for(const auto& pl : pp)
        {   pl.to_toplist();
        }
    }
};

#endif // ARBITER_H
