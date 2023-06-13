﻿#ifndef TEST_H
#define TEST_H

#include "vscr.h"
///----------------------------------------------------------------------------|
/// Баннер.
///----------------------------------------------------------------------------:
struct  Bunner : public myl::Mat2D
{       Bunner(std::initializer_list<std::wstring> data) : myl::Mat2D(data)
        {
        }
};

///--------------------------|
/// testclass_Bunner.        |<<<----------------------------------------------|
///--------------------------:
inline void testclass_Bunner()
{   VScreen scr;

    Bunner bann1(
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

        scr.write({1, 1}, figure());

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

    Korzina korzina(cfg.WK, cfg.HK);

    Vec2u position{Korzina::get_pos_center({cfg.WK, cfg.HK})};

    scr.write(position, korzina);

    Figure  figure;
            figure.gen(0);

    scr.write_alfa({1, 1}, figure());

            figure.pos = {10, 13};

    korzina << figure;

    scr.write(position, korzina);

    Hard    hard;
            hard << scr;
}

inline void tests()
{
  //testclass_Bunner          ();
  //testclass_LoaderFigures   ();
  //testclass_Figure          ();
  //console::testclass_IDevice();
    testclass_Korzina         ();
}

#endif // TEST_H
