#ifndef __ST7735_FONT_H
#define __ST7735_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define FONT_7X10

typedef enum
{
  FONT_6x8 = 0,
  FONT_7x10,
  FONT_11x18,
  FONT_16x26
} font_size_t;

typedef struct
{
  font_size_t size;
  const uint16_t *data;
  uint8_t width;
  uint8_t height;
} font_t;

#ifdef FONT_6X8
extern font_t font_6x8;
#endif

#ifdef FONT_7X10
extern font_t font_7x10;
#endif

#ifdef FONT_11X18
extern font_t font_11x18;
#endif

#ifdef FONT_16X26
extern font_t font_16x26;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __ST7735_FONT_H */
