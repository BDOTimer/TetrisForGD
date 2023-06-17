#ifndef MYL_H
#define MYL_H

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
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
        /// Пишем одну матрицу в другую          |
        /// c альфа-каналом.                     |
        ///--------------------------------------:
        template<typename T>
        void write_alfa(const Vec2u& pos, const T& o)
        {
            const myl::Mat2D& m = o.get_mat();

            const unsigned& W = m.width;
            const unsigned& H = m.height;

            for    (unsigned r = pos.y, j = 0; r < height && j < H; ++r, ++j)
            {   for(unsigned c = pos.x, i = 0; c < width  && i < W; ++c, ++i)
                {   if(m.mat[j][i] != ' ')
                    {    mat[r][c]  = m.mat[j][i];
                    }
                }
            }
        }

        ///--------------------------------------|
        /// Позицию для размещения по центру.    |
        ///--------------------------------------:
        Vec2u get_pos_center(const myl::Mat2D& m) const
        {   return { (width - m.width) /2, (height - m.height) /2 };
        }

        void clear(wchar_t C =  '.')
        {   std::wstring s(width, C);
            for(auto& d : mat) d = s;
        }

        ///--------------------------------------|
        /// Вращение по часовой.                 |
        ///--------------------------------------:
        void rot_p()
        {
            std::vector<std::wstring> m;
            for    (unsigned c = 0; c < mat.front().size(); ++c)
            {
                m.push_back(std::wstring());
                for(unsigned r = mat.size() - 1; r < mat.size() ; --r)
                {   m.back().push_back(mat[r][c]);
                }
            }
            mat = m;
        }

        void rot_n()
        {
            std::vector<std::wstring> m;
            for(unsigned c = mat.front().size() - 1; c < mat.front().size(); --c)
            {
                m.push_back(std::wstring());
                for(unsigned r = 0; r < mat.size() ; ++r)
                {   m.back().push_back(mat[r][c]);
                }
            }
            mat = m;
        }

    protected:
        std::vector<std::wstring> mat;
    };

    inline void sleep(int ms)
    {   std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
}

struct  CustomException : public std::exception
{       CustomException(int line, const char* filename, const char* mess = "")
        {   reason = std::string("\nERROR_EXCEPTION:\n    FILE: ") +
                                                    cut(filename ) +
                             "\n    LINE: " + std::to_string(line)
                           + "\n    MESS: \"" + mess + "\"\n\n";
        }

    std::string LEFT = "code";
    std::string reason;

    virtual const char* what() const throw()
    {   return  reason.c_str();
    }

    std::string cut(std::string s)
    {   const auto pos = s.find  (LEFT) + LEFT.size() + 1;
        return           s.substr(pos, s.size() - pos);
    }
};

#define ERROR_EXCEPTION         CustomException(__LINE__, __FILE__)
#define ERROR_EXCEPTION_MESS(M) CustomException(__LINE__, __FILE__, M)

#endif // MYL_H
