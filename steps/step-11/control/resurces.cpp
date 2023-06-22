#include "resurces.h"

std::unique_ptr<Resurces> ResurcesHolder::res = nullptr;


void Resurces::create()
{
    m.emplace_back(new Bunner(
    {   L"|-------------------|",
        L"|                   |",
        L"|      ЯTeTRis      |",
        L"|    (xlat-code)    |",
        L"|       2023©       |",
        L"|                   |",
        L"|-------------------|"
    }));

    m.emplace_back(new Bunner(
    {   L"|-----------------------|",
        L"|                       |",
        L"|       GAME OVER!      |",
        L"|                       |",
        L"|-----------------------|"
    }));

    m.emplace_back(new Bunner(
    {   L"########################",
        L"#                      #",
        L"#   Program FINISHED!  #",
        L"#                      #",
        L"########################"
    }));

    m.emplace_back(new Bunner(
    {   L"###<-START-MENU->###",
        L"#                  #",
        L"#                  #",
        L"#  1. Один игрок   #",
        L"#  2. Два  игрока  #",
        L"#  3. ...          #",
        L"#                  #",
        L"#  ...             #",
        L"#                  #",
        L"#  ESCAPE  ВЫХОД   #",
        L"#                  #",
        L"####################"
    }));

    m.emplace_back(new Bunner(
    {   L"/////////--TODO--/////////",
        L"/                        /",
        L"/  ... в разработке ...  /",
        L"/                        /",
        L"/////////--2023--/////////"
    }));

    if(m.size() != Resurces::E_SIZE)
    {   throw(ERROR_EXCEPTION_MESS("Amount resurces!"));
    }
}



