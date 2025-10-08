/**
 * @file       bsp_srf05.h
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      Board support package for SRF05 Ultrasonic Distance Sensor
 * @note       This BSP provides an abstraction layer for the SRF05 driver,
 *             handling hardware-specific initializations (GPIO, Timer) and
 *             exposing simplified sensor control functions.
 * @example    Refer to application layer for usage examples.
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __BSP_SRF05_H
#define __BSP_SRF05_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "driver_srf05.h"

#define BSP_VERSION_1

#ifdef BSP_VERSION_1
/* Public defines ----------------------------------------------------------- */
/* GPIO Configuration */
#define SRF05_GPIO_PORT                  GPIOB
#define SRF05_GPIO_PIN_TRIGGER           GPIO_PIN_5
#define SRF05_GPIO_PIN_ECHO              GPIO_PIN_6

/* Timer Configuration */
#define SRF05_HTIM                       htim1
#define SRF05_TIM_INSTANCE               TIM1

#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
/* Public defines ----------------------------------------------------------- */
/* GPIO Configuration */
#define SRF05_GPIO_PORT                  GPIOB
#define SRF05_GPIO_PIN_TRIGGER           GPIO_PIN_5
#define SRF05_GPIO_PIN_ECHO              GPIO_PIN_6

/* Timer Configuration */
#define SRF05_HTIM                       htim1
#define SRF05_TIM_INSTANCE               TIM1

#endif /* BSP_VERSION_2 */

/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */

#define BSP_SRF05_CHECK_HANDLER_INIT(handler) \
    do { \
        if (!(handler)->srf05_is_init || (handler)->status != SRF05_OK) { \
            return SRF05_NOT_INIT; \
        } \
        (handler)->status = SRF05_BUSY; \
    } while(0)

#define BSP_SRF05_CHECK_STATUS(handler, function) \
    do { \
           srf05_status_t status = (function); \
           (handler)->status = status; \
           return (status); \
    } while(0)

#define BSP_SRF05_INIT_CHECK(func_call) \
    do { \
        srf05_status_t status = (func_call); \
        if (status != SRF05_OK) { \
            return status; \
        } \
    } while(0)

/* Public variables --------------------------------------------------------- */
/* Public APIs -------------------------------------------------------------- */

/**
 * @brief         Initializes GPIO pins for SRF05 operation.
 * 
 * @return        srf05_status_t SRF05_OK if GPIOs initialized successfully,
 *                               SRF05_ERROR if any error occurs during initialization.
 * 
 * @note          Configures trigger pin as output and echo pin as input.
 */
srf05_status_t bsp_srf05_gpio_init();

/**
 * @brief         Initializes Timer for SRF05 echo pulse measurement.
 * 
 * @return        srf05_status_t SRF05_OK if timer initialized successfully,
 *                               SRF05_TIM_ERROR if timer initialization fails.
 * 
 * @note          Configures the timer in input capture mode to measure echo pulse width.
 */
srf05_status_t bsp_srf05_tim_init();

/**
 * @brief         This function maps the hardware resources (GPIO, Timer) to the
 *                SRF05 driver structure.
 *
 * @param[in]     None
 *
 * @return        srf05_status_t SRF05_OK if initialization is successful,
 *                               SRF05_ERROR if any error occurs during initialization.
 *
 * @note          None
 */
srf05_status_t bsp_srf05_init();

/**
 * @brief         Triggers a distance measurement by sending a 1ms pulse to the trigger pin.
 * 
 * @param[in]     None
 * 
 * @return        srf05_status_t SRF05_OK if trigger pulse sent successfully,
 *                               SRF05_ERROR if any error occurs during triggering.
 * 
 * @note          This function sets the trigger pin high for 1 millisecond to initiate a measurement.
 * @attention     Ensure the SRF05 has been initialized before calling this function.
 */
srf05_status_t bsp_srf05_trigger();

/**
 * @brief         Reads the echo pulse duration in microseconds.
 * 
 * @param[in]     None
 * @param[out]    distance_cm  Pointer to store the calculated distance in centimeters.
 * 
 * @return        srf05_status_t SRF05_OK if distance read successfully,
 *                               SRF05_ERROR if any error occurs during reading.
 *
 * @note          This function calculates the distance based on the echo pulse duration
 *                and the speed of sound.
 * @attention     Ensure the SRF05 has been initialized and a trigger has been sent before calling this function.
 */
srf05_status_t bsp_srf05_get_distance_cm(float *distance_cm);
/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __BSP_SRF05_H */

/* End of file -------------------------------------------------------------- */