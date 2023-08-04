#ifndef TL_H
#define TL_H
///----------------------------------------------------------------------------|
/// ...
///----------------------------------------------------------------------------:
#include <list>
#include <vector>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string_view>

template <typename... TT>
void Banner(TT&&... vals)
{   ((std::wcout << vals << std::endl), ...);
}

using vecstr_t = std::vector<std::wstring>;

inline std::wostream& operator<<( std::wostream& o, const vecstr_t& m)
{   for(const auto& s : m) std::wcout << s << '\n';
    return o;
}

///----------------------------------------------------------------------------|
/// Cipher
///----------------------------------------------------------------------------:
struct  Cipher
{       Cipher(std::wstring_view fn,
              std::wstring_view pass) : filename(fn), myrand(pass)
        {   seed = myrand.getseed   () ;
        }

    std::wstring_view filename;

    ///--------------------------|
    /// Сохранить.               |
    ///--------------------------:
    void save(std::wstring_view s)
    {
        auto en = encode(s);

        std::ofstream f(filename.data(), std::ifstream::binary);

        f.write((char*)&en[0], en.size() * sizeof(en[0]));
    }

    ///--------------------------|
    /// Загрузить.               |
    ///--------------------------:
    std::wstring load()
    {
        auto fsize = (unsigned)filesize(filename);
        std::vector<int16_t> m; m.resize(fsize / 2);

        std::ifstream f(filename.data(), std::ifstream::binary);

        f.read((char*)&m[0], fsize);

        return decode(m);
    }

    std::wstring_view get_status_str()
    {   return is_good ? L"Успех!\n" : L"Фейл!\n";
    }

    bool get_status(){ return is_good; }

private:
    ///--------------------------|
    /// myRand.                  |-------------------:
    ///--------------------------|
    struct  myRand
    {       myRand(std::wstring_view p)
            {   setseed(p);
            }

        void setseed(std::wstring_view s)
        {   seed = 8938263476806173987;
            for(const auto c : s) { seed *= c; seed += c; }
        }

        void setseed(uint64_t s){ seed = s; }

        uint64_t operator()()
        {   return seed = (seed * 79 + 13) >> 1;
        }

        uint64_t getseed(){ return seed; }

    private:
        uint64_t seed = 8938263476806173987;
    };
    ///----------------------------------------------.

    std::vector<int16_t> encode(std::wstring_view s)
    {
        myrand.setseed(seed);

        std::vector<int16_t> m(1); m.reserve(s.size());

        int16_t summa = 0;

        for(const auto c : s)
        {
            m.push_back(c - (int16_t)myrand());
            summa += (int)c;
        }

        m[0] = summa;

        return m;
    }

    std::wstring decode(std::vector<int16_t> m)
    {
        myrand.setseed(seed);

        std::wstring s; s.reserve(m.size());

        int16_t summa = 0;

        for(auto i = m.cbegin() + 1; i != m.cend(); ++i)
        {
            s.push_back( *i + (int16_t)myrand());
            summa += (int)s.back();
        }

        is_good = summa == m[0];

        if(!is_good)
        {   s = L"Топлист краш ...";
        }
        return s;
    }

private:
    bool is_good;

    static std::ifstream::pos_type filesize( std::wstring_view filename)
    {      std::ifstream in(filename.data(), std::ifstream::ate   |
                                             std::ifstream::binary);
        return in.tellg();
    }

    myRand myrand;
    uint64_t seed;

    friend void testclass_myRand();
};

///-------------------|
/// testclass_myRand  |
///-------------------:
inline void testclass_myRand()
{   Cipher::myRand r(L"" );
                   r.setseed(L"admin");
                   r.setseed(L"0");
                   r.setseed(L"1");
                   r.setseed(L"2");
                   r.setseed(L"3");
                   r.setseed(L"В"); std::cin.get();

    const size_t N = 100;

    std::vector<int> m(N, 0);

    for(size_t i = 0; i < 1'000'000; ++i)
    {
        m[r()%N]++;
    }

    for(const auto a : m) std::cout << a << '\n';

    std::cin.get();
}

///-------------------|
/// testclass_Cipher  |
///-------------------:
inline void testclass_Cipher()
{
    std::wstring test{L"ЯaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaЯ"};

    std::wcout << test << std::endl;

    [[maybe_unused]] Cipher cipher(L"tl.txt", L"admin2023");


    cipher.save(test  );

    l(cipher.load())

    l(cipher.get_status_str())
}

///----------------------------------------------------------------------------|
/// Serial.
///----------------------------------------------------------------------------:
struct  Serial   : public std::wstringstream
{       Serial() : cipher(L"tl.bin", L"password:admin2023.")
        {
        }

    void to_file()
    {   cipher.save(this->str());
    }

    void from_file()
    {     this->str(cipher.load());
      //l(this->str())
    }

    std::wstring_view get_status_str() { return cipher.get_status_str(); }

private:
    Cipher cipher;
};

///----------------------------------------------------------------------------|
/// Структура в качестве примера.
///----------------------------------------------------------------------------:
struct Record
{   std::wstring name;
    int  amount_game = 0;
    int  counted     = 0;

    bool add(int cnt)
    {   amount_game++;
        if(cnt > counted) { counted = cnt; return true; }
        return false;
    }
};

///------------------|
/// wostream         |
///------------------:
inline std::wostream& operator<<(std::wostream& o, const Record& c)
{   o   << c.name        << " - "
        << c.amount_game << " - "
        << c.counted     ;
    return o;
}

///------------------|
/// Serial Record    |
///------------------:
inline Serial& operator<<(Serial& o, const Record& c)
{   o   << c.name        << '\n'
        << c.amount_game << '\n'
        << c.counted     ;
    return o;
}

inline Serial& operator>>(Serial& o, Record& c)
{
    std::vector<std::wstring> m(3);

    for(size_t i = 0; i < m.size() && getline(o, m[i]); ++i);

    c.name        =           m[0] ;
    c.amount_game = std::stoi(m[1]);
    c.counted     = std::stoi(m[2]);

    return o;
}

///----------------------------------------------------------------------------|
/// Структура в качестве примера.
///----------------------------------------------------------------------------:
template<typename T>
struct  Data
{       Data(size_t anum) : alloc_number(anum)
        {   data.reserve                (anum);
        }

    std::vector   <T >  data;
    std::vector   <T*> pdata;

    void add(const T&    d)
    {    data.push_back( d);
        pdata.push_back(&data.back());

        realloc();
    }

    void sort()
    {   std::sort(pdata.begin(), pdata.end(),
            [](T* a, T* b){ return a->counted > b->counted; }
        );
    }

    std::vector<std::wstring> formated()
    {
        if(pdata.empty())
            return { L"|----Топ----|",
                     L"|           |",
                     L"|   ПУСТО   |",
                     L"|           |",
                     L"|-----------|"};

        size_t SIZESTR = pdata.size() > cfg->H - 6 ? cfg->H - 6 : pdata.size();

        std::vector<std::wstring> res(SIZESTR + 4, L"| ");

        unsigned a = 3,
                 b = 3,
                 c = 3;

        std::vector<std::vector<std::wstring>> h;

        ///--------------------|
        /// Получить размеры.  |
        ///--------------------:
        for(size_t i = 0; i < SIZESTR; ++i)
        {
            const auto p = pdata[i];

            h.push_back(std::vector<std::wstring>(3));

            h.back()[0] =                 p->name        ;
            h.back()[1] = std::to_wstring(p->amount_game);
            h.back()[2] = std::to_wstring(p->counted    );

            if(a < h.back()[0].size()) a = h.back()[0].size();
            if(b < h.back()[1].size()) b = h.back()[1].size();
            if(c < h.back()[2].size()) c = h.back()[2].size();
        }

        ///--------------------|
        /// Выравнивание.      |
        ///--------------------:
        for(auto& e : h)
        {   e[0].resize(a, L' ');
            e[1].resize(b, L' ');
            e[2].resize(c, L' ');
        }

        ///--------------------|
        /// Результат.         |
        ///--------------------:
        for(size_t i = 0, N = h.size(); i < N; ++i)
        {
            const size_t I = i + 2;

            res[I] += h[i][0];
            res[I] += L" ";
            res[I] += h[i][1];
            res[I] += L" ";
            res[I] += h[i][2];
            res[I] += L" |";
        }

        ///--------------------|
        /// Голова и ноги.     |
        ///--------------------:
        {
            const size_t N = res[2].size();

            std::wstring s1(N, L'-'); s1.front() = L'|'; s1.back() = L'|';
            std::wstring s2(N, L' '); s2.front() = L'|'; s2.back() = L'|';

            res.front() = res    .back()      = s1;
            res[1]      = res[res.size() - 2] = s2;
        }

        ///--------------------|
        /// Добавить заголовок.|
        ///--------------------:
        {
            std::wstring s{L"Топ Лист"};

            auto C = (res.front().size() - s.size()) / 2;

            for(size_t i = 0; i < s.size(); ++i) res.front()[i + C] = s[i];
        }

        return res;
    }

private:
    ///------------------|
    /// pdata устарел?   |
    ///------------------:
    void realloc()
    {   if(data.size() <= alloc_number) return;

        alloc_number = data.max_size();

        pdata.clear  ();
        pdata.reserve(alloc_number);

        for(auto& e : data) pdata.push_back(&e);
    }

    size_t alloc_number;
};

struct  Cargo   : protected Data<Record>
{       Cargo() :           Data(100) {}

    void  add(const Record data)
    {   D.add(             data);
    }

    void sort() { D.sort(); }

    const std::vector<Record*>& get() const
    {   return this->pdata;
    }

    const std::vector<std::wstring>& get_strs() const
    {   return form;
    }

    void formated()
    {   D.sort   ();
        form = D.formated();
    }

    void test_formated()
    {         formated();
        auto          m = get_strs();
        std::wcout << m << '\n';
    }

private:
    Data& D = *this;

    std::vector<std::wstring> form;

    friend std::wostream& operator<<(std::wostream& o, const Cargo& c);
    friend Serial& operator<<(Serial& o, const Cargo& c);
    friend Serial& operator>>(Serial& o,       Cargo& c);
};

///------------------|
/// wostream         |
///------------------:
inline std::wostream& operator<<(std::wostream& o, const Cargo& c)
{   for(const auto& e : c.get()) o << *e << '\n'; return o;
}

///------------------|
/// Serial Cargo     |
///------------------:
inline Serial& operator<<(Serial& o, const Cargo& c)
{   o.clear();
    o << c.get().size() << '\n';
    for(const auto& e : c.get()) o << *e << '\n';
    return o;
}

inline Serial& operator>>(Serial& o, Cargo& c)
{
    o.seekg(0);

    std::wstring s; std::getline(o, s);
                         size_t N;
                                N = std::stoi(s);
                     c. data.resize(N);
                     c.pdata.clear();
    for (auto& e :   c. data)
    {   o >>   e ;
        c.pdata.push_back(&e);
    }
    return o;
}

///------------------|
/// testclass_Cargo  |
///------------------:
inline void testclass_Cargo()
{
    Banner(
    L"///--------------------|",
    L"/// Init               |",
    L"///--------------------:");
    Cargo cargo;
          cargo.test_formated();
          cargo.add({L"A" ,  1,    2});
          cargo.add({L"xc", 11, 2227});
          cargo.test_formated();

          cargo.add({L" q w e r t y"                              , 2023, 555});
          cargo.add({L"1234a_1234b 1234c_1234d 123e_234f_ЙЦУКЕНГ_", 2024, 888});

    Record       p                      ;
                 p.name        = L"name";
                 p.amount_game =    2025;
                 p.counted     =     777;
      cargo.add (p);
    l(cargo)

    Banner(
    L"///--------------------|",
    L"/// Serial << cargo    |",
    L"///--------------------:");
    Serial  ss;
            ss << cargo ;
            ss.to_file();
          l(ss.str    ())

    Banner(
    L"///--------------------|",
    L"/// Serial::from_file()|",
    L"///--------------------:");
    Serial  ff;
            ff.from_file     ();
          l(ff.str           ())
          l(ff.get_status_str())

    Banner(
    L"///--------------------|",
    L"/// Serial >> Cargo    |",
    L"///--------------------:");
    Cargo   cc;
    ff >>   cc;
    ff <<   cc;
    ff >>   cc; ////////////////////////////////////////////////////////////////
          l(cc)
          l(ss.str().size())
          l(ff.str().size())
          l(ss.str())
          l(ff.str())

    l(cc)
      cc.sort();
    l(cc)
      cc.test_formated();

    std::wcout << (ss.str() == ff.str() ? L"Тест:OK" : L"Тест:FAIL\a\a") <<'\n';

    std::cin.get();
}

///----------------------------------------------------------------------------|
/// testclass_tp
///----------------------------------------------------------------------------:
inline void testclass_tp()
{
    setlocale(0, "");

    Banner(
    L"///--------------------|",
    L"/// Start ...          |",
    L"///--------------------:");

  //testclass_myRand();
  //testclass_Cipher();
    testclass_Cargo ();
}

#endif // TL_H
