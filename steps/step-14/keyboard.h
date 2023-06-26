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

///----------------------------------------------------------------------------|
/// KeysProfile.
///---------------------------------------------------------------- KeysProfile:
struct  KeysProfile
{       KeysProfile(std::initializer_list<int> keys) : keys(keys)
        {
        }
        KeysProfile(std::wstring Keys)
        {
            for(const auto c : Keys)
            {   keys.push_back((int)c);
            }
            keys.push_back(27);
            keys.push_back(13);
            keys.push_back( 8);
        }
        KeysProfile(){}

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
        //test();

        myl::sleep(20);

        if (_kbhit())
        {   int key = _getch();

            //if(key >  90) key -= 32;

            auto p  = std::find(keys.begin(), keys.end(), key);

            if(  p != keys.end()) return key;
        }
        return 0;
    }

private:
    bool exit = false;
};

///----------------------------------------------------------------------------|
/// InputString.
///---------------------------------------------------------------- InputString:
struct  InputString   : private KeysProfile
{       InputString() :
            KeysProfile(
                L"ЯЧЫЙЦУqwertyuiopasdfghjklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM")
        {
            std::sort(KeysProfile::keys.begin(), KeysProfile::keys.end());
        }

        std::wstring get(std::wstring_view promt)
        {
            std::string s;

            DEVICE << promt << "> _";

            for(bool done = true; done; )
            {
                if (_kbhit())
                {   int key = _getch();

                    switch(key)
                    {
                        case  8: if(!s.empty()) s.pop_back(); break;
                        case 13: done = false;                break;
                        case 27: done = false;  s = "?";      break;
                        default:
                            if(std::binary_search(
                                    keys.begin(), keys.end(), (char)key ))
                            {
                                if(s.size() < 20) s.push_back((char)key);
                            }
                    }

                    std::string                t{"> "};
                                               t += s;
                                               t.resize(23, ' ');
                    DEVICE << "\r" << promt << t;
                }
            }

            std::string  t(39 , ' ');
                         t[0] = '\r';
            DEVICE    << t;

            std::wstring w{s.begin(), s.end()};

            return w;
        }

};

#endif // KEYBOARD_H
