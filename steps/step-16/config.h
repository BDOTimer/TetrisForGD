#ifndef CONFIG_H
#define CONFIG_H

#include "myl.h"

///----------------------------------------------------------------------------|
/// Конфигурация программы.
///----------------------------------------------------------------------------:
struct Config
{
    std::string name   = "Default"    ;
    std::string figkit = "figures.txt";

    unsigned H  = 22  ; /// Высота доски.
    unsigned W  = 58  ; /// Ширина доски.

    unsigned HK = 13  ; /// Высота корзины.
    unsigned WK = 13  ; /// Ширина корзины.

    wchar_t  C  = '.' ; /// Символ заполнения.

    std::wstring_view version{L"Step-16"};

    void load_from_file(){ /* ... */ }
};

extern Config const* cfg;

#endif // CONFIG_H
