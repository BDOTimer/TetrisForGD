
#include "resurces.h"
#include "toplist.h"
#include "scenaries.h"
//#include "../config.h"

std::unique_ptr<Resurces> ResurcesHolder::res = nullptr;

const Config         cfg_default;
      Config const* cfg = &cfg_default;

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
        L"#  3. Топлист      #",
        L"#  4. Сценарий     #",
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

    m.emplace_back(new Toplist  );
    m.emplace_back(new Scenaries);

    if(m.size() != Resurces::E_SIZE)
    {   throw(ERROR_EXCEPTION_MESS("Amount resurces!"));
    }
}



