# Pico Linear Hall Effect Sensor
A small C library to read values from Linear Hall Effect Sensors like OH49E with a Raspberry Pi Pico (RP2040) or Raspberry Pi Pico 2 (RP2350), with calibration and smoothing.

The library can output the raw value of the sensor, a smoothed average, a bipolar force measurement, and the output voltage.

Multiple sensors can be managed simultaneously.


### Available functions
```c
/**
 * Initializes a new LHE sensor.
 *
 * @param GPIO The GPIO pin connected to the sensor (26, 27, or 28).
 * @return A new lhe_sensor_t instance.
 */
lhe_sensor_t lhe_init(uint8_t GPIO);

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
```

### Usage
An example application is provided.


### Version history
- 2024.12.01 - v1.0.0 - First release