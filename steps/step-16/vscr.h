#ifndef VSCR_H
#define VSCR_H

#include "config.h"

///----------------------------------------------------------------------------|
/// Виртуальный экран.
///----------------------------------------------------------------------------:
struct  VScreen : public myl::Mat2D
{       VScreen() : Mat2D(cfg->W, cfg->H, cfg->C)
        {
        }

    ///--------------------------------------|
    /// Кукиш фовард декларейшн!             |
    ///--------------------------------------:
    template<typename T>
    void write(Vec2u pos, const T& m)
    {   myl::Mat2D::write(pos, m.get_mat());
    }

    void write(Vec2u pos, std::wstring s)
    {   myl::Mat2D::write(pos, s);
    }
};

///----------------------------------------------------------------------------|
/// Конкретный способ или девайс вывода на монитор.
///----------------------------------------------------------------------------:
struct  Hard
{
    Hard& operator<<(const VScreen& scr)
    {   for(const auto& s : scr.get_mat())
        {   DEVICE << s << L"\n";
        }   DEVICE      << L"\n";
        return  *this;
    }
};

///----------------------------------------------------------------------------|
/// Доступ к виртуальному экрану через враппер.
///----------------------------------------------------------------------------:
struct  VScreenWrap
{       VScreenWrap(VScreen& vs, unsigned d) : vsc(vs), dispace_x(d)
        {
        }

    template<typename T>
    void write(Vec2u pos, const T& m)
    {   pos.x += dispace_x;
        vsc.write(pos,  m);
    }

    void write(Vec2u pos, std::wstring s)
    {   pos.x += dispace_x;
        vsc.write(pos,  s);
    }

    template<typename T>
    void    write_alfa(Vec2u pos, const T& o)
    {   pos.x += dispace_x;
        vsc.write_alfa(pos,  o);
    }

    const std::vector<std::wstring>& get_mat() const { return vsc.get_mat(); }

    unsigned NW(){ return vsc.NW(); }
    unsigned NH(){ return vsc.NH(); }

private:
    VScreen& vsc      ;
    unsigned dispace_x;
};

#endif // VSCR_H
