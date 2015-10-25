/*
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
    pin_SS(slave_select_pin),
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
     * Set up chip select pin, and set it to inactive. This select line is
     * active low.
     */
    pinMode(pin_SS, OUTPUT);
    digitalWrite(pin_SS, HIGH);

    if (manage_SPI)
    {
        SPI.begin();
    }
}

/**
 * Given some parameters, return the 8 bit command byte to send to the device.
 */
uint8_t MCP4162::get_command_byte(const uint8_t addr, const uint8_t cmd)
{
    uint8_t cmd_byte = 0x00;
    cmd_byte |= addr << 4;
    cmd_byte |= cmd << 2;
    return cmd_byte;
}

/**
 * Set the byte value to the rheostat.
 */
void MCP4162::write_byte(uint8_t val)
{
    uint8_t cmd = get_command_byte(ADDR_VOLATILE_WIPER, CMD_WRITE);
    SPI.beginTransaction(SPI_SETTINGS);
    digitalWrite(pin_SS, LOW);
    SPI.transfer(cmd);
    SPI.transfer(val);
    digitalWrite(pin_SS, HIGH);
    SPI.endTransaction();
}

/**
 * Convert a frequency to the byte that should be sent, then send it. The
 * relationship between the resistance and byte is:
 * val = 256 * resistance / 10K ohms
 * See Equation 5-1 in the datasheet.
 */

void MCP4162::writeResistance(double resistance)
{

    uint8_t val = NUM_STEPS * (resistance / MAX_RESISTANCE);
    write_byte(val);
}
