#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "myl.h"

struct  Infopanel : public myl::Mat2D
{       Infopanel()
            : Mat2D(0, 0, ' ')
        {
        }

    Vec2u pos{0, 0};

    int& push(std::wstring_view str)
    {   strs.push_back(std::make_unique<std::pair<std::wstring, int>>(str, 0));
        return strs.back()->second;
    }

    const Infopanel& update()
    {   calc(); return *this;
    }

private:
    std::vector<std::unique_ptr<std::pair<std::wstring, int>>> strs;
    const unsigned                                       amount_num = 4;

    void calc()
    {   if(strs.empty()) return;

        const unsigned H = 2 + strs.size();

        unsigned W = 0;
        {
            for(const auto& e : strs)
            {   if(e->first.size() > W) W = e->first.size();
            }

            mat.resize(H);

            unsigned i = 1;

            for(auto& e : strs)
            {
                auto n = std::to_wstring(e->second);
                     n.resize(5, ' ');

                auto a = e->first;
                     a.resize(W + 2, L' ');

                mat[i++]  = L"| " + a + n + L"|";
            }

            mat.front() = std::wstring(mat[1].size(), '-');
            mat.back () = std::wstring(mat[1].size(), '-');
        }
    }
};

#endif // INFOPANEL_H
