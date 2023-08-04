#ifndef KORZINA_H
#define KORZINA_H

#include "figure.h"

///----------------------------------------------------------------------------|
/// Корзина.
///----------------------------------------------------------------------------:
struct  Korzina : public myl::Mat2D
{       Korzina(unsigned w, unsigned h)
            :   myl::Mat2D(w + 2, h + 1, ' ')//,
                //pos(get_pos_center({w, h}, -1))
        {
            //pos.x = cfg->WK / 2;
            pos.y = cfg->H - cfg->HK - 2;
            init();
        }

    Vec2u pos{0, 0};

    Korzina& operator<<(const Figure& F)
    {
        const auto&    m = F.get_mat().get_mat();
        const unsigned W = F.get_mat().NW() ;
        const unsigned H = F.get_mat().NH();


        for    (unsigned r = F.pos.y, j = 0; j < H; ++r, ++j)
        {   for(unsigned c = F.pos.x, i = 0; i < W; ++c, ++i)
            {
                const auto&[fpx, fpy] = calc({c, r});

                if(m[j][i] != ' ' && fpx < NW() && fpy < NH())
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
    {   return { (cfg->W - szk.x) /2 - 1,
                 (cfg->H - szk.y) /2   };
    }

    ///--------------------------------------|
    /// Позиция старта фигуры.               |
    ///--------------------------------------:
    Vec2u get_pos_figure_start()
    {   return { pos.x + NW() /2 - 2, pos.y - 2 };
    }

    ///-------------|
    /// Хуже...     |
    ///-------------:
    int check_lines()
    {   int cnt = 0;

        std::vector<std::wstring> d(NH(), std::wstring(NW(), ' '));

        d.back() = mat.back();

        unsigned j = mat.size() - 2;

        for(unsigned i = mat.size() - 2; i < mat.size(); --i)
        {
            if(mat[i].find(' ') == std::string::npos)
            {
                cnt++;
            }
            else d[j--] = mat[i];
        }

        auto a = std::wstring(NW(), ' ');
             a.front() = '|';
             a.back () = '|';

        for(unsigned i = 0; i < (unsigned)cnt; i++)
        {   d[i] = a;
        }

        mat = d;

        return cnt;
    }

    ///-------------|
    /// Лучше...    |
    ///-------------:
    int check_lines_02()
    {   int cnt = 0;

        auto s{std::wstring(NW(), ' ')};
             s  .front() = '|';
             s  .back () = '|';

        auto b = mat.rbegin() + 1;
        auto a = b;

        for(; b != mat.rend(); ++b)
        {
            if(b->find(' ') == std::string::npos)
            {
               *b = s; cnt++;
            }
            else
            {   if(cnt) std::swap(*a, *b);
                ++a;
            }
        }

        return cnt;
    }

private:
    void init()
    {   mat.back() = std::wstring(NW(), '_');
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
