#if !defined(MotorController_H)
#define MotorController_H


#include "project.h"
#include "main_data.h"
#include "ballServeController.h"
    
void SetMotorSpeed(int speeds[]);
void SetMotorSpeed_Single(enum MotorDirection dir, int speed);
void SetMotorsEnabled(bool enabled);

#endif
/* [] END OF FILE */
