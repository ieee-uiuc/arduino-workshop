/*
 * Filter Class
 * Kashev Dalmia - kashev.dalmia@gmail.com
 *
 * IEEE Arduino Workshop
 * github.com/ieee-uiuc/arduino-workshop
 */

#ifndef BREAKOUT_TWO_SHIELD_H
#define BREAKOUT_TWO_SHIELD_H

#include <Arduino.h>
#include "Filter.h"

class BreakoutTwoShield
{
public:
    /**
     * The appropriate pin for the chip select of the high pass filter is 6, and
     * the low pass filter is 7. We cannot declare these in member variables
     * because of the way that Arduino initializer lists are broken.
     */
    BreakoutTwoShield() :
        high_pass(6),
        low_pass(7)
    {
    };

    /**
     * Initialize the filters.
     */
    void init()
    {
        high_pass.init();
        low_pass.init();
    }

    /**
     * Set the cutoff frequency of the high pass filter.
     */
    void setHighPassCutoffFrequency(double freq)
    {
        high_pass.setCutoffFrequency(freq);
    };

    /**
     * Set the cutoff frequency of the low pass filter.
     */
    void setLowPassCutoffFrequency(double freq)
    {
        low_pass.setCutoffFrequency(freq);
    };

    /**
     * Read the state of the buttons, and return a packed version of the state.
     *
     * +---------+----------+----------+
     * | retval  | Button 1 | Button 2 |
     * +---------+----------+----------+
     * | 0x00    | OFF      | OFF      |
     * | 0x01    | ON       | OFF      |
     * | 0x02    | OFF      | ON       |
     * | 0x03    | ON       | ON       |
     * +---------+----------+----------+
     */
    uint8_t readButtons()
    {
        uint8_t button_1_state = digitalRead(BUTTON_1_PIN);
        uint8_t button_2_state = digitalRead(BUTTON_2_PIN);
        return (button_1_state | (button_2_state << 1));
    }

    /**
     * Minimum and Maxium frequency cutoffs in Hz. These are put in the audio
     * range to make changes easy to hear.
     */
    const double MAX_FREQ_CUTOFF = 1e3;
    const double MIN_FREQ_CUTOFF = 0;

private:

    /**
     * The objects representing the filters on the shield.
     */
    Filter high_pass;
    Filter low_pass;

    /**
     * The pins of the buttons.
     */
    const uint8_t BUTTON_1_PIN = 4;
    const uint8_t BUTTON_2_PIN = 5;
};

#endif
