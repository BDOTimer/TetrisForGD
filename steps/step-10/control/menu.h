#ifndef MENU_H
#define MENU_H

#include "arbiter.h"

struct  Menu : protected ResurcesHolder
{       Menu() :    keys ({ (unsigned char)('1'),
                            (unsigned char)('2'),
                            (unsigned char)('3'),
                             27
                    }),
                    arbiter(scr)
        {
            show_banner_center_pause((Bunner*)res->get(Resurces::E_LOGO));

            menu_start();

            show_banner_center_clear_pause(
                (Bunner*)res->get(Resurces::E_PROG_FINISHED));

            scr.clear(L' ');
            DEVICE.set_cursor_to_start();
            hard << scr;
            DEVICE.set_cursor_to_start();
        }

    ///-----------------------|
    /// Стартове меню.        |
    ///-----------------------:
    void menu_start()
    {
        while(true)
        {
            show_banner_center_clear((Bunner*)res->get(Resurces::E_MENU_START));

            ///--------------------------------|
            /// Клавиатура.                    |
            ///--------------------------------:
            if(const int key = keys.scan(); key)
            {
                switch((char)key)
                {
                    case '1':
                    {   char what = arbiter.start_game_one_play();

                        if(what == 'z')
                        {
                            show_banner_center_pause(
                                (Bunner*)res->get(Resurces::E_GAME_OVER));
                        }
                        break;
                    }
                    case '2':
                    {   arbiter.start_game_two_play();

                        show_banner_center_clear_pause(
                            (Bunner*)res->get(Resurces::E_TODO));
                        break;
                    }
                    case '3':                  break;
                    case  27:                 return;
                }
            }
        }
    }

private:
    VScreen     scr ;
    Hard        hard;
    KeysProfile keys;
    Arbiter  arbiter;

    void show_banner_center(Bunner* bann)
    {
        scr.write(scr.get_pos_center(*bann), *bann);

        DEVICE.set_cursor_to_start();
        hard << scr;
    }

    void show_banner_center_pause(Bunner* bann)
    {
        show_banner_center(bann);
        DEVICE.pause_press_enter(L"PRESS ENTER");
        clean();
    }

    void show_banner_center_clear(Bunner* bann)
    {   scr.clear         ();
        show_banner_center(bann);
    }

    void show_banner_center_clear_pause(Bunner* bann)
    {   scr.clear               ();
        show_banner_center      (bann);
        DEVICE.pause_press_enter(L"PRESS ENTER");
        clean                   ();
    }

    void clean()
    {   DEVICE.set_cursor_to_start();
        hard   <<  scr;
        DEVICE <<   "              \n";
    }
};

#endif // MENU_H
