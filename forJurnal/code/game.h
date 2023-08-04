#ifndef GAME_H
#define GAME_H

#include "korzina.h"
#include "keyboard.h"
#include "infopanel.h"

#include <functional>

///----------------------------------------------------------------------------|
/// Game.
///----------------------------------------------------------------------- Game:
struct  Game
{       Game(VScreen&            _scr,
             std::wstring_view     nm,
             IKeysProfileAction*    k,
             unsigned            disp,
             unsigned        poskor_x)

            :
                displace_x(disp),
                timer1    ( 0.7),
                vscr      (_scr),
                scr       (_scr , disp),
                korzina   (cfg->WK, cfg->HK),
                keys      (k)
        {
            name +=  nm  ;
            name += L" >";

            korzina.pos.x = poskor_x;
        }

    unsigned   displace_x;
    Vec2u        POSSTART;
    myl::TimerGame timer1;
    bool done      = true;

    void init()
    {
        infocnt.pos  = {0, 1};
                pcnt = &infocnt.push(L"Cчёт ");
                pnum = &infocnt.push(L"Фигур");

        ///---------------------------------|
        /// ...                             |
        ///---------------------------------:
        POSSTART = korzina.get_pos_figure_start();

           *pcnt = 0;
           *pnum = 0;

        figure.pos =  POSSTART  ;
        figure.gen_probab_rand();
    }

    void run        (){         loop(); }///////////////////////////////////////
    int  get_counted(){ return *pcnt  ; }

    void add_to_name()
    {   name += L"::";
        name += cfg->name;
    }



private:
    Hard                hard;
    VScreen&            vscr;
    VScreenWrap          scr;
    Figure            figure;
    Korzina          korzina;
    IKeysProfileAction* keys;
    Infopanel        infocnt;
    std::wstring name{L"< "};

    int* pcnt = nullptr;
    int* pnum = nullptr;

    void loop()
    {
        while(done)
        {
            DEVICE.set_cursor_to_start();
            vscr.clear    ();
            keys->act.scan();
            loop_tick     (); //////////////////////////////////////////////////

            hard << vscr;
        }
    }

public:
    void loop_tick()
    {
        int& cnt = *pcnt;
        int& num = *pnum;

        ///---------------|
        /// for(; done; ) |
        ///---------------:
        {

            scr.write(korzina.pos, korzina);

            ///--------------------------------|
            /// Упала ли?.                     |
            ///--------------------------------:
            if(is_collision_Down(figure.pos))
            {
               korzina << figure;

               scr.write(korzina.pos, korzina);

               figure.pos =  POSSTART  ;
               figure.gen_probab_rand();

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
            if(const int key = keys->get(); key != NOKEY)
            {
                switch(key)
                {
                    case AB::E_LEFT : left (); break;
                    case AB::E_RIGHT: right(); break;
                    case AB::E_UP   : rot_p(); break;
                    case AB::E_DOWN : drop (); break;
                }
            }

                    scr.write     (     {0, 0}, name   );
                    scr.write_alfa(figure .pos, figure );
                    scr.write     (infocnt.pos, infocnt.update());
        }
    }

private:
    bool is_collision_Down(Vec2u p)
    {   p.y ++;
        return is_collision(p);
    }

    bool is_collision(Vec2u p)
    {
        p.x += displace_x;

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
