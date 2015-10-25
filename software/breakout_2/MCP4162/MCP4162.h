/*
 * MCP4162 Arduino Library
 * Kashev Dalmia - kashev.dalmia@gmail.com
 *
 * IEEE Arduino Workshop
 * github.com/ieee-uiuc/arduino-workshop
 */


#ifndef MCP4162_H
#define MCP4162_H

#include <Arduino.h>
#include <SPI.h>

/**
 * Controller for a Microchip MCP4162 single digital rheostat, controllable via
 * SPI. Note that the standard Arduino Uno SPI pins are:
 *
 * MOSI - 11
 * MISO - 12
 * SCK  - 13
 * SS   - Up to User.
 *
 * Everything but SS is handled by the Arduino SPI library.
 *
 * Datasheet @ http://ww1.microchip.com/downloads/en/DeviceDoc/22059b.pdf
 */
class MCP4162
{
public:
    MCP4162(uint8_t slave_select_pin, bool manage_SPI_bus=false);

    void init();
    void writeResistance(double resistance);

private:

    uint8_t get_command_byte(const uint8_t addr, const uint8_t cmd);
    void write_byte(uint8_t val);

    /**
     * Slave select pin for this particular resistor. Note that this pin must
     * be unique to the resistor, and will be put in output mode during init().
     * For this part, chip select is active-low.
     */
    uint8_t pin_SS;

    /**
     * True if this device should manage the SPI bus itself, meaning making
     * calls to SPI.init(), etc. Only set to true if there are no other devices
     * on the SPI bus.
     */
    bool manage_SPI;


    /*
     * CONSTANTS
     */

    /**
     * This particular part has 256 steps of resistance, over 0 to 10K Ohms
     */
    const int NUM_STEPS = 256;
    const double MAX_RESISTANCE = 10e3; // Ohms

    /**
     * The addresss of the volatile memory which sets the rheostat wiper. See
     * the memory map in Datasheet Table 4-1. Note that since this part is a
     * single rheostat, addresses for the second rheostat are excluded.
     */
    const uint8_t ADDR_VOLATILE_WIPER     = 0x00;
    const uint8_t ADDR_NON_VOLATILE_WIPER = 0x02;
    const uint8_t ADDR_STATUS_REGISTER    = 0x05;

    /**
     * Commands are two bits wide; see Datasheet Table 7-1.
     */
    const uint8_t CMD_READ  = 0x03;
    const uint8_t CMD_WRITE = 0x00;
    const uint8_t CMD_INC   = 0x01;
    const uint8_t CMD_DEC   = 0x02;

    /**
     * SPI Settings for this device.
     */
    const int MAX_SCLK_FREQUENCY = 10e6;
    const SPISettings SPI_SETTINGS = SPISettings(
        MAX_SCLK_FREQUENCY, MSBFIRST, SPI_MODE3);

};

#endif
