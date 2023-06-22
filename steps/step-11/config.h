#ifndef CONFIG_H
#define CONFIG_H

#include "myl.h"

///----------------------------------------------------------------------------|
/// Конфигурация программы.
///----------------------------------------------------------------------------:
struct Config
{
    unsigned H = 22 ; /// Высота доски.
    unsigned W = 29 ; /// Ширина доски.
    wchar_t  C = '.'; /// Символ заполнения.

    unsigned HK = 13; /// Высота корзины.
    unsigned WK = 13; /// Ширина корзины.

    std::wstring_view version{L"Step-11"};

    void load_from_file(){ /* ... */ }
};

inline const Config cfg;

#endif // CONFIG_H
