#if !defined(MotorController_H)
#define MotorController_H


#include "project.h"
#include "main_data.h"
#include "ballServeController.h"

    
void turnDown(void);
void turnUp(void);
void stopMoving(void);
void setSpin(int motors[]);

void SetMotorsEnabled(bool enabled) ;

#endif
/* [] END OF FILE */
