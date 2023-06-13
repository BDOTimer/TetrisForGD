#ifndef GAME_H
#define GAME_H

#include "korzina.h"

struct  Game
{       Game(VScreen& _scr) : scr(_scr), korzina(cfg.WK, cfg.HK)
        {
            loop();
        }

private:
    Hard       hard;
    VScreen&    scr;
    Figure   figure;
    Korzina korzina;

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

            scr.write_alfa(figure .pos, figure );
            hard << scr;

            myl::sleep(400);
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
                if(const auto& a = mat[r][c]; m[j][i] != ' ' && !(a == ' '
                                                             ||   a == '.'))
                {   return true;
                }
            }
        }
        return false;
    }
};

#endif // GAME_H
