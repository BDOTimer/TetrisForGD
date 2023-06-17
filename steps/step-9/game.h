#ifndef GAME_H
#define GAME_H

#include "korzina.h"
#include "keyboard.h"
#include "infopanel.h"

struct  Game
{       Game(VScreen& _scr)
            :   scr  (_scr), korzina(cfg.WK, cfg.HK),
                keys ({75, 77, 72, 80})
        {
                    infocnt.pos = {0, 0};
            pcnt = &infocnt.push(L"cnt");
            pnum = &infocnt.push(L"num");

            loop();
        }

private:
    Hard         hard;
    VScreen&      scr;
    Figure     figure;
    Korzina   korzina;
    KeysProfile  keys;
    Infopanel infocnt;

    int* pcnt = nullptr;
    int* pnum = nullptr;

    int counted = 0;

    void loop()
    {
        const Vec2u POSSTART = korzina.get_pos_figure_start();

        int& cnt = *pcnt;
        int& num = *pnum;

             cnt = 0;
             num = 0;

        figure.pos = POSSTART;
        figure.gen();

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
            }
            else
            {   figure.pos.y++;
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
                }
            }

            cnt += korzina.check_lines_02();

                    scr.write_alfa(figure .pos, figure);
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
        const auto&     mat = scr   .get_mat();
        const auto&     m   = figure.get_mat().get_mat();
        const unsigned& W   = figure.get_mat().width    ;
        const unsigned& H   = figure.get_mat().height   ;


        for    (unsigned r = p.y, j = 0; j < H && r < scr.height; ++r, ++j)
        {   for(unsigned c = p.x, i = 0; i < W && c < scr.width ; ++c, ++i)
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
        if(!is_collision(p)) {--figure.pos.x; --figure.pos.y;}
    }

    void right()
    {   Vec2u p = figure.pos; ++p.x;
        if(!is_collision(p)) {++figure.pos.x; --figure.pos.y;}
    }

    void rot_p()
    {   figure.get_mat().rot_p();
        if(is_collision(figure.pos)) figure.get_mat().rot_n();
    }
};

#endif // GAME_H
