#ifndef VSCR_H
#define VSCR_H

#include "config.h"

///----------------------------------------------------------------------------|
/// Виртуальный экран.
///----------------------------------------------------------------------------:
struct  VScreen : public myl::Mat2D
{       VScreen() : Mat2D(cfg.W, cfg.H, cfg.C)
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

#endif // VSCR_H
