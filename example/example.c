/*
 * Pico Linear Hall Effect Sensor
 * Linear Hall Effect (LHE) sensor library for Raspberry Pi Pico,
 * with calibration and smoothing.
 * By Turi Scandurra – https://turiscandurra.com/circuits
*/

#include <stdio.h>
#include <pico/stdlib.h>
#include "lhe.h"
#include "hardware/adc.h"

// LHE sensor on GPIO pin 26
#define ADC_PIN 26

int main() {
    stdio_init_all();

    // Initialize the ADC before continuing
    adc_init(); 

    // Create a new sensor instance
    lhe_sensor_t sensor = lhe_init(ADC_PIN);
    // Calibrate the sensor when no magnetic field is present, setting the zero point.
    int16_t offset = lhe_calibrate(&sensor);

    /* Optional settings
    // Set the sensor sensitivity
    lhe_set_sensitivity(14); // Default 18 mV/mT

    // Set the number of samples to get when smoothing the reading
    lhe_set_num_samples(20); // Default 10

    // Set the number of samples to get when calibrating the sensor
    lhe_set_calibration_samples(2000); // Default 1000
    */

    while (true) {
        // Get the raw sensor value
        uint16_t raw_value = lhe_get_raw(&sensor);

        // Get the offset-corrected, smoothed value
        int32_t calibrated_value = lhe_get(&sensor);

        // Get the sensor voltage in mV
        int16_t voltage = lhe_get_voltage(&sensor);

        // Get the sensor strength in G
        int16_t strength = lhe_get_strength(&sensor);

        // Print all the values
        printf("raw: %d\tcorr: %d\tmV: %d\tG: %d\n",\
                raw_value, calibrated_value, voltage, strength);

        sleep_ms(1000);
    }
}