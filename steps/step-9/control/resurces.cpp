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

    if(m.size() != Resurces::E_SIZE)
    {   throw(ERROR_EXCEPTION_MESS("Amount resurces!"));
    }
}



