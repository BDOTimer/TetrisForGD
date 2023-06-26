#ifndef SCENARIES_H
#define SCENARIES_H

#include "../config.h"
#include "../myl.h"
#include "../keyboard.h"
#include "resurces.h"

#include <fstream>
#include <algorithm>
#include <sstream>
#include <list>


///----------------------------------------------------------------------------|
/// LoadScenaries.
///-------------------------------------------------------------- LoadScenaries:
struct  LoadScenaries
{       LoadScenaries()
        {   std::ifstream f(filename);
            std::getline (f, s, '\f');

            myl::split<std::string_view>(s, m, " \n\"=;");

            for(size_t i  = 0; i < m.size(); ++i)
            {     if(m[i] == "SCENARIO") pos_start.push_back(i);
            }

            for(size_t i  = 0; i < m.size(); ++i)
            {     if(m[i] == "{") pos_a.push_back(i);
            }

            for(size_t i  = 0; i < m.size(); ++i)
            {     if(m[i] == "}") pos_b.push_back(i);
            }

            check_stupid(pos_start, pos_a, pos_b);
        }

    std::vector<size_t> pos_start;
    std::vector<size_t> pos_a    ;
    std::vector<size_t> pos_b    ;

    std::string_view find(std::string_view f, unsigned n)
    {
        for(unsigned i = pos_a[n]; i < pos_b[n]; ++i)
        {
            if( f ==   m[i    ])
            {   return m[i + 1];
            }
        }

        return "";
    }

private:
    const char* filename = "scenaries.txt";

    std::string                   s;
    std::vector<std::string_view> m;

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

    const char* error_mess = "File \"Scenaries.txt\" fail!";
    friend void testclass_LoadScenaries_f();
    friend void testclass_Scenaries_f    ();
    friend struct Scenaries;
};

#include <iostream>
///-----------------------------|
/// testclass_LoadScenaries     |
///-----------------------------:
inline void testclass_LoadScenaries_f()
{
    LoadScenaries ld;

    for(const auto&  s : ld.m )
    {   std::cout << s << '\n';
    }   std::cout      << '\n';
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

            for(size_t i = 0; i < cfgs.size();   ++i)
            {   cfgs[i].name = m[pos_start[i] + 1];
            }

            build_form();

            for(unsigned i = 0; i < cfgs.size(); ++i)
            {   keys.keys.push_back(i + '1');
            }   keys.keys.push_back(     13);
        }

    void select()
    {   do
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

        //l(n)

        auto& cf = cfgs[n];

        if(buid_cfg(cf, n))
        {    cfg = &cf;
        }
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

                std::wstring name; name << cfgs[i].name;

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
        cf.figkit = find("Figkit", n);

        std::ifstream f(cf.figkit);

        return f.is_open();
    }

    friend void testclass_Scenaries_f();
};

///-----------------------------|
/// testclass_Scenaries         |
///-----------------------------:
inline void testclass_Scenaries_f()
{
    Scenaries sc;
              sc.build_form();

    for(const auto&   s : sc.get_mat())
    {   std::wcout << s << '\n';
    }   std::wcout      << '\n';
}

#endif // SCENARIES_H
