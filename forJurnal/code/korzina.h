#ifndef KORZINA_H
#define KORZINA_H

#include "figure.h"

///----------------------------------------------------------------------------|
/// Корзина.
///----------------------------------------------------------------------------:
struct  Korzina : public myl::Mat2D
{       Korzina(unsigned w, unsigned h)
            :   myl::Mat2D(w + 2, h + 1, ' '),
                pos(get_pos_center({w, h}))
        {
            init();
        }

    Vec2u pos{0, 0};

    Korzina& operator<<(const Figure& F)
    {
        const auto&     m = F.get_mat().get_mat();
        const unsigned& W = F.get_mat().width ;
        const unsigned& H = F.get_mat().height;


        for    (unsigned r = F.pos.y, j = 0; j < H; ++r, ++j)
        {   for(unsigned c = F.pos.x, i = 0; i < W; ++c, ++i)
            {
                const auto&[fpx, fpy] = calc({c, r});

                if(m[j][i] != ' ' && fpx < width && fpy < height)
                {
                    mat[fpy][fpx] = m[j][i];
                }
            }
        }
        return *this;
    }

    ///--------------------------------------|
    /// Позиция для размещения по центру.    |
    ///--------------------------------------:
    static Vec2u get_pos_center(const Vec2u szk)
    {   return { (cfg.W - szk.x) /2 - 1, (cfg.H - szk.y) /2 };
    }

    ///--------------------------------------|
    /// Позиция старта фигуры.               |
    ///--------------------------------------:
    Vec2u get_pos_figure_start()
    {   return { pos.x + width /2 - 2, pos.y - 2 };
    }

private:
    void init()
    {   mat.back() = std::wstring(width, '_');
        for(auto& s : mat)
        {   s.front() = '|';
            s.back () = '|';
        }
    }

    ///--------------------------------------|
    /// Пересчёт position источника          |
    /// относительно position корзины.       |
    ///--------------------------------------:
    Vec2u calc(const Vec2u fpos) const
    {   return { fpos.x - pos.x, fpos.y - pos.y };
    }
};

#endif // KORZINA_H
