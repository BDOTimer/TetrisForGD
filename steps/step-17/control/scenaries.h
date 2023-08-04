#ifndef SCENARIES_H
#define SCENARIES_H

#include "../config.h"
#include "../myl.h"
#include "../keyboard.h"
#include "resurces.h"

//#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>


///----------------------------------------------------------------------------|
/// LoadScenaries.
///-------------------------------------------------------------- LoadScenaries:
struct  LoadScenaries
{       LoadScenaries()
        {
            {
                //auto PP = std::codecvt_utf8_utf16<wchar_t>();
                //std::wifstream f(filename );
                //               f.imbue(std::locale(f.getloc(), &PP));
                //std::getline  (f, s, L'\f');
            }
            {
                std::ifstream f(filename );
                if          (!f.is_open())
                {   throw(ERROR_EXCEPTION_MESS("!file.is_open()"));
                }

                std::string ss; std::getline  (f, ss, '\f');
                s = utf8_to_wstring(ss);
            }

            myl::split<std::wstring_view>(s, m, L" \n\"=;");

            for(size_t i  = 0; i < m.size(); ++i)
            {     if(m[i] == L"SCENARIO") pos_start.push_back(i);
            }

            for(size_t i  = 0; i < m.size(); ++i)
            {     if(m[i] == L"{") pos_a.push_back(i);
            }

            for(size_t i  = 0; i < m.size(); ++i)
            {     if(m[i] == L"}") pos_b.push_back(i);
            }

            check_stupid(pos_start, pos_a, pos_b);
        }

    std::vector<size_t> pos_start;
    std::vector<size_t> pos_a    ;
    std::vector<size_t> pos_b    ;

    std::wstring_view find(std::wstring_view f, unsigned n)
    {
        for(unsigned i = pos_a[n]; i < pos_b[n]; ++i)
        {
            if( f ==   m[i    ])
            {   return m[i + 1];
            }
        }
        return L"";
    }

    std::wstring_view geti(unsigned i, std::wstring_view nameval) const
    {
        for(size_t   j =  pos_a[i]; j < pos_b[i]; ++j)
        {   if(nameval ==     m[j])
            {   return    m[1 + j];
            }
        }
        return L"10";
    }

private:
    const wchar_t* filename = L"scenaries.txt";

    std::wstring                   s;
    std::vector<std::wstring_view> m;

    void check_stupid(const std::vector<size_t>& ps,
                      const std::vector<size_t>& pa,
                      const std::vector<size_t>& pb) const
    {
        if(ps.size() != pa.size() || ps.size() != pb.size())
        {   throw(ERROR_EXCEPTION_MESS(error_mess));
        }

        for(size_t i = 0, j = ps.size() - 1; i < j; ++i)
        {   if(ps[i] > ps[i + 1])
                throw(ERROR_EXCEPTION_MESS(error_mess));
        }

        for(size_t i = 0; i < ps.size(); ++i)
        {   if(ps[i] > pa[i] || pa[i] > pb[i])
                throw(ERROR_EXCEPTION_MESS(error_mess));
        }
    }

    const  char*  error_mess = "File \"Scenaries.txt\" fail!";

    friend void   testclass_LoadScenaries_f();
    friend void   testclass_Scenaries_f    ();
    friend struct Scenaries;
};

///-----------------------------|
/// testclass_LoadScenaries     |
///-----------------------------:
inline void testclass_LoadScenaries_f()
{
    TESTINFO;

    LoadScenaries ld;

    for(const auto&  s : ld.m )
    {   std::wcout << s << '\n';
    }   std::wcout      << '\n';
}

///----------------------------------------------------------------------------|
/// Scenaries.
///------------------------------------------------------------------ Scenaries:
struct  Scenaries   : public    myl::Mat2D   ,
                      protected LoadScenaries,
                      public    ResClass
{       Scenaries() : Mat2D(0, 0, ' ')
        {
            cfgs.resize(pos_start.size());

            for(size_t i = 0; i < cfgs.size(); ++i)
            {   cfgs[i].name = m[pos_start[i]  + 1];
            }

            build_form();

            for(unsigned i = 0; i < cfgs.size(); ++i)
            {   keys.keys.push_back(i + '1');
            }   keys.keys.push_back(     13);
        }

    void select()
    {
        do
        {   if(int      k =  -1; ( k = keys.scan() ) != 0)
            {        if(k == 13)              break;
                else if(k >   0) { set_sc(k); break; }
            }
        } while(true);
    }

    void set_sc(unsigned n)
    {
           n -= '1';
        if(n >= cfgs.size()) return;

        auto& cf =  cfgs[n];

        if(buid_cfg(cf,  n))
        {    cfg = &cfgs[n];
        }

//l(cfg->name)
//DEVICE.pause_press_enter(L"PRESS ENTER\n");
    }

private:
    std::vector<Config> cfgs;
    KeysProfile         keys;

    void build_form()
    {
        std::list<std::wstring> ss(cfgs.size(), L"| ");

        unsigned sz_max = cfgs[0].name.size();

        for(size_t  i = 1;   i < cfgs.size(); ++i)
        {   if(sz_max < cfgs[i]. name.size())
               sz_max = cfgs[i]. name.size();
        }

        auto beg = ss.begin();

        for(size_t i  = 0; i < cfgs.size (); ++i, ++beg)
        {
                *beg += std::to_wstring(i + 1);
                *beg += L". ";

                beg->resize(6, ' ');

                std::wstring name = cfgs[i].name;

                        name.resize(sz_max + 1, ' ');
                *beg += name;
                *beg += L"|";
        }

        std::wstring  E(ss.front().size(), L'-');
        ss.push_front(E);
        ss.push_back (E);

        for(const auto& s : ss)
        {   mat.push_back(s);
        }
    }

    bool buid_cfg(Config& cf, unsigned n)
    {
        cf.figkit = find(L"Figkit", n);

        std::wifstream f(cf.figkit.c_str());

//l(cf.figkit)
//l(f.is_open())
//DEVICE.pause_press_enter(L"PRESS ENTER\n");

        if(f.is_open())
        {
            //cf.W  = find_uint(n, L"WS");
            //cf.H  = find_uint(n, L"HS");

            cf.WK = find_uint(n, L"WK");
            cf.HK = find_uint(n, L"HK");

            //l(cf.W )
            //l(cf.H )
            //l(cf.WK)
            //l(cf.HK)
        }

        return f.is_open();
    }

    unsigned find_uint(unsigned i, std::wstring_view nameval) const
    {
        auto ss = geti(i, nameval);

        unsigned n;

        try
        {    std::wstring  w(ss);
             n = std::stoi(w.c_str());
        }
        catch(...)
        {    n = 10;
        }
        return n;
    }

    friend void testclass_Scenaries_f();
};

///-----------------------------|
/// testclass_Scenaries         |
///-----------------------------:
inline void testclass_Scenaries_f()
{
    TESTINFO;

    Scenaries sc;
              sc.build_form();

    for(const auto&   s : sc.get_mat())
    {   std::wcout << s << '\n';
    }   std::wcout      << '\n';
}

#endif // SCENARIES_H
