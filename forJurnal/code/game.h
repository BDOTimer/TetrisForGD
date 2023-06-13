#ifndef GAME_H
#define GAME_H

#include "korzina.h"
#include "keyboard.h"

struct  Game
{       Game(VScreen& _scr)
            :   scr  (_scr), korzina(cfg.WK, cfg.HK),
                keys ({75, 77, 72, 80})
        {
            loop();
        }

private:
    Hard        hard;
    VScreen&     scr;
    Figure    figure;
    Korzina  korzina;
    KeysProfile keys;

    int counted = 0;

    void loop()
    {
        const Vec2u POSSTART = korzina.get_pos_figure_start();

        figure.pos = POSSTART;
        figure.gen(0);

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

               if(is_collision(figure.pos))
               {    done = false;
               }
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

            counted += korzina.check_lines_02();

            scr.write_alfa(figure.pos, figure );
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
    {   Vec2u p = figure.pos;--p.x;
        if(!is_collision(p)) --figure.pos.x;
    }

    void right()
    {   Vec2u p = figure.pos;++p.x;
        if(!is_collision(p)) ++figure.pos.x;
    }

    void rot_p()
    {   figure.get_mat().rot_p();
        if(is_collision(figure.pos)) figure.get_mat().rot_n();
    }
};

#endif // GAME_H
