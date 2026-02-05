/**
 * @file       app_processor.h
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      Application layer for controlling a distance sensing and display system.
 * @note       This file defines the application's states, handler structure, and public APIs.
 * @example    Refer to app_processor.c for implementation details.
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __APP_PROCESSOR_H
#define __APP_PROCESSOR_H 

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "bsp_system_clock.h"
#include "bsp_st7735.h"
#include "bsp_srf05.h"
#include "bsp_led.h"

/* Public enumerate/structure ----------------------------------------------- */
typedef enum
{
  APP_OK            = 0x00U, /**< Operation completed successfully */
  APP_ERROR         = 0x01U, /**< Operation failed */
  APP_BUSY          = 0x02U, /**< Operation is busy processing previous command*/
  APP_NOT_INIT      = 0x03U  /**< Operation failed because application is not initialized */
}
app_status_t;

typedef struct
{
  bool is_init;              /**< Indicates if the application is initialized */
  app_status_t status;       /**< Current operation status */
}
app_handler_t;

/* Public macros ------------------------------------------------------------ */

#define APP_CHECK_HANDLER_INIT(handler) \
    do { \
        if (!(handler)->is_init || (handler)->status != APP_OK) { \
            return APP_NOT_INIT; \
        } \
    } while(0)

/* Public APIs -------------------------------------------------------------- */

/**
 * @brief         Initializes the necessary peripherals for Application control.
 * @param[in]     None
 * @return        app_status_t
 * @note          This function configures the System Clock and peripherals.
 */
app_status_t app_processor_init();

/**
 * @brief         Updates the host's position on the display and controls an LED based on the position.
 * @param[in]     x The x-coordinate for the host's current position (0-127).
 * @return        app_status_t
 * @note          If 'x' is less than 64 (left half), it indicates a "DANGEROUS" zone and turns the LED on.
 *                Otherwise, it indicates a "SAFE" zone and turns the LED off.
 */

app_status_t app_processor_host(uint8_t x);

/**
 * @brief         Performs the main operation of the application, sensing distance and updating the host.
 * @param[in]     None
 * @return        app_status_t 
 * @note          This function reads the distance from the SRF05 sensor, scales it,
 *                and then calls app_processor_host() to update the display and LED.
 */
app_status_t app_processor_operates();

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __APP_PROCESSOR_H */

/* End of file -------------------------------------------------------------- */