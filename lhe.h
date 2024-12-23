/*
 * @file lhe.h
 * @brief Linear Hall Effect (LHE) sensor library for Raspberry Pi Pico,
 * with calibration and smoothing.
 *
 * @author Turi Scandurra – https://turiscandurra.com/circuits
*/

#ifndef LHE_H_
#define LHE_H_

#include <pico/stdlib.h>

/**
 * @struct lhe_sensor_t
 * @brief Linear Hall Effect sensor structure
 *
 */
typedef struct {
    /**
     * @var id
     * @brief Demultiplexer channel for this sensor
     */
    uint8_t id;

    /**
     * @var adc_channel
     * @brief ADC channel for this sensor
     */
    uint8_t adc_channel;

    /**
     * @var offset
     * @brief Offset value for this sensor
     */
    int16_t offset;
} lhe_sensor_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup Initialization Initialization functions
 * @{
 */

/**
 * Initializes a new LHE sensor.
 *
 * @param GPIO The GPIO pin connected to the sensor (26, 27, or 28).
 * @return A new lhe_sensor_t instance.
 */
lhe_sensor_t lhe_init(uint8_t GPIO);

/**
 * @}
 */

/**
 * @defgroup Calibration Calibration functions
 * @{
 */

/**
 * Calibrates the sensor by taking multiple readings and calculating the offset.
 *
 * @param sensor The sensor to calibrate.
 * @return The calculated offset value.
 * @note Calibration assumes no magnetic field is present.
 *      Ensure a magnetically quiet environment for accurate results.
 */
int16_t lhe_calibrate(lhe_sensor_t* sensor);

/**
 * @}
 */

/**
 * @defgroup Reading Reading functions
 * @{
 */

/**
 * Gets the smoothed, offset-corrected reading from the sensor.
 *
 * @param sensor The sensor to read from.
 * @return The smoothed, offset-corrected reading.
 */
int32_t lhe_get(lhe_sensor_t* sensor);

/**
 * Gets the raw, unprocessed reading from the sensor.
 *
 * @param sensor The sensor to read from.
 * @return The raw reading.
 */
uint16_t lhe_get_raw(lhe_sensor_t* sensor);

/**
 * Gets the voltage reading from the sensor in millivolts.
 *
 * @param sensor The sensor to read from.
 * @return The voltage reading in millivolts.
 */
int16_t lhe_get_voltage(lhe_sensor_t* sensor);

/**
 * Gets the magnetic field strength reading from the sensor in milliteslas.
 *
 * @param sensor The sensor to read from.
 * @return The magnetic field strength reading in milliteslas.
 */
int16_t lhe_get_strength(lhe_sensor_t* sensor);

/**
 * @}
 */

/**
 * @defgroup Configuration Configuration functions
 * @{
 */

/**
 * Sets the sensitivity of the sensor in mV/mT.
 *
 * @param s The new sensitivity value.
 */
void lhe_set_sensitivity(uint16_t s);

/**
 * Sets the number of samples to take when smoothing the reading.
 *
 * @param n The new number of samples.
 */
void lhe_set_num_samples(uint16_t n);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

