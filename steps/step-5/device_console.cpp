///----------------------------------------------------------------------------|
/// device_console реализация.
///----------------------------------------------------------------------------:
#include "idevice.h"
#include <iostream>

namespace console
{
    struct  DeviceConsole : public IDevice
    {       DeviceConsole()
            {   mode = L"DeviceConsole";
            }

           ~DeviceConsole()
            {  //if(IDevice::p != nullptr) delete IDevice::p;
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

        void pause_press_enter(std::wstring_view str=L"")
        {   std::wcout << str;
            std::cin.get   ();
        }
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

