#ifndef TOPLIST_H
#define TOPLIST_H

#include "../config.h"
#include "../myl.h"
#include "resurces.h"

#include <fstream>
#include <algorithm>
#include <sstream>
#include <list>

///----------------------------------------------------------------------------|
/// Toplist.
///-------------------------------------------------------------------- Toplist:
struct Record
{   std::string name;
    int  amount_game = 0;
    int  counted     = 0;

    bool add(int cnt)
    {   amount_game++;
        if(cnt > counted) { counted = cnt; return true; }
        return false;
    }
};

struct  Load_file
{       Load_file()
        {   std::ifstream f(file_name);

            if(f.is_open())
            {
                for(std::string s ; std::getline(f, s);)
                {   decoder    (s);
                    m     .push_back({s, 0, 0});
                    m_sort.push_back(&m.back());
                }

                parse();
            }
            build_form();
        }

    const char* file_name = "top.txt";

    void save()
    {   std::ofstream f(file_name);
        for(const auto& r : m_sort)
        {
            std::string s{r->name};                          s.push_back(' ');
                        s += std::to_string(r->amount_game); s.push_back(' ');
                        s += std::to_string(r->counted    );
            coder      (s);
            f <<        s << '\n';
        }
    }

protected:
    std::list  <Record     > m;
    std::vector<Record*    > m_sort;
    std::vector<std::string> m_show;

    void parse()
    {   for(auto&[name, am, cnt] :   m)
        {   std::istringstream  a(name) ;
            std::string      s; a >> s  ;
                                a >> am ;
                                a >> cnt;
                                name = s;
        }
    }

    void formated()
    {   m_show.clear();
        for(unsigned n = 0, i = 0; n < 12 && i < m_sort.size(); ++n, ++i)
        {   m_show.push_back(m_sort[i]->name);
        }

        unsigned msz  = 0;
        for(const auto& s : m_show)
        {   if(msz    < s.size())
               msz    = s.size();
        }

        msz++;

        auto a = msz + 5;
        auto b = a   + 6;

        int  I = 0;

        for(unsigned i = 0; i < m_sort.size(); ++i)
        {   m_show  [i].resize(msz, ' ');
            m_show  [i] += std::to_string(m_sort[i]->amount_game);
            m_show  [i].resize(a, ' ');

            m_show  [i] += std::to_string(m_sort[i]->counted);
            m_show  [i].resize(b, ' ');

            std::string t = std::to_string(++I);
                        t.resize(3, ' ');

            m_show  [i] = std::string("| ")
                        + t
                        + m_show  [i] + " |";
        }

        std::string E(m_show.front().size(), '-');

        m_show.insert   (m_show.begin(), E);
        m_show.push_back(                E);
    }

    void coder(std::string& s)
    {   for(auto& c : s) c++;
    }

    void decoder(std::string& s)
    {   for(auto& c : s) c--;
    }

    void    build_form()
    {   if(!m_sort.empty())
        {   std::sort(m_sort.begin(), m_sort.end(),
                [](Record* a, Record* b){ return a->counted > b->counted; });

            formated();
        }
        else
        {   m_show = std::initializer_list<std::string>{
                "-----------------------",
                "|   Toplist is EMPTY   |",
                "------------------------"
            };
        }
    }

    friend void testclass_Load_file();
};

///-----------------------------|
/// testclass_Load_file         |
///-----------------------------:
inline void testclass_Load_file()
{
    Load_file lf;

    for(const auto   r : lf.m_sort)
    {   std::cout << r->name        << ' '
                  << r->amount_game << ' '
                  << r->counted     << '\n';
    }

    lf.save     ();
    std::cin.get();
}

///----------------------------------------------------------------------------|
/// Toplist.
///-------------------------------------------------------------------- Toplist:
struct  Toplist   : public myl::Mat2D, protected Load_file, public ResClass
{       Toplist() : Mat2D(0, 0, ' ')
        {   to_mat();
        }

    Vec2u pos{0, 0};

    void add(std::string name, int cnt)
    {   Record* r = finder(name);
                r->add    (cnt );
        build_form();
        to_mat    ();
    }

    void save() { Load_file::save(); }

private:
    Record* finder(std::string name)
    {   for(auto& r : m_sort)
        {   if(r->name == name) return r;
        }
        m     .push_back({name, 0, 0});
        m_sort.push_back(&m.back(   ));
        return &m  .back();
    }

    friend void testclass_Toplist();

    void to_mat()
    {
        mat.clear();
        for(const auto& s : m_show)
        {
            std::wstring  w(s.begin(), s.end());
            mat.push_back(w);
        }

        height = mat.        size();
        width  = mat.front().size();
    }
};

///-----------------------------|
/// testclass_Toplist           |
///-----------------------------:
inline void testclass_Toplist()
{
    Toplist tl;
            tl.add("ZZZyxx9", 1201);
            tl.add("VVVa"   ,  877);

    for(const auto   r : tl.m_sort)
    {   std::cout << r->name        << ' '
                  << r->amount_game << ' '
                  << r->counted     << '\n';
    }

    std::cout << '\n';

    for(const auto&  s : tl.m_show)
    {   std::cout << s << '\n';
    }

    std::cout << '\n';

    for(const auto&   s : tl.get_mat())
    {   std::wcout << s << '\n';
    }

    tl.save     ();
    std::cin.get();
}

#endif // TOPLIST_H
