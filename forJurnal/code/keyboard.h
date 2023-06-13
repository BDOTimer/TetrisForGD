#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <conio.h>
#include "config.h"
#include <algorithm>

///----------------------------------------------------------------------------|
/// Управление.
///----------------------------------------------------------------------------:
enum KEYS_a
{
    Ea_LEFT  = 75,
    Ea_RIGHT = 77,
    Ea_UP    = 72,
    Ea_DOWN  = 80
};

/*
enum KEYS_b
{
    Eb_LEFT  = 65,
    Eb_RIGHT = 68,
    Eb_UP    = 87,
    Eb_DOWN  = 83
}
*/

struct  KeysProfile
{       KeysProfile(std::initializer_list<int> keys) : keys(keys)
        {
        }

    std::vector<int> keys;

    static void test()
    {   while (_kbhit  () != 27)
        {   int k = _getch();
            //std::cout << k << '\n';
            DEVICE << std::to_wstring(k);
        }
    }

    bool is_exit()
    {   bool   a = exit;
                   exit = false;
        return a;
    }

    int scan()
    {
        for(int i  = 0; i < 20; ++i)
        {
            myl::sleep(20);

            if (_kbhit())
            {   int key = _getch();

                if(key >  90) key -= 32;

                auto p = std::find(keys.begin(), keys.end(), key);

                if(p != keys.end()) return *p;
            }
        }
        return 0;
    }

private:
    bool exit = false;
};

#endif // KEYBOARD_H
