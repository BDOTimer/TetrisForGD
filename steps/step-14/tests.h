#ifndef TEST_H
#define TEST_H

#include "vscr.h"
///----------------------------------------------------------------------------|
/// Баннер.
///----------------------------------------------------------------------------:
struct  Bunner2 : public myl::Mat2D
{       Bunner2(std::initializer_list<std::wstring> data) : myl::Mat2D(data)
        {
        }
};

///--------------------------|
/// testclass_Bunner.        |<<<----------------------------------------------|
///--------------------------:
inline void testclass_Bunner()
{   VScreen scr;

    Bunner2 bann1(
    {   L"123",
        L"456",
        L"789"
    });

    myl::Mat2D bann2(
    {   L"|-------------------|",
        L"|                   |",
        L"|      ЯTeTRis      |",
        L"|    (xlat-code)    |",
        L"|       2023©       |",
        L"|                   |",
        L"|-------------------|"
    });

    scr.write({1, 1},                    bann1);
    scr.write(scr.get_pos_center(bann2), bann2);

    Hard    hard;
            hard << scr;
}

#include "figure.h"
///--------------------------|
/// testclass_LoaderFigures. |<<<----------------------------------------------|
///--------------------------:
inline void testclass_LoaderFigures()
{   VScreen        scr     ;
    LoaderFigures  lfigures;

    lfigures.test();
}

///--------------------------|
/// testclass_Figure.        |<<<----------------------------------------------|
///--------------------------:
inline void testclass_Figure()
{   VScreen scr   ;
    Figure  figure;
    Hard    hard  ;

    for(unsigned i = 0; i < figure.get_amount(); ++i)
    {
        figure.gen(int(i));

        scr.write({1, 1}, figure.get_mat());

        hard << scr;

        DEVICE.pause_press_enter(L"PRESS ENTER\n");
    }
}

#include "korzina.h"
///--------------------------|
/// testclass_Korzina.       |<<<----------------------------------------------|===
///--------------------------:
inline void testclass_Korzina()
{
    VScreen scr;

    Korzina korzina(cfg->WK, cfg->HK);

    Vec2u position{Korzina::get_pos_center({cfg->WK, cfg->HK})};

    scr.write(position, korzina);

    Figure  figure;
            figure.gen(0);

    scr.write_alfa({1, 1}, figure.get_mat());

            figure.pos = {10, 13};

    korzina << figure;

    scr.write(position, korzina);

    Hard    hard;
            hard << scr;
}

#include "game.h"
///--------------------------|
/// testclass_Game.          |<<<----------------------------------------------|===
///--------------------------:
inline void testclass_Game()
{
    VScreen scr;

    Game    game     (scr, L"Vasia");
            game.init(             );
            game.run (             );
}

#include "infopanel.h"
///--------------------------|
/// testclass_Infopanel.     |<<<----------------------------------------------|===
///--------------------------:
inline void testclass_Infopanel()
{
    VScreen scr;

    Infopanel  ipanel;

    int& cnt = ipanel.push(L"cnt :");
    int& num = ipanel.push(L"num :");

         num = 2023;

    Hard hard;

    while(true)
    {
        cnt++;
        num -= 3;

        DEVICE.set_cursor_to_start();

        ipanel.update();

                scr.write({1, 1}, ipanel);
        hard << scr;

        myl::sleep(500);
    }
}

#include "control\program.h"
///--------------------------|
/// testclass_Program.       |<<<----------------------------------------------|
///--------------------------:
inline void testclass_Program()
{
    Program run;
}

#include "control\toplist.h"
///--------------------------|
/// testclass_Toplist2.      |<<<----------------------------------------------|
///--------------------------:
inline void testclass_Toplist2()
{
    ResClass* rt = new Toplist;
    VScreen   scr ;
              scr .write({0, 0}, *((Toplist*)rt));

    Hard      hard;
              hard << scr;

    Toplist&  tl = *((Toplist*)rt);
              tl.add("Vasia",  24);

              scr .write({0, 0}, tl);

              hard << scr;

              tl.save();
}

#include "control\scenaries.h"
///--------------------------|
/// testclass_xxx.           |<<<----------------------------------------------|
///--------------------------:
inline void testclass_Scenaries_F()
{
  //testclass_LoadScenaries_f();
    testclass_Scenaries_f    ();
}

inline void testclass_Scenaries()
{
    VScreen scr;
    Hard   hard;

    Scenaries sc;
    scr.write({0, 0}, sc);

    hard << scr;

    sc.set_sc('1');

    l(cfg->name  )
    l(cfg->figkit)
}

inline void tests()
{
  //testclass_Bunner          ();
  //testclass_LoaderFigures   ();
  //testclass_Figure          ();
  //console::testclass_IDevice();
  //testclass_Korzina         ();
  //testclass_Game            ();
  //testclass_Infopanel       ();

  ///---------------------------|
  testclass_Program         ();
  ///---------------------------|

  //myl::testclass_TimerGame  ();
  //testclass_Load_file       ();
  //testclass_Toplist         ();
  //testclass_Toplist2        ();
  //testclass_Scenaries_F     ();

  //testclass_Scenaries       ();
}

#endif // TEST_H
