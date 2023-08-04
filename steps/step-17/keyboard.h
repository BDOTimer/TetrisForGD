#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <conio.h>
#include "config.h"
#include <algorithm>

///----------------------------------------------------------------------------|
/// Управление.
///----------------------------------------------------------------------------:

struct A
{   enum KEYS
    {   E_LEFT  = 75,
        E_RIGHT = 77,
        E_UP    = 72,
        E_DOWN  = 80
    };
};

struct B
{   enum KEYS
    {   E_LEFT  = 'a',
        E_RIGHT = 'd',
        E_UP    = 'w',
        E_DOWN  = 's'
    };
};

struct AB
{   enum KEYS
    {   E_LEFT = 0,
        E_RIGHT,
        E_UP   ,
        E_DOWN
    };
};

#include <iostream>
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
    {   for (int k; (k = _getwch()) != 27;) /// _kbhit  () != 27
        {   DEVICE << (wchar_t)k;
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

        myl::sleep(10);

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
                L"ячсмитьбюЯЧСМИТЬБЮqwertyuiopasdfghjklzxcvbnm ")
        {
            std::sort(KeysProfile::keys.begin(), KeysProfile::keys.end());
        }

    std::wstring get(std::wstring_view promt)
    {
        std::wstring w;

        DEVICE << promt << "> _";

        for(bool done = true; done; )
        {
            if (_kbhit())
            {   int key = _getwch();

                switch(key)
                {
                    case  8: if(!w.empty()) w.pop_back(); break;
                    case 13: done = false;                break;
                    case 27: done = false;  w = L"?";     break;
                    default:
                        //if(std::binary_search(
                        //    keys.begin(), keys.end(), (wchar_t)key))
                        {
                                if(w.size() < 20) w.push_back((wchar_t)key);
                        }
                }

                std::wstring               t{L"> "};
                                           t += w;
                                           t.resize(23, L' ');
                DEVICE << "\r" << promt << t;
            }
        }

        std::wstring t(39 , L' ');
                     t[0] = L'\r';
                     t.push_back(L'\r');
        DEVICE    << t;

        return w;
    }

    std::wstring getw(std::wstring_view promt)
    {
        std::wstring w;

        DEVICE << promt << "> _";
        DEVICE >> w;
        return    w;
    }

};

///----------------------------------------------------------------------------|
/// KeysProfile2.
///--------------------------------------------------------------- KeysProfile2:
const int NOKEY = 999;
struct  KeysProfile2
{       KeysProfile2(std::initializer_list<int> pl1,
                     std::initializer_list<int> pl2) : keys1(pl1), keys2(pl2)
        {
            for(unsigned i = 0; i < keys1.size(); ++i) m[keys1[i]] = i;
            for(unsigned i = 0; i < keys2.size(); ++i) m[keys2[i]] = i;
            m[0] = NOKEY;
        }

    int a = 0;
    int b = 0;

    int get_a(){ auto r = a; a = 0; return m[r]; }
    int get_b(){ auto r = b; b = 0; return m[r]; }

    void scan()
    {
        if(_kbhit())
        {   int key = _getch();

            auto p1  = std::find(keys1.begin(), keys1.end(), key);
            auto p2  = std::find(keys2.begin(), keys2.end(), key);

            a = (p1 != keys1.end()) ? key : 0;
            b = (p2 != keys2.end()) ? key : 0;
        }
    }

private:
    std::vector<int> keys1;
    std::vector<int> keys2;

    int m[256];
};

///----------------------------------------------------------------------------|
/// KeysProfileData.
///------------------------------------------------------------ KeysProfileData:
struct  KeysProfileData   : public KeysProfile2
{       KeysProfileData() : KeysProfile2(
                            {   A::E_LEFT ,
                                A::E_RIGHT,
                                A::E_UP   ,
                                A::E_DOWN
                            },
                            {   B::E_LEFT ,
                                B::E_RIGHT,
                                B::E_UP   ,
                                B::E_DOWN
                            })
        {
        }
};

struct      IKeysProfileAction
{           IKeysProfileAction(KeysProfileData& a) : act(a)
            {
            }
    virtual~IKeysProfileAction() {}

    virtual int get() = 0;

    KeysProfileData& act;
};

struct  KeysProfileActionA : public IKeysProfileAction
{       KeysProfileActionA(KeysProfileData& a) : IKeysProfileAction(a)
        {
        }

    int get()
    {   return act.get_a();
    }
};

struct  KeysProfileActionB : public IKeysProfileAction
{       KeysProfileActionB(KeysProfileData& a) : IKeysProfileAction(a)
        {
        }

    int get()
    {   return act.get_b();
    }
};

#endif // KEYBOARD_H
