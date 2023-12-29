#if !defined(LED_H)
#define LED_H

#include "project.h"
#include <stdio.h>

extern const uint32 StripLights_CLUT[ ];

void chooseSide(uint8 cycles, uint8 sideCoord, uint32 color);
void start();
void end();
void chooseDiffIdle(uint32 startColor);
void chooseDifficulty(uint32 diffColor);
void oneColor(uint32 color);

#endif
/* [] END OF FILE */

