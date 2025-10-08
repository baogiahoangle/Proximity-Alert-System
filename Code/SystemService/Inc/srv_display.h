/**
 * @file       srv_display.h
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-20-9
 * @author     Hoang Le
 * @brief      System Service layer for display.
 * @note       None.
 * @example    Refer to srv_display.c for implementation details.
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __SRV_DISPLAY_H
#define __SRV_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "bsp_st7735.h"

/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */

/* Public variables --------------------------------------------------------- */
/* Public APIs -------------------------------------------------------------- */

/**
 * @brief         Draws an initial background display on the ST7735.
 *
 * @param[in]     None
 *
 * @return        None
 *
 * @note          This function draws a magenta rectangle border and fills the screen
 *                with a gradient: blue on the left half and white on the right half.
 * @attention     Requires bsp_st7735_init() to be called first for the display to be ready.
 */
void srv_display();

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* __SRV_DISPLAY_H */

/* End of file -------------------------------------------------------------- */