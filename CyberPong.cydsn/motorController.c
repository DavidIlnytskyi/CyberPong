#include "motorController.h"
#include "stdlib.h"

void chooseSide(uint8 cycles, uint8 sideCoord);

uint8 stopCoords[] = {1, 7, 13, 19};

extern const uint32 StripLights_CLUT[ ];



void turnDown(void){
    IN1_P_01_Write(1);
    IN2_P_00_Write(0);
}

void turnUp(void){
    IN1_P_01_Write(0);
    IN2_P_00_Write(1);
}

void stopMoving(){
    PWM_Down_WriteCompare(0);
}

void setSpin (int motors[]){
    if (motors[0] == 0){
            chooseSide(2, stopCoords[3]);
            Pin_Output_LEFT_Write(0);
            Pin_Output_LEFT_GROUND_Write(0);
    } else{
            Pin_Output_LEFT_Write(1);
            Pin_Output_LEFT_GROUND_Write(1); 
        }
        
        if (motors[1] == 0){
            chooseSide(2, stopCoords[1]);
            Pin_Output_RIGHT_Write(0);
            Pin_Output_RIGHT_GROUND_Write(0); 
        }
        else{
            Pin_Output_RIGHT_Write(1);
            Pin_Output_RIGHT_GROUND_Write(1); 
        }
        if (motors[2] == 0){
            chooseSide(2, stopCoords[0]);
            Pin_Output_UP_Write(0);
            Pin_Output_UP_GROUND_Write(0); 
        }
        else{
            Pin_Output_UP_Write(1);
            Pin_Output_UP_GROUND_Write(1); 
        }
        Pin_Output_DOWN_Write(1);
        Pin_Output_DOWN_GROUND_Write(1);
        PWM_Start();
        
        if (motors[3] == 2000){
            PWM_WriteCompare(700);
        } else if (motors[3] == 5000){
            PWM_WriteCompare(850);
        } else {
            PWM_WriteCompare(1000);
        }
}

void SetMotorsEnabled(bool enabled) {
    if(motorsEnabled == enabled)
        return;
    if(enabled==false)
        StopBallServe();
    motorsEnabled = enabled;
}



void chooseSide(uint8 cycles, uint8 sideCoord)
{
    uint32 ledPosition = 1;
    uint8 currCycles = 0;
    uint32 ledPos;
    
    for(int i = 0; i < 7; ++i)
    {
        StripLights_Pixel(i, 0, StripLights_CYAN);
        StripLights_Trigger(1);  
        CyDelay(50);
    }
    
    uint32 mainCol = StripLights_GetPixel(0, 0);
    uint32 col2 = mainCol;
    col2 = (col2 >> 1) & 0x007F7F7F;
    col2 = (col2 >> 1) & 0x007F7F7F;
    uint32 col3 = col2;
    col3 = (col3 >> 1) & 0x007F7F7F;
    uint32 col4 = col3;
    col4 = (col4 >> 1) & 0x007F7F7F;
    col4 = (col4 >> 1) & 0x007F7F7F;
    
    for(;;)
    {
        StripLights_Pixel((ledPosition+23)%24, 0, StripLights_BLACK);
        
        StripLights_Pixel((ledPosition + 3) % 24, 0, mainCol);
        StripLights_Pixel(ledPosition % 24, 0, col4);
        StripLights_Pixel((ledPosition + 6) % 24, 0, col4);
        StripLights_Pixel((ledPosition + 1) % 24, 0, col3);
        StripLights_Pixel((ledPosition + 5) % 24, 0, col3);
        StripLights_Pixel((ledPosition + 2) % 24, 0, col2);
        StripLights_Pixel((ledPosition + 4) % 24, 0, col2);
        
        StripLights_Trigger(1);  
        CyDelay(10);
        ledPosition = (ledPosition + 1) % 24;
        if(ledPosition == sideCoord)
        {
            currCycles++;
        }
        if(currCycles == cycles)
        {
            break;
        }
    }

}
/* [] END OF FILE */
