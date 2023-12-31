#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    bool IsWritable(long address);
    FlashMemoryDevice* m_hardware;
    int MAXREADCOUNT = 5;
    int SLEEPTIME_FOR_READ = 200;
    int WRITABLE = 0xff;
};