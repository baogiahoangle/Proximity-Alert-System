/**
 * @file       driver_srf05.h
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-17-9
 * @author     Hoang Le
 * @brief      Driver for SRF05 Ultrasonic Distance Sensor
 * @note       This driver supports:
 *            - Triggering distance measurements
 *            - Reading echo pulse duration
 *            - Calculating distance in centimeters and inches
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __DRIVER_SRF05_H
#define __DRIVER_SRF05_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdbool.h>

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/**
 * @brief  SRF05 sensor configuration structure
 * @note   Contains GPIO port/pin for trigger and echo signals
 */
typedef struct
{
  GPIO_TypeDef *port;       /**< GPIO port for trigger and echo pins */
  uint16_t pin_trigger;     /**< GPIO pin for trigger signal */
  uint16_t pin_echo;        /**< GPIO pin for echo signal */
  TIM_HandleTypeDef *htim;  /**< Timer handle for measuring echo pulse duration */
}
srf05_t;

/**
 * @brief  Display operation status codes
 * @note   Used to track the success/failure of display operations
 */
typedef enum
{
  SRF05_OK          = 0x00U,  /**< Operation completed successfully */
  SRF05_ERROR       = 0x01U,  /**< Operation failed */
  SRF05_BUSY        = 0x02U,  /**< Display is busy processing previous command */
  SRF05_PARAM_ERROR = 0x03U,  /**< Invalid parameter provided */
  SRF05_TIM_ERROR   = 0x04U,  /**< Timer error occurred */
  SRF05_NOT_INIT    = 0x05U   /**< Display not initialized */
}
srf05_status_t;

/**
 * @brief  Display handler structure for tracking display state
 * @note   Maintains initialization status and current operation state
 */
typedef struct
{
  bool srf05_is_init;     /**< Set to true after successful initialization */
  srf05_status_t status;  /**< Current operation status */
  srf05_t *srf05;         /**< Pointer to SRF05 device configuration structure */
}
srf05_handler_t;

/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Public APIs -------------------------------------------------------------- */

/**
 * @brief         Initializes the SRF05.
 * 
 * @param[in]     srf05  Pointer to SRF05 configuration structure.
 * 
 * @return        srf05_status_t SRF05_OK if initialization is successful,
 *                               SRF05_PARAM_ERROR if invalid parameters are provided,
 *                               SRF05_TIM_ERROR if timer initialization fails,
 *                               SRF05_ERROR if any error occurs during initialization.
 * 
 * @note          Configures GPIO pins and timer for SRF05 operation.
 * @attention     Ensure the GPIO ports and pins are correctly defined in the srf05_t structure.
 */
srf05_status_t srf05_init(srf05_t *srf05);

/**
 * @brief         Triggers a distance measurement by sending a 10us pulse to the trigger pin.
 * 
 * @param[in]     srf05  Pointer to SRF05 configuration structure.
 * 
 * @return        srf05_status_t SRF05_OK if trigger pulse sent successfully,
 *                               SRF05_PARAM_ERROR if invalid parameters are provided,
 *                               SRF05_ERROR if any error occurs during triggering.
 * 
 * @note          This function sets the trigger pin high for 10 microseconds to initiate a measurement.
 * @attention     Ensure the SRF05 has been initialized before calling this function.
 */
srf05_status_t srf05_trigger(srf05_t *srf05);

/**
 * @brief         Reads the echo pulse duration in microseconds.
 * 
 * @param[in]     srf05  Pointer to SRF05 configuration structure.
 * 
 * @return        srf05_status_t SRF05_OK if duration read successfully,
 *                               SRF05_PARAM_ERROR if invalid parameters are provided,
 *                               SRF05_ERROR if any error occurs during reading,
 *                               SRF05_BUSY if measurement is still in progress.
 * 
 * @note          This function measures the time the echo pin stays high after triggering a measurement.
 * @attention     Ensure the SRF05 has been initialized and a trigger has been sent before calling this function.
 */
srf05_status_t srf05_get_distance_cm(srf05_t *srf05, float *distance_cm);
/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __DRIVER_SRF05_H */

/* End of file -------------------------------------------------------------- */