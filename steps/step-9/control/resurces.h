#ifndef RESURCES_H
#define RESURCES_H

#include "../config.h"
#include "../myl.h"
#include <iostream>


///----------------------------------------------------------------------------|
/// ResClass.
///----------------------------------------------------------------------------:
struct       ResClass
{   virtual ~ResClass(){}
};

///----------------------------------------------------------------------------|
/// ������.
///----------------------------------------------------------------------------:
struct  Bunner : public myl::Mat2D, public ResClass
{       Bunner(std::initializer_list<std::wstring> data) : myl::Mat2D(data)
        {
        }
};

struct  Resurces
{       Resurces  ()
        {   create();

            //test();
        }
       ~Resurces  (){ for(auto p : m) delete p; }

    enum eTYPE
    {   E_LOGO,          /// Bunner
        E_GAME_OVER,     /// Bunner
        E_PROG_FINISHED, /// Bunner

        /// ...
        E_SIZE
    };

    const ResClass* get(eTYPE type) const
    {   return m[type];
    }


private:
    std::vector<ResClass*> m;

    void create();

    void test()
    {
    }
};

struct  ResurcesHolder
{
    static std::unique_ptr<Resurces> res;

    static void create()
    {   res = std::make_unique<Resurces>();
    }
    static void del()
    {   res = nullptr;
    }
};

#endif // RESURCES_H
