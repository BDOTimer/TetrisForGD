///----------------------------------------------------------------------------|
/// device_console реализация.
///----------------------------------------------------------------------------:
#include "idevice.h"
#include <iostream>

///----------------------------------------------------------------------------|
/// win.
///------------------------------------------------------------------------ win:
namespace win
{
    #ifdef __WIN32__
    #include <windows.h>
    void set_cursor_to_start()
    {   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    }

    void carret_visible(bool visible = false)
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

        SetConsoleTitleW(L"ЯTeTRis-2023");
    }

    #else
    void set_cursor_to_start()
    {   std::system("cls");
    }
    void carret_visible(bool visible = false){}
    #endif
}

///----------------------------------------------------------------------------|
/// console.
///-------------------------------------------------------------------- console:
namespace console
{
    struct  DeviceConsole : public IDevice
    {       DeviceConsole()
            {   mode = L"DeviceConsole";

                win::carret_visible();
            }

           ~DeviceConsole()
            {
            }


        IDevice& operator<<(std::wstring_view str)
        {   std::wcout << str;
            return *this;
        }

        IDevice& operator<<(std::string_view str)
        {   std::cout << str;
            return *this;
        }

        IDevice& operator<<(char   c)
        {   std::wcout << (wchar_t)c;
            return *this;
        }

        void pause_press_enter(std::wstring_view str = L"")
        {   std::wcout << str;
            std::cin.get   ();
        }

        void set_cursor_to_start(){ win::set_cursor_to_start(); }
    };

    void testclass_IDevice()
    {
        IDevice::create_device_console();

        (*IDevice::p) << L"testclass_IDevice(): DeviceConsole ЗАПУЩЕН!\n";
    }
}

std::unique_ptr<IDevice> IDevice::p = nullptr;

void IDevice::create_device_console()
{   p = std::make_unique<console::DeviceConsole>();
}

namespace console
{
    void testclass_IDevice();
}

