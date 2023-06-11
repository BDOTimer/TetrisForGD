#ifndef MYL_H
#define MYL_H

#include <vector>
#include <string>
#include <initializer_list>

#include "idevice.h"

struct Vec2u
{   unsigned x, y;
};

///---------|
/// my lib  |
///---------:
namespace myl
{
    struct  Mat2D
    {       Mat2D(unsigned W, unsigned H, wchar_t C)
                :
                    width (W),
                    height(H),
                    color (C),
                    mat   (H, std::wstring(W, C))
            {
            }

            Mat2D(const std::vector<std::wstring>& dat)
                :
                    width (dat.front().size()),
                    height(dat        .size()),
                    color (0  ),
                    mat   (dat)
            {
            }

        unsigned width ;
        unsigned height;
        unsigned color ;

        const std::vector<std::wstring>& get_mat() const { return mat; }

        ///--------------------------------------|
        /// Пишем одну матрицу в другую.         |
        ///--------------------------------------:
        void write(Vec2u pos, const myl::Mat2D& m)
        {
            const unsigned& W = m.width;
            const unsigned& H = m.height;

            for    (unsigned r = pos.y, j = 0; r < height && j < H; ++r, ++j)
            {   for(unsigned c = pos.x, i = 0; c < width  && i < W; ++c, ++i)
                {   mat[r][c] = m.mat[j][i];
                }
            }
        }

        ///--------------------------------------|
        /// Позицию для размещения по центру.    |
        ///--------------------------------------:
        Vec2u get_pos_center(const myl::Mat2D& m) const
        {   return { (width - m.width) /2, (height - m.height) /2 };
        }

    private:
        std::vector<std::wstring> mat;
    };
}


#endif // MYL_H
