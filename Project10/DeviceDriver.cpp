#include "DeviceDriver.h"
#include <stdexcept>
#include <windows.h>

class READException : public std::exception
{
public:
    explicit READException(char const* Messeage)
	: exception(Messeage)
    {
	    
    }
};


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int value = 0;

    value = m_hardware->read(address);
    for(int index=0;index<4;index++)
    {
        Sleep(200);
        if(value != m_hardware->read(address))
        {
            throw READException("wrongReadValue");
        }
    }

    return value;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}