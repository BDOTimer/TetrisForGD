#ifndef MENU_H
#define MENU_H

#include "arbiter.h"
#include "toplist.h"
#include "scenaries.h"

///----------------------------------------------------------------------------|
/// Menu.
///----------------------------------------------------------------------- Menu:
struct  Menu : protected ResurcesHolder
{       Menu() :    keys ({ (int)('1'),
                            (int)('2'),
                            (int)('3'),
                            (int)('4'),
                             27
                    }),
                    arbiter(scr)
        {
            scr.write({cfg->W - (unsigned)cfg->version.size(), 0},
                                 std::wstring(cfg->version ));

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

                        if(what == '?') break;

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
                    {
                        char what = arbiter.start_game_two_play();
                        if(what == 'z')
                        {
                           show_banner_center_pause(
                                (Bunner*)res->get(Resurces::E_GAME_OVER));
                        }

                        Toplist* tp = (Toplist*)res->get(Resurces::E_TOPLIST);
                                 tp->save();
                        break;
                    }

                    case '3':///////////////////////////////////////////////////
                    {
                        show_banner_center_clear_pause(
                            (Toplist*)res->get(Resurces::E_TOPLIST));
                        break;
                    }

                    case '4':///////////////////////////////////////////////////
                    {
                        show_scenario(
                            (Scenaries*)res->get(Resurces::E_SCENARIO));
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

    void show_scenario(Scenaries* sc)
    {   scr.clear                (  );
        show_banner_center       (sc);
        sc->select               (  );

      //scr.reload               (  );
    }
};

#endif // MENU_H
