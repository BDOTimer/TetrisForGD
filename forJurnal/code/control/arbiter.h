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

            auto name = input_name(L"PLAYER::");

            if(name[0] == '?')
            {   pp.clear();
                return '?';
            }

            pp.back().name = name ;
        }

        KeysProfileActionA a(data);

                          positioner_X.calc(Positioner_X::E_ONE, cfg);//////////
        const auto& pl1 = positioner_X.get (Positioner_X::E_ONE);

        Game game     (scr, pp.back().name, &a, pl1.disp, pl1.poskor_x);
             game.add_to_name();
             game.init       (); pp.back().set(&game);
             game.run        ();

        to_toplist();

        return 'z';
    }

    char start_game_two_play()
    {
        if( pp.size () != 2)
        {   pp.clear();

            {   pp.push_back(Player());
                auto name = input_name(L"FIRST PLAYER::");
                if(name[0] == '?') return '?';
                pp.back().name = name ;
            }

            {   pp.push_back(Player());
                auto name = input_name(L"SECOND PLAYER::");
                if(name[0] == '?') return '?';
                pp.back().name = name ;
            }
        }

        KeysProfileActionA a(data);
        KeysProfileActionB b(data);

                          positioner_X.calc(Positioner_X::E_TWO, cfg);//////////
        const auto& pl1 = positioner_X.get (Positioner_X::E_ONE);
        const auto& pl2 = positioner_X.get (Positioner_X::E_TWO);

        Game game1     (scr, pp.front().name, &b, pl1.disp, pl1.poskor_x);
             game1.add_to_name();
             game1.init       ();

             pp.front().set(&game1);

        Game game2     (scr, pp.back ().name, &a, pl2.disp, pl2.poskor_x);
             game2.add_to_name();
             game2.init       ();

             pp.back ().set(&game2);

        Hard hard;

        while(game1.done && game2.done)
        {
            DEVICE.set_cursor_to_start();
            scr.clear();

            data.scan();

            game1.loop_tick();
            game2.loop_tick();

            hard << scr;
        }

        to_toplist();

        return 'z';
    }

private:
    VScreen&              scr;
    InputString         input;
    KeysProfileData      data;
    Positioner_X positioner_X;

    std::vector<Player> pp;

    std::wstring input_name(std::wstring promt)
    {
        promt += L"Ваше имя?";

        auto str = input.get(promt);

        return str.empty() ? L"???" : str;
    }

    void to_toplist()
    {   for(auto& pl : pp)
        {   pl.to_toplist();
            if(pl.game->done) pl.win++;
        }
    }
};

#endif // ARBITER_H
