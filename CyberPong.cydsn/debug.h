#if !defined(Debug_H)
#define Debug_H

    
#include "project.h"
#include "main_data.h"
#include <stdio.h>
#include "stdbool.h"
#include <time.h>
    
bool disablePrintIfZeroRPM;
static char *MotorDirectionStr[] = {
    "Left", "Right", "Top", "Bottom",
};

void Print(char text[]);
void Println(char text[]);

void PrintMotorSpeeds();
void HandleUARTInput();

#endif
/* [] END OF FILE */

