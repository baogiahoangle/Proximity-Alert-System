#include "main.h"
#include "app_processor.h"
#include "srv_display.h"

int main(void)
{
  app_processor_init();
  srv_display();
  while (1)
  {
    app_processor_operates();
  }
}
