#ifndef MENU_H
#define MENU_H

#include "arbiter.h"
#include "toplist.h"

///----------------------------------------------------------------------------|
/// Menu.
///----------------------------------------------------------------------- Menu:
struct  Menu : protected ResurcesHolder
{       Menu() :    keys ({ (unsigned char)('1'),
                            (unsigned char)('2'),
                            (unsigned char)('3'),
                             27
                    }),
                    arbiter(scr)
        {
            scr.write({cfg.W - cfg. version.size(),   0},
                               std::wstring(cfg.version));

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

                        Toplist* tp = (Toplist*)res->get(Resurces::E_TOPLIST);
                                 tp->save();
                        break;
                    }

                    case '2':
                    {   arbiter.start_game_two_play();

                        show_banner_center_clear_pause(
                            (Bunner*)res->get(Resurces::E_TODO));
                        break;
                    }

                    case '3':///////////////////////////////////////////////////
                    {
                        show_banner_center_clear_pause(
                            (Toplist*)res->get(Resurces::E_TOPLIST));
                        break;
                    }

                    case  27: return;
                }
            }
        }
    }

private:
    VScreen     scr ;
    Hard        hard;
    KeysProfile keys;
    Arbiter  arbiter;

    template<typename T>
    void show_banner_center(T* bann)
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

    void show_banner_center_clear_pause(Toplist* bann)
    {   scr.clear               ();
        show_banner_center      (bann);
        DEVICE.pause_press_enter(L"PRESS ENTER");
        clean                   ();
    }


};

#endif // MENU_H
