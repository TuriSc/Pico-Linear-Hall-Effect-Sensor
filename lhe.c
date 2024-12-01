/*
 * Pico Linear Hall Effect Sensor
 * Linear Hall Effect (LHE) sensor library for Raspberry Pi Pico,
 * with calibration and smoothing.
 * By Turi Scandurra – https://turiscandurra.com/circuits
*/

#include "lhe.h"
#include "hardware/adc.h"

// Number of samples to get when smoothing the reading
static uint16_t num_samples = 10;

// Number of samples to get when calibrating the sensor
static uint16_t num_calibration_samples = 1000;

// Sensitivity of the sensor in mV/mT
static uint16_t sensitivity = 18;

// Unique ID counter for sensors
static uint8_t next_id = 0;

/**
 * Initializes a new LHE sensor.
 *
 * @param GPIO The GPIO pin connected to the sensor (26, 27, or 28).
 * @return A new lhe_sensor_t instance.
 */
lhe_sensor_t lhe_init(uint8_t GPIO) {
    lhe_sensor_t sensor;
    sensor.id = next_id++; // Assign a unique ID to the sensor
    uint8_t adc_channel;
    switch(GPIO) {
        case 28:
        adc_channel = 2;
        break;
        case 27:
        adc_channel = 1;
        break;
        case 26:
        default:
        adc_channel = 0;
        break;
    }
    sensor.adc_channel = adc_channel;
    sensor.offset = 0;
    return sensor;
}

/**
 * Calibrates the sensor by taking multiple readings and calculating the offset.
 *
 * @param sensor The sensor to calibrate.
 * @return The calculated offset value.
 * @note Calibration assumes no magnetic field is present.
 *      Ensure a magnetically quiet environment for accurate results.
 */
int16_t lhe_calibrate(lhe_sensor_t* sensor) {
    adc_select_input(sensor->adc_channel);
    uint32_t sum = 0;
    for (int i = 0; i < num_calibration_samples; i++) {
        sum += adc_read();
    }
    sensor->offset = (int16_t)(sum / num_calibration_samples);
    return sensor->offset;
}

/**
 * Gets the smoothed, offset-corrected reading from the sensor.
 *
 * @param sensor The sensor to read from.
 * @return The smoothed, offset-corrected reading.
 */
 int32_t lhe_get(lhe_sensor_t* sensor) {
    adc_select_input(sensor->adc_channel);
    uint32_t sum = 0;
    for (int i = 0; i < num_samples; i++) {
        sum += adc_read();
    }
    uint16_t adc_value = (uint16_t)(sum / num_samples);
    return (adc_value - sensor->offset);
}

/**
 * Gets the raw, unprocessed reading from the sensor.
 *
 * @param sensor The sensor to read from.
 * @return The raw reading.
 */
uint16_t lhe_get_raw(lhe_sensor_t* sensor) {
    adc_select_input(sensor->adc_channel);
    return adc_read(); // Take a single reading
}

/**
 * Gets the voltage reading from the sensor in millivolts.
 *
 * @param sensor The sensor to read from.
 * @return The voltage reading in millivolts.
 */
int16_t lhe_get_voltage(lhe_sensor_t* sensor) {
    // Get the smoothed, offset-corrected value
    int32_t adc_value = lhe_get(sensor);
    // Quick calculation equal to adc_value * 3300 / 4095;
    return (adc_value * 825) >> 10; // Expressed in mV
}

/**
 * Gets the magnetic field strength reading from the sensor in milliteslas.
 *
 * @param sensor The sensor to read from.
 * @return The magnetic field strength reading in milliteslas.
 */
int16_t lhe_get_strength(lhe_sensor_t* sensor) {
    // Get the sensor voltage
    int32_t adc_mv = lhe_get_voltage(sensor);
    return (adc_mv / sensitivity);
}

/**
 * Sets the sensitivity of the sensor in mV/mT.
 *
 * @param s The new sensitivity value.
 */
void lhe_set_sensitivity(uint16_t s) {
    sensitivity = s;
}

/**
 * Sets the number of samples to take when smoothing the reading.
 *
 * @param n The new number of samples.
 */
void lhe_set_num_samples(uint16_t n) {
    num_samples = n;
}
