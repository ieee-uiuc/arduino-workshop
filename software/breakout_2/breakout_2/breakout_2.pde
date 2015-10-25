/*
 * Breakout II Sketch
 * Kashev Dalmia - kashev.dalmia@gmail.com
 *
 * IEEE Arduino Workshop
 * github.com/ieee-uiuc/arduino-workshop
 */

#include <SPI.h>
#include <MCP4162.h>
#include "Filter.h"
#include "BreakoutTwoShield.h"


/**
 * Frequency stepping constants.
 */
const double num_freq_steps = 20;
const double freq_percentage = 1/num_freq_steps;


/**
 * The object representing the shield.
 */
BreakoutTwoShield shield;

/**
 * The persistent cutoff frequencies of the filters.
 */
double HPF_cutoff = shield.MIN_FREQ_CUTOFF;
double LPF_cutoff = shield.MAX_FREQ_CUTOFF;

/**
 * Persistant variable to store button state.
 */
uint8_t button_state = 0x00;
/**
 * Button debouncing variables.
 */
bool debounced = true;
int debouncing_timout = 0;
const int MAX_DEBOUNCING_TIMEOUT = 500;


void setup()
{
    Serial.begin(9600);

    SPI.begin();
    shield.init();

    shield.setHighPassCutoffFrequency(HPF_cutoff);
    shield.setLowPassCutoffFrequency(LPF_cutoff);

    Serial.println("Init Finished!");
}

void loop()
{
    /*
     * Read the button state, and increase or decrese the cutoff freuencies.
     */
    button_state = shield.readButtons();
    if (debounced && button_state == 0x01)
    {
        /*
         * Increase the cutoff.
         */
        LPF_cutoff += freq_percentage * shield.MAX_FREQ_CUTOFF;
        LPF_cutoff = min(LPF_cutoff, shield.MAX_FREQ_CUTOFF);
        shield.setLowPassCutoffFrequency(LPF_cutoff);
        Serial.print("New cutoff frequency: ");
        Serial.println(LPF_cutoff);
        debounced = false;
    }
    else if (debounced && button_state == 0x02)
    {
        /*
         * Decrease the cutoff.
         */
        LPF_cutoff -= freq_percentage * shield.MAX_FREQ_CUTOFF;
        LPF_cutoff = max(LPF_cutoff, shield.MIN_FREQ_CUTOFF);
        Serial.print("New cutoff frequency: ");
        Serial.println(LPF_cutoff);
        shield.setLowPassCutoffFrequency(LPF_cutoff);
        debounced = false;
    }
    else if (button_state == 0x00)
    {
        if (!debounced)
        {
            debouncing_timout += 1;
            if (debouncing_timout >= MAX_DEBOUNCING_TIMEOUT)
            {
                debounced = true;
                debouncing_timout = 0;
            }
        }
    }

}
