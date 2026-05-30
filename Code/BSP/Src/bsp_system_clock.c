#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_system_clock.h"

#ifdef BSP_VERSION_1
void bsp_error_handler(void)
{
  while (1)
  {
  }
}

void bsp_system_clock_init(void)
{
  rcc_config_72mhz();
}

#endif /* BSP_VERSION_1 */

#ifdef BSP_VERSION_2
#endif /* BSP_VERSION_2 */

#ifdef __cplusplus
}
#endif