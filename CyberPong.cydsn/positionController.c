#include "positionController.h"
#include "stdlib.h"

void easyMode(){
    Pin_Motor_Write(0);
    Pin_Output_Serve_Write(0);
    setDesiredVoltage(1950);

    for(;;){
        Pin_Motor_Write(1);
        Pin_Output_Serve_Write(1);
    }
}
void mediumMode(){
    setDesiredVoltage(1700);
    for (uint8 i = 0; i < 2; ++i){
        UpdateServing();
    }
    setDesiredVoltage(1900);
    for (uint8 i = 0; i < 3; ++i){
        UpdateServing();
    }
}
void hardMode(){
    uint16 voltages [] = {1700, 1900, 2100, 1900, 1700};
    for (uint8 i = 0; i < 5; ++i){
        setDesiredVoltage(voltages[i]);
        UpdateServing();
    }
}
