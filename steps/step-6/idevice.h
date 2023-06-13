#ifndef IDEVICE_H
#define IDEVICE_H

#include <string>
#include <memory>

struct       IDevice
{
    virtual ~IDevice() {}

    virtual  IDevice& operator<<(std::wstring_view str) = 0;
    virtual  IDevice& operator<<(std:: string_view str) = 0;
    virtual  IDevice& operator<<(char              c  ) = 0;
    virtual  void pause_press_enter  (std::wstring_view str) = 0;
    virtual  void set_cursor_to_start() = 0;

    static   std::unique_ptr<IDevice> p;

    static void create_device_console();

    std::wstring_view mode;
};

#define DEVICE (*IDevice::p)

#endif // IDEVICE_H
