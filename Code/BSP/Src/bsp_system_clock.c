/**
 * @file       bsp_system_clock.c
 * @copyright  Copyright (c) 2025
 * @license    
 * @version    1.0.0
 * @date       2025-27-9
 * @author     
 * @brief      Board support package for System Clock Configuration
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------------ */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------- */
#include "bsp_system_clock.h"

#ifdef BSP_VERSION_1
/* Public defines ----------------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Public implementations --------------------------------------------------- */
void bsp_error_handler(void)
{
  // __disable_irq();
  while (1)
  {
  }
}

void bsp_system_clock_init(void)
{
  rcc_config_72mhz();
}

/* -------------------------------------------------------------------------- */

#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
/* Public defines ----------------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------------- */
/* Public macros ------------------------------------------------------------ */

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */

/* Public implementations --------------------------------------------------- */
/* -------------------------------------------------------------------------- */

#endif /* BSP_VERSION_2 */


#ifdef __cplusplus
} /* extern "C" { */
#endif


/* End of file -------------------------------------------------------------- */