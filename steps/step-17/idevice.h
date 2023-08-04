#ifndef IDEVICE_H
#define IDEVICE_H

#include <string>
#include <memory>
#include <sstream>

struct  IDeviceT
{

    template<typename T>
    IDeviceT& operator<<(const T a)
    {   ws << a;
        return *this;
    }

    IDeviceT& operator<<(const char a)
    {
        if(a == '\n') endl ();
        else          ws << a;
        return *this;
    }

    static void test()
    {    IDeviceT   T;
                    T << L"IDeviceT::test(): " << 2023 << T.endl();
    }

private:
    std::wstring   endl();
    std::wstringstream ws;
};

extern IDeviceT oIDeviceT;

#define l(v) oIDeviceT << #v << " = " << (v) << '\n';

///----------------------------------------------------------------------------|
/// IDevice.
///-------------------------------------------------------------------- IDevice:
struct       IDevice
{
    virtual ~IDevice() {}

    virtual  IDevice& operator>>(std::wstring&     str) = 0;
    virtual  IDevice& operator<<(std::wstring_view str) = 0;
    virtual  IDevice& operator<<(std:: string_view str) = 0;
    virtual  IDevice& operator<<(char              c  ) = 0;
    virtual  IDevice& operator<<(wchar_t           c  ) = 0;
    virtual  IDevice& operator<<(unsigned          n  ) = 0;

    virtual  void pause_press_enter  (std::wstring_view str) = 0;
    virtual  void set_cursor_to_start() = 0;
    virtual  void clear_screen       () = 0;

    static   std::unique_ptr<IDevice> p;

    static void create_device_console();

    std::wstring_view mode;
};

#define DEVICE (*IDevice::p)

#endif // IDEVICE_H
