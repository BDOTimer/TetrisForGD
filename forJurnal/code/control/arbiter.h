#ifndef ARBITER_H
#define ARBITER_H

#include "resurces.h"
#include "player.h"

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

        Game game (scr); pp.back().set(&game);
             game.run();

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
};

#endif // ARBITER_H
