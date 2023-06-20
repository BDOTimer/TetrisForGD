#ifndef FIGURE_H
#define FIGURE_H

#include "myl.h"
#include <fstream>

///----------------------------------------------------------------------------|
/// Загрузка набора фигур из файла.
///----------------------------------------------------------------------------:
struct  LoaderFigures
{       LoaderFigures()
        {
            load_from_file();
        }

    myl::Mat2D* gen(int r = -1)
    {   if(r < 0)  r = rand() % figures.size();
        return &figures[unsigned(r)];
    }

    unsigned get_amount()const { return figures.size(); }

    void test(){ test_01(); }

private:
    std::vector<myl::Mat2D> figures;

    void test_01()
    {   for    (const auto& mat : figures)
        {   DEVICE << "[FIGURE]:" << '\n';
            for(const auto& s   : mat.get_mat())
            {   DEVICE   << s  << '\n';
            }
        }
    }

    const wchar_t C = ' ';

    void load_from_file()
    {
        if(std::wifstream file("figures.txt"); file.is_open())
        {
            for(std::wstring s; std::getline(file, s);)
            {
                if(s.find(L"[FIGURE]") != s.npos)
                {
                    for(bool b = true; b;)
                    {
                        b = false;

                        std::vector<std::wstring> temp;

                        for(int n = 0; n < 5 && std::getline(file, s); ++n)
                        {
                            if(s.find(L"[FIGURE]") != s.npos)
                            {   b = true;
                                break;
                            }

                            if(s.size() != 5) s.resize(5, C);

                            temp.push_back(s);
                        }

                        if(!is_empty(temp))
                        {
                            for(int n = temp.size(); n < 5 && n > 2; ++n)
                            {
                                temp.push_back(std::wstring(5, C));
                            }
                        }

                        if(temp.size() == 5 )
                        {   figures.push_back(myl::Mat2D(temp));
                        }

                    }
                }
            }
        }
        else DEVICE << "ERROR FILE\n";
    }

    bool is_empty(const std::vector<std::wstring>& f) const
    {   for    (const auto& s : f)
        {   for(const auto& c : s)
            {   if(c != C) return false;
            }
        }
        return true;
    }
};

///----------------------------------------------------------------------------|
/// Падающая фигура.
///----------------------------------------------------------------------------:
struct  Figure
{       Figure(){}
        Figure(Vec2u pos_scr) : pos(pos_scr)
        {
        }

    Vec2u pos{0, 0};

    myl::Mat2D& get_mat() const
    {   if(pFig == nullptr) throw(ERROR_EXCEPTION_MESS("pFig == nullptr"));
        return *pFig;
    }

    void gen(int n = -1)
    {   pFig = figures.gen(n);
    }

    unsigned get_amount() const { return figures.get_amount(); }


private:
    LoaderFigures figures;
    myl::Mat2D*   pFig = nullptr;
};


#endif // FIGURE_H
