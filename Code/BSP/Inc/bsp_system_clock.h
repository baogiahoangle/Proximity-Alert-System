#ifndef __BSP_SYSTEM_CLOCK_H
#define __BSP_SYSTEM_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_rcc.h" 

#define BSP_VERSION_1
#ifdef BSP_VERSION_1

void bsp_error_handler(void);
void bsp_system_clock_init(void);

#endif /* BSP_VERSION_1 */

#ifdef __cplusplus
}
#endif

#endif /* __BSP_SYSTEM_CLOCK_H */