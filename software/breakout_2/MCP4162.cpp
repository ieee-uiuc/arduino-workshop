/**
 * MCP4162 Arduino Library
 * Kashev Dalmia - kashev.dalmia@gmail.com
 *
 * IEEE Arduino Workshop
 * github.com/ieee-uiuc/arduino-workshop
 */

#include "MCP4162.h"

/**
 * Constructor. Sets interal parameters.
 */
MCP4162::MCP4162(uint8_t slave_select_pin, bool manage_SPI_bus) :
    pin_SS(slave_select_pin)
    manage_SPI(manage_SPI_bus)
{
}

/**
 * Initialization of resistor. To be called during the Arduino setup(). SPI is
 * usually left unitinialized, so that this class can be used with other devices
 * on the SPI bus.
 */
void MCP4162::init()
{
    /*
     * Set up chip select pin, and set it to inactive.
     */
    pinMode(pin_SS, OUTPUT);
    digitalWrite(pin_SS, HIGH);

    if (manage_SPI)
    {
        SPI.begin();
        SPI.setBitOrder(MSBFIRST);
    }
}

/**
 * Given some parameters, return the 16 bit command to send to the device.
 */
uint16_t MCP4162::getLongCommand(
    const uint8_t addr, const uint8_t cmd, const uint8_t val)
{
    uint16_t full_long_cmd = 0x00;
    full_long_cmd |= uint16_t(addr) << 12;
    full_long_cmd |= uint16_t(cmd) << 10;
    full_long_cmd |= uint16_t(val);
    return full_long_cmd;
}

/**
 * Set the value to the rheostat.
 */
void MCP4162::write(uint8_t val)
{
    uint16_t cmd = getLongCommand(ADDR_VOLATILE_WIPER, CMD_WRITE, val);
    SPI.transfer16(cmd)
}
