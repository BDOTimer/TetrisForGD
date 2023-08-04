#ifndef MYL_H
#define MYL_H

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <memory>
#include <initializer_list>

#include "control\timer.h"
#include "idevice.h"

#include <locale>
#include <codecvt>

inline std::wstring utf8_to_wstring(const std::string& str)
{      std::wstring_convert<std:: codecvt_utf8_utf16<wchar_t> > myconv;
    return  myconv.from_bytes(str);
}

struct Vec2u
{   unsigned x, y;

    void operator+=(const unsigned xx){ x += xx; }
};

///---------|
/// my lib  |
///---------:
namespace myl
{
    struct  Mat2D
    {       Mat2D(){}
            Mat2D(unsigned W, unsigned H, wchar_t C)
                :
                    color (C),
                    mat   (H, std::wstring(W, C))
            {
            }

            Mat2D(const std::vector<std::wstring>& dat)
                :
                    color (0  ),
                    mat   (dat)
            {
            }

        ///--------------------|
        /// Смещение.          |
        ///--------------------:
        Vec2u displace = {0, 0};

        unsigned NW() const { return mat.back().size(); }
        unsigned NH() const { return mat       .size(); }
        unsigned color;

        const std::vector<std::wstring>& get_mat() const { return mat; }

        ///--------------------------------------|
        /// Пишем одну матрицу в другую.         |
        ///--------------------------------------:
        void write(Vec2u pos, const myl::Mat2D& m)
        {
            pos += displace.x;

            const unsigned W = m.NW();
            const unsigned H = m.NH();

            for    (unsigned r = pos.y, j = 0; r < NH() && j < H; ++r, ++j)
            {   for(unsigned c = pos.x, i = 0; c < NW() && i < W; ++c, ++i)
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

            const unsigned W = m.NW();
            const unsigned H = m.NH();

            for    (unsigned r = pos.y, j = 0; r < NH() && j < H; ++r, ++j)
            {   for(unsigned c = pos.x, i = 0; c < NW() && i < W; ++c, ++i)
                {   if(m.mat[j][i] != ' ')
                    {    mat[r][c]  = m.mat[j][i];
                    }
                }
            }
        }

        void write(Vec2u pos, std::wstring_view s)
        {   auto&  str  = mat[pos.y];
            for(auto i  =     pos.x, j = 0u; i < str.size()  &&
                                             j < s  .size(); ++i, ++j)
            {   str [i] = s[j];
            }
        }

        ///--------------------------------------|
        /// Позицию для размещения по центру.    |
        ///--------------------------------------:
        Vec2u get_pos_center(const myl::Mat2D& m) const
        {   return { (NW() - m.NW()) /2, (NH() - m.NH()) /2 };
        }

        void clear(wchar_t C =  '.')
        {   std::wstring s(NW(), C );
            for(auto& d :  mat)  d = s;
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

    template<typename S> inline
    void split(const  S& text, std::vector<S>& dest, const S separ)
    {   for(size_t i , e = 0;
                  (i = text.find_first_not_of(separ, e)) != S::npos;)
        {   if(   (e = text.find_first_of    (separ, i)) == S::npos )
                   e = text.size();
            dest.emplace_back(text.substr(i, e - i));
        }
    }
}

inline     std::string&  operator<<(std::string& o, const std::wstring& s)
{   for(const auto c : s) o.push_back(char(c));
    return o;
}

inline     std::wstring& operator<<(std::wstring& o, const std::string& s)
{   return (o = std::wstring(s.begin(), s.end()));
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

#define TESTINFO std::wcout << "TESTINFO: " << __func__ << '\n'

//#define  ll(v)  std::wcout << #v << " = " << (v) << "\n";

#endif // MYL_H
