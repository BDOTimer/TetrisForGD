#ifndef TOPLIST_H
#define TOPLIST_H

#include "../config.h"
#include "../myl.h"
#include "tp.h"
#include "resurces.h"

#include <fstream>
#include <algorithm>
#include <sstream>
#include <list>

///----------------------------------------------------------------------------|
/// Toplist.
///-------------------------------------------------------------------- Toplist:
struct  Toplist   : public myl::Mat2D, public ResClass
{       Toplist()
        {   from_file();
        }

    Vec2u pos{0, 0};

    void add(std::wstring name, int cnt)
    {
        Record* r = finder(name);
                r->add    (cnt );

        cargo.formated();
        to_mat        ();
    }

    void save()
    {   Serial  ss;
                ss << cargo ;
                ss.to_file();
    }

private:
    Cargo cargo;

    Record* finder(std::wstring name)
    {
        for(auto& r : cargo.get())
        {   if(r->name == name) return r;
        }
               cargo.add({name, 0, 0});
        return cargo.get().back();
    }

    void to_mat  ()
    {   mat.clear();
        for(const auto&   s : cargo.get_strs())
        {   mat.push_back(s);
        }
    }

    void from_file()
    {   Serial  ff;
                ff.from_file();
                ff >> cargo;

        cargo.formated();
        to_mat        ();
    }

    friend void testclass_Toplist();
};

///-----------------------------|
/// testclass_Toplist           |
///-----------------------------:
inline void testclass_Toplist()
{
    Toplist tl;
            tl.add(L"ZZZyxx9", 1201);
            tl.add(L"VVVa"   ,  877);

    for(const auto    r : tl.cargo.get())
    {   std::wcout << r->name         << ' '
                   << r->amount_game  << ' '
                   << r->counted      << '\n';
    }

    std::cout << '\n';

    for(const auto&   s : tl.cargo.get_strs())
    {   std::wcout << s << '\n';
    }

    std::cout << '\n';

    for(const auto&   s : tl.get_mat())
    {   std::wcout << s << '\n';
    }

    tl.save     ();
    std::cin.get();
}

#endif // TOPLIST_H
