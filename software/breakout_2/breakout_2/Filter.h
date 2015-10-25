/*
 * Filter Class
 * Kashev Dalmia - kashev.dalmia@gmail.com
 *
 * IEEE Arduino Workshop
 * github.com/ieee-uiuc/arduino-workshop
 */

#ifndef FILTER_H
#define FILTER_H

#include <Arduino.h>
#include <MCP4162.h>

/**
 * Class which wraps a resistor to set cutoff frequencies.
 */
class Filter
{
public:
    Filter(uint8_t slave_select_pin, bool manage_SPI_bus=false) :
        resistor(slave_select_pin, manage_SPI_bus)
    {
    };

    /**
     * Initialize everything.
     */
    void init()
    {
        resistor.init();
    };

    /**
     * Given a cutoff frequency in Hz, set the filter cutoff to the closest it
     * can be to that frequency. The supported frequency range is 160 Hz to
     * around 20e3 Hz.
     */
    void setCutoffFrequency(double freq)
    {
        double resistance = 1/(2 * PI * CAPACITANCE * freq);
        resistor.writeResistance(resistance);
    };

private:
    /**
     * The resistor object.
     */
    MCP4162 resistor;

    const double CAPACITANCE = 0.1e-6;

};

#endif
