#if !defined(MotorController_H)
#define MotorController_H


#include "project.h"
#include "main_data.h"
#include "ballServeController.h"

    
void turnDown(void);
void turnUp(void);
void stopMoving(void);
void setSpin(int motors[]);
void easyMode(void);
void mediumMode(void);
void hardMode(void);
void setDesiredVoltage(uint16 desired_voltage);
void SetMotorsEnabled(bool enabled);
void setDifficulty();

#endif
/* [] END OF FILE */
