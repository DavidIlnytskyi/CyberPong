#include "motorController.h"
#include "stdlib.h"

int Clamp(int v, int min, int max){
    if (v < min)
        v = min;
    else if(v > max)
        v = max;    
    return v;
}
void SetMotorSpeed(int speeds[]) {
    for (int i = 0; i < MOTOR_COUNT; i++) {
        SetMotorSpeed_Single(i, speeds[i]);
        motor_speeds[i] = speeds[i];
    }
}
void SetMotorSpeed_Single(enum MotorDirection dir, int speed) {
    if(speed == 0) {
        FanController_SetDesiredSpeed(dir+1, 0);
        motor_speeds[dir] = speed;
        return;
    }
    // Setting rotation direction
    uint8 bits = Control_Rotation_Read();
    bits ^= (-(speed < 0 ? -1 : 1) ^ bits) & (1UL << dir);
    Control_Rotation_Write(bits);
    
    // Setting speed
    int clamped = Clamp(abs(speed), MIN_RPM, MAX_RPM);
    FanController_SetDesiredSpeed(dir+1, motorsEnabled ? 2*clamped : 0);
    motor_speeds[dir] = speed;
}

void SetMotorsEnabled(bool enabled) {
    if(motorsEnabled == enabled)
        return;
    if(enabled==false)
        StopBallServe();
    motorsEnabled = enabled;
    for (int i = 0; i < MOTOR_COUNT; i++) {
        SetMotorSpeed_Single(i, enabled ? motor_speeds[i] : 0);
    }
}
/* [] END OF FILE */
