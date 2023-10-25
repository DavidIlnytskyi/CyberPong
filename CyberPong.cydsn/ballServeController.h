#if !defined(BallServeController_H)
#define BallServeController_H

#include "project.h"
#include "stdbool.h"    
#include "motorController.h"

bool doServe;
bool isServing;
int counter;
    
void CheckForBallServeRequest();
void StopBallServe();
CY_ISR(Pin_Input_BallTrigger_Handler);

void UpdateServing();

#endif
/* [] END OF FILE */
