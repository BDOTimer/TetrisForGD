#ifndef MENU_H
#define MENU_H

#include "../game.h"
#include "resurces.h"

struct  Menu : protected ResurcesHolder
{       Menu()
        {
            show_banner_center((Bunner*)res->get(Resurces::E_LOGO));

            Game run(scr);

            show_banner_center((Bunner*)res->get(Resurces::E_GAME_OVER));

            show_banner_center((Bunner*)res->get(Resurces::E_PROG_FINISHED));
        }

private:
    VScreen scr ;
    Hard    hard;

    void show_banner_center(Bunner* bann)
    {
        scr.write(scr.get_pos_center(*bann), *bann);

        DEVICE.set_cursor_to_start();
        hard << scr;

        DEVICE.pause_press_enter(L"PRESS ENTER");

        //scr.clear();

        DEVICE.set_cursor_to_start();
        hard   <<  scr;

        DEVICE <<   "              \n";
    }
};

#endif // MENU_H
