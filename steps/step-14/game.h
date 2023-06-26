#ifndef GAME_H
#define GAME_H

#include "korzina.h"
#include "keyboard.h"
#include "infopanel.h"

///----------------------------------------------------------------------------|
/// Game.
///----------------------------------------------------------------------- Game:
struct  Game
{       Game(VScreen& _scr, std::wstring_view nm)
            :   scr  (_scr),
                korzina(cfg->WK, cfg->HK),
                keys ({ Ea_LEFT ,
                        Ea_RIGHT,
                        Ea_UP   ,
                        Ea_DOWN
                })

        {   name +=  nm  ;
            name += L" >";
        }

    void init()
    {
        infocnt.pos  = {0, 1};
                pcnt = &infocnt.push(L"cnt");
                pnum = &infocnt.push(L"num");
    }

    void run        (){         loop(); }
    int  get_counted(){ return *pcnt  ; }

    void add_to_name()
    {   std::wstring mm; mm << cfg->figkit;
        name += L"::";
        name += mm   ;
    }

private:
    Hard         hard;
    VScreen&      scr;
    Figure     figure;
    Korzina   korzina;
    KeysProfile  keys;
    Infopanel infocnt;
    std::wstring name{L"< "};

    int* pcnt = nullptr;
    int* pnum = nullptr;

    void loop()
    {
        const Vec2u POSSTART = korzina.get_pos_figure_start();

        int& cnt = *pcnt;
        int& num = *pnum;

             cnt = 0;
             num = 0;

        figure.pos = POSSTART;
        figure.gen();

        myl::TimerGame timer1( 0.5);

        for(bool done = true; done; )
        {
            DEVICE.set_cursor_to_start();

            scr.clear();
            scr.write(korzina.pos, korzina);

            ///--------------------------------|
            /// Упала ли?.                     |
            ///--------------------------------:
            if(is_collision_Down(figure.pos))
            {
               korzina << figure;

               scr.write(korzina.pos, korzina);

               figure.pos = POSSTART;
               figure.gen();

               if(is_collision(figure.pos))
               {    done = false;
               }
               else num++;

             //timer1.set_period(0.5);
            }
            else
            {   if(timer1.is_ready())
                {
                    figure.pos.y++;

                    cnt += korzina.check_lines_02();
                }
            }

            ///--------------------------------|
            /// Клавиатура.                    |
            ///--------------------------------:
            if(const int key = keys.scan(); key)
            {
                switch(key)
                {
                    case KEYS_a::Ea_LEFT : left (); break;
                    case KEYS_a::Ea_RIGHT: right(); break;
                    case KEYS_a::Ea_UP   : rot_p(); break;
                    case KEYS_a::Ea_DOWN : drop (); break;
                }
            }

                    scr.write     (     {0, 0}, name   );
                    scr.write_alfa(figure .pos, figure );
                    scr.write     (infocnt.pos, infocnt.update());
            hard << scr;
        }
    }

    bool is_collision_Down(Vec2u p)
    {   p.y ++;
        return is_collision(p);
    }

    bool is_collision(const Vec2u& p)
    {
        const auto&    mat = scr   .get_mat();
        const auto&    m   = figure.get_mat().get_mat();
        const unsigned W   = figure.get_mat().NW();
        const unsigned H   = figure.get_mat().NH();


        for    (unsigned r = p.y, j = 0; j < H && r < scr.NH(); ++r, ++j)
        {   for(unsigned c = p.x, i = 0; i < W && c < scr.NW() ; ++c, ++i)
            {
                if(const auto& a = mat[r][c]; m[j][i] != ' ' &&
                                                  !(a == ' ' || a == '.'))
                {   return true;
                }
            }
        }
        return false;
    }

    void left()
    {   Vec2u p = figure.pos; --p.x;
        if(!is_collision(p)) {--figure.pos.x; }
    }

    void right()
    {   Vec2u p = figure.pos; ++p.x;
        if(!is_collision(p)) {++figure.pos.x; }
    }

    void rot_p()
    {   figure.get_mat().rot_p();
        if(is_collision(figure.pos)) figure.get_mat().rot_n();
    }

    void drop ()
    {   Vec2u     p{figure.pos.x, figure.pos.y + 1};
        for( bool b = true; (b = !is_collision(p)); ++p.y, ++figure.pos.y);
    }
};

#endif // GAME_H
