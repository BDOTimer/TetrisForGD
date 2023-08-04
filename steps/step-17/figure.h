#ifndef FIGURE_H
#define FIGURE_H

#include "myl.h"
#include <list>
#include <fstream>

struct  proFigure : public myl::Mat2D
{       proFigure(const std::vector<std::wstring>& e) : myl::Mat2D(e)
        {
        }

    unsigned id                   {0};

    ///------------------------------|
    /// Вероятность выпадения фигуры.|
    ///------------------------------:
    unsigned probability          {0};
};

///----------------------------------------------------------------------------|
/// Загрузка набора фигур из файла.
///----------------------------------------------------------------------------:
struct  LoaderFigures
{       LoaderFigures()
        {
            load_from_file();
        }

    unsigned probability_summa = 0;

    myl::Mat2D* gen(int r = -1)
    {   if(r < 0)  r  = rand() % figures.size(  );
        for(int nrot  = rand() % 4; nrot; nrot--)
        {   figures[unsigned(r)].rot_n();
        }
        return &figures[unsigned(r)];
    }

    unsigned get_amount()const { return figures.size(); }

    void test                    () const { test_01(); }
    void test_extract_probability() const
    {
        std::wstring s{L"qwerty : 2023xxx"};

        auto n = extract_probability(s,  0);

        DEVICE << L"probability: " << std::to_wstring(n)  << '\n';
    }

    unsigned   get_id_rand()
    {   int    r = rand() % maprand.size();
        return maprand[(unsigned)r];
    }

private:
    std::vector<proFigure> figures;

    void test_01() const
    {   for    (const auto& mat : figures)
        {   DEVICE << "[FIGURE]:" << std::to_wstring(mat.probability) << '\n';
            for(const auto& s   : mat.get_mat())
            {   DEVICE   << s  << '\n';
            }
        }
    }

    const wchar_t C = ' ';

    std::wstring_view FIGKEY = L"[FIGURE]";

    void load_from_file()
    {
        if(std::wifstream file(cfg->figkit.c_str()); file.is_open())
        {
            std::vector<std::vector<std::wstring>> m;
            unsigned                        probs{0};
            {
                for   ( std::wstring s ; std::getline(file, s);)
                {
                    if( s.find(FIGKEY) != s.npos)
                    {
                        if(!m.empty())
                        {
                            if(m.back    ( ).size() < 3)
                            {  m.pop_back( );
                            }
                            else
                            {
                                ///------|
                                /// Res. |
                                ///------:
                                /// ...

                                for(size_t i = m.back().size(); i < 5; ++i)
                                {   m.back().push_back(std::wstring(5,  C));
                                }

    figures.push_back (proFigure(    m.back  ())  );
    figures.back().probability = probs;
    figures.back().id          = figures.size() - 1;

                            }
                        }

                        m.push_back(std::vector<std::wstring>     ());
                        probs = extract_probability(s, FIGKEY.size());
                    }
                    else if(!m.empty() && m.back ().size()  < 5)
                    {
                        m.back ().push_back     (s   );
                        m.back ().back( ).resize(5, C);
                    }
                }

                if(m.empty())
                {   DEVICE << "ERROR: FIGKEY not find.\n";
                    return;
                }
            }
        }
        else DEVICE << "ERROR FILE\n";

        for(const auto& f : figures) probability_summa += f.probability;

        init_maprand();
    }

    bool is_empty(const std::vector<std::wstring>& f) const
    {   for    (const auto& s : f)
        {   for(const auto& c : s)
            {   if(c != C) return false;
            }
        }
        return true;
    }

private:
    unsigned extract_probability(std::wstring_view s, size_t p) const
    {   unsigned a = 0;

        if( p = s.find(L':', p); p != s.npos)
        {
            try
            {   ++p;
                std::wstring ss(s.substr(p, s.size() - p));
                auto d = std::stod (ss);

                a = d < 0 ? 0 : (unsigned)d;
            }
            catch(...)
            {   a = 1;
            }
        }
        return  a;
    }

    std::vector<unsigned> maprand;
    void init_maprand ()
    {   maprand.resize(probability_summa, 0);

        unsigned i = 0;

        for(const auto& f : figures)
        {
            const auto& N = f.probability;

            for(unsigned j = 0; j < N; ++j)
            {   maprand[i++] = f.id;
            }
        }

      //debug_maprand(); ///////////////////////////////////////////////////////
    }

    void debug_maprand()
    {   for(const auto& id : maprand)
        {   DEVICE << std::to_wstring(id) << '\n';
        }
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

    void genn(int n = -1)
    {   pFig = figures.gen(n);
    }

    void gen_probab_rand()
    {

        pFig = figures.gen(rrand());
    }

    unsigned get_amount() const { return figures.get_amount(); }


private:
    LoaderFigures figures;
    myl::Mat2D*   pFig = nullptr;

    unsigned rrand()
    {   return figures.get_id_rand();
    }
};


#endif // FIGURE_H
