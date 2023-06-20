#include "resurces.h"

std::unique_ptr<Resurces> ResurcesHolder::res = nullptr;

void Resurces::create()
{

    const std::initializer_list<std::wstring> data_logo =
    {   L"|-------------------|",
        L"|                   |",
        L"|      ЯTeTRis      |",
        L"|    (xlat-code)    |",
        L"|       2023©       |",
        L"|                   |",
        L"|-------------------|"
    };
    m.emplace_back(new Bunner(data_logo));

    const std::initializer_list<std::wstring> data_game_over =
    {   L"|-------------------|",
        L"|                   |",
        L"|     GAME OVER!    |",
        L"|                   |",
        L"|-------------------|"
    };
    m.emplace_back(new Bunner(data_game_over));

    const std::initializer_list<std::wstring> data_fin =
    {   L"########################",
        L"#                      #",
        L"#   Program FINISHED!  #",
        L"#                      #",
        L"########################"
    };
    m.emplace_back(new Bunner(data_fin));

    const std::initializer_list<std::wstring> data_menu_start =
    {   L"#######-START-MENU-#######",
        L"#                        #",
        L"#                        #",
        L"#   1. Одиночная ИГРА.   #",
        L"#   2. Два     ИГРОКА.   #",
        L"#   3. ... ?             #",
        L"#                        #",
        L"#   ...                  #",
        L"#                        #",
        L"#   ESCAPE ---- ВЫХОД.   #",
        L"#                        #",
        L"#####################№####"
    };
    m.emplace_back(new Bunner(data_menu_start));

    const std::initializer_list<std::wstring> data_todo =
    {   L"//////////-TODO-//////////",
        L"/                        /",
        L"/  ... в разработке ...  /",
        L"/                        /",
        L"//////////////////////////"
    };
    m.emplace_back(new Bunner(data_todo));

    if(m.size() != Resurces::E_SIZE)
    {   throw(ERROR_EXCEPTION_MESS("Amount resurces!"));
    }
}



