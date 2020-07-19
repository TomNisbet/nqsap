/*****************************************************************************/
/*****************************************************************************/
/**
 *
 * XMODEM CRC Communication
 *
 * Simple implementation of read and write using XMODEM CRC.  This is tied directly to
 * the LoaderHw code, so the receive function writes the data to the target RAM as each
 * packet is received.  The complete file is not kept in Arduino memory.
 */
#ifndef INCLUDE_CONFIGURE_H
#define INCLUDE_CONFIGURE_H

#include "Arduino.h"
#include "Configure.h"

//class PromDevice;
class CmdStatus;

class XModem
{
  public:
    XModem(LoaderHw & hw, CmdStatus & cs) : loaderHw(hw), cmdStatus(cs) {}
    uint32_t ReceiveFile(uint32_t address);
    bool SendFile(uint32_t address, uint32_t fileSize);
    void Cancel();

  private:
    enum
    {
        // XMODEM control characters.
        XMDM_SOH = 0x01,
        XMDM_EOT = 0x04,
        XMDM_ACK = 0x06,
        XMDM_NAK = 0x15,
        XMDM_CAN = 0x18,
        XMDM_ESC = 0x1b,
        XMDM_CRC = 'C'
    };
    enum
    {
        // Misc constants for XMODEM.
        PKTLEN = 128
    };

    LoaderHw & loaderHw;
    CmdStatus & cmdStatus;

    int GetChar(int msWaitTime = 3000);
    uint16_t UpdateCrc(uint16_t crc, uint8_t data);
    bool StartReceive();
    bool ReceivePacket(uint8_t buffer[], unsigned bufferSize, uint8_t seq, uint32_t destAddr);
    void SendPacket(uint32_t address, uint8_t seq);
};

#endif // #define INCLUDE_CONFIGURE_H
