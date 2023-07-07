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

class WRITEException : public std::exception
{
public:
    explicit WRITEException(char const* Messeage)
        : exception(Messeage)
    {

    }
};


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int value =  (int)m_hardware->read(address);

    for(int index=0;index< MAXREADCOUNT-1;index++)
    {
        Sleep(SLEEPTIME_FOR_READ);
        if(value != (int)m_hardware->read(address))
        {
            throw READException("wrongReadValue");
        }
    }

    return value;
}

void DeviceDriver::write(long address, int data)
{
    if (IsWritable(address) == false) throw WRITEException("WrongAddress");
        m_hardware->write(address, (unsigned char)data);
}

bool DeviceDriver::IsWritable(long address)
{
	return ((int)(m_hardware->read(address)) == WRITABLE);
	
}
