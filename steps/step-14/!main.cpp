/// Тетрис на коленке.
///----------------------------------------------------------------------------|
/// C++17
/// исходник в utf-8
///----------------------------------------------------------------------------:

#include "tests.h"

void foo()
{
    std::ofstream f("123.txt");
    std::string s;
    for(char c = char(128); c < char(256); ++c)
    {
        f << c << std::endl;
    }
}


///----------------------------------------------------------------------------|
/// Старт.
///----------------------------------------------------------------------------:
int main()
{
    setlocale(0, "");
    srand((unsigned)time(0));

    IDevice::create_device_console();

    ///------------------------------//
    /// DEVICE << L"ЯTeTRis-2023\n"; //
    ///------------------------------//

    try
    {   tests();
    }
    catch(const CustomException& e)
    {   DEVICE << e.what();
    }

    DEVICE << "TETRIS FINISH!\n";
    DEVICE.pause_press_enter(L"PRESS ENTER\n");
}
