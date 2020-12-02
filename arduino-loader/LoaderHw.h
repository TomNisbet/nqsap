#ifndef INCLUDE_LOADER_HW
#define INCLUDE_LOADER_HW

#include "Arduino.h"

/*****************************************************************************/
/*****************************************************************************/
/**
 * LoaderHw class
 *
 * Provides the device-specific interface to read and write registers and RAM.
 */


class LoaderHw
{
  public:
    LoaderHw(uint32_t size);
    void begin();
    void enable();
    void disable();
    bool isActive() { return mEnabled; }
    void clkPulse();
    void reset();
    const char * registerName(int registerNumber);
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t data);
    void transferRegister(uint8_t wReg, uint8_t rReg);
    bool writeData(const byte data[], uint32_t len, uint32_t address);
    byte readByte(uint32_t address);
    bool testHardware();

  protected:
    uint32_t mSize;                 // Size of the RAM, in bytes
    bool mEnabled;

    bool burnByte(byte value, uint32_t address);
    bool testRegister(unsigned reg, bool isRw);
    bool testMemory();
    bool testAlu();
    bool testAluOperation(uint8_t op, const char * opName, uint8_t a, uint8_t b);
    uint8_t aluCompute(uint8_t op, uint8_t a, uint8_t b);
    uint8_t localCompute(uint8_t op, uint8_t a, uint8_t b);
    bool testAdder();
    bool testAdderOperation(uint8_t a, uint8_t b);

    void selectWriteRegister(uint8_t reg);
    void selectReadRegister(uint8_t reg);
    void setDataBusMode(uint8_t mode);
    void setAddress(uint32_t address);
    byte readDataBus();
    void writeDataBus(byte data);
};

#endif  // #define INCLUDE_LOADER_HW
