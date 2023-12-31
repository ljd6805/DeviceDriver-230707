#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project10/DeviceDriver.cpp"
using namespace testing;

class MockFlashMemory:public FlashMemoryDevice
{
public:
	//unsigned char read(long address) override;
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void , write, (long address, unsigned char data), (override));
};


TEST(TestDeviceDriver, Driver_WriteOk) {
	MockFlashMemory mock;

	EXPECT_CALL(mock, read)
		.Times(1)
		.WillOnce(Return(0xff));

	EXPECT_CALL(mock, write)
		.Times(1);

	DeviceDriver testdriver(&mock);

	long inputAddress = 0x00;
	int data = 0x1234;

	EXPECT_NO_THROW(testdriver.write(inputAddress, data));
	
}

TEST(TestDeviceDriver, Driver_WriteException) {
	MockFlashMemory mock;

	EXPECT_CALL(mock, read)
		.Times(1)
		.WillOnce(Return(0x1f));
		
	DeviceDriver testdriver(&mock);

	long inputAddress = 0x00;
	int data = 0x1234;

	EXPECT_THROW(testdriver.write(inputAddress, data),WRITEException);

}

TEST(TestDeviceDriver, Driver_ReadOk) {
	MockFlashMemory mock;

	EXPECT_CALL(mock, read)
		.Times(5)
		.WillRepeatedly(Return((unsigned char)0xff));

	DeviceDriver testdriver(&mock);

	long inputAddress = 0x1234;
	int expected = 0xff;
	int actual = testdriver.read(inputAddress);

	EXPECT_EQ(expected, actual);

}

TEST(TestDeviceDriver, Driver_ReadException) {
	MockFlashMemory mock;

	EXPECT_CALL(mock, read)
		.Times(3)
		.WillOnce(Return((unsigned char)0xf1))
		.WillOnce(Return((unsigned char)0xf1))
		.WillRepeatedly(Return((unsigned char)0xff));
		

	DeviceDriver testdriver(&mock);
	long inputAddress = 0x1234;
	
	EXPECT_THROW(testdriver.read(inputAddress), READException);

}