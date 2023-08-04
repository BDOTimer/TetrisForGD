#ifndef CONFIG_H
#define CONFIG_H

#include "myl.h"

///----------------------------------------------------------------------------|
/// Конфигурация программы.
///----------------------------------------------------------------------------:
struct Config
{
    std::wstring name   = L"Default"    ;
    std::wstring figkit = L"figures.txt";

    unsigned W  = 78   ; /// Ширина доски.
    unsigned H  = 22   ; /// Высота доски.

    unsigned WK = 13   ; /// Ширина корзины.
    unsigned HK = 13   ; /// Высота корзины.

    wchar_t  C  = '.'  ; /// Символ заполнения.

    std::wstring_view version{L"Step-17"};

    void load_from_file(){ /* ... */ }

    void debug()
    {      l(name)
           l(W )
           l(H )
           l(WK)
           l(HK)
    }
};

extern Config const* cfg;

///----------------------------------------------------------------------------|
/// Позиционер.
///----------------------------------------------------------------------------:
struct Positioner_X
{
    enum eMODEorID
    {    E_ONE = 0,
         E_TWO
    };

    struct Data
    {   unsigned disp    ;
        unsigned poskor_x;
    };

    void calc(eMODEorID MODE, const Config* cf)
    {
        switch(MODE)
        {
            case E_ONE:
            {   m.resize   (1);
                m[0].disp = 0 ;
                m[0].poskor_x = (cf->W - cf->WK) / 2 - 1;

                break;
            }
            case E_TWO:
            {   m.resize   (2);
                m[0].disp = 0 ;
                m[1].disp = cf->W / 2;

                m[0].poskor_x = (cf->W  / 2 - cf->WK) / 2 - 1;
                m[1].poskor_x = m[0].poskor_x;

                break;
            }
        }

        done = true;
    }

    const   Data& get(eMODEorID id_player)
    {   if( (size_t)id_player  >= m.size())
        {   throw(ERROR_EXCEPTION_MESS("don't exist data for this player!"));
        }
        if( !done )
        {   throw(ERROR_EXCEPTION_MESS("need call calc(...)!"));
        }

        return m[id_player];
    }

    ///--------------|
    /// Test.        |
    ///--------------:
    static void test()
    {   Config cf{L"Config TEST:", L"", 70, 5, 5, 5, '.', L"Step-17"};

        ///----------|
        /// E_ONE.   |
        ///----------:
        {
            Positioner_X positioner_X;
                         positioner_X.calc(Positioner_X::E_ONE, &cf);
            auto     d = positioner_X.get (Positioner_X::E_ONE);

            l(d.disp)

            std::wstring s(cf.W, '*');

            const unsigned A = d.poskor_x + d.disp;

            for(unsigned i = A, N = A + cf.WK; i < N; ++i) {s[i] = '-';}
            l(cf.W)
            l(cf.WK)
            l(s)
        }

        ///----------|
        /// E_TWO.   |
        ///----------:
        {
            Positioner_X positioner_X;
                         positioner_X.calc(Positioner_X::E_TWO, &cf);
            auto    d1 = positioner_X.get (Positioner_X::E_ONE);
            auto    d2 = positioner_X.get (Positioner_X::E_TWO);

            l(d1.disp)
            l(d2.disp)

            std::wstring s(cf.W, '*');

            const unsigned A = d1.poskor_x + d1.disp;
            const unsigned B = d2.poskor_x + d2.disp;

            for(unsigned i = A, N = A + cf.WK; i < N; ++i) {s[i] = '-';}
            for(unsigned i = B, N = B + cf.WK; i < N; ++i) {s[i] = '-';}

            l(cf.W)
            l(cf.WK)
            l(s)
        }
    }

private:
    std::vector<Data> m;
    bool done =   false;
};

#endif // CONFIG_H
