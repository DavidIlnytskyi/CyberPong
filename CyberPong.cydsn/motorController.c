#include "motorController.h"
#include "stdlib.h"
#include "main_data.h"

#include "stdio.h"
void chooseSide(uint8 cycles, uint8 sideCoord);

uint8 stopCoords[] = {1, 7, 13, 19};

extern const uint32 StripLights_CLUT[ ];


void turnDown(void){
    PWM_Down_WriteCompare(720);
    ENA_P_16_Write(1);
    IN1_P_01_Write(1);
    IN2_P_00_Write(0);
}

void turnUp(void){
    PWM_Down_WriteCompare(720);
    ENA_P_16_Write(1);
    IN1_P_01_Write(0);
    IN2_P_00_Write(1);
}

void stopMoving(){
    ENA_P_16_Write(0);
    PWM_Down_WriteCompare(0);
}
void oneColor()
{
    StripLights_DisplayClear(StripLights_BLACK);
    StripLights_MemClear(StripLights_BLACK);
    
    StripLights_Pixel(0, 0, StripLights_BLACK);
    for(int i = 0; i < 24; ++i)
    {
        StripLights_Pixel(i, 0, StripLights_CYAN);
    }
    CyDelay(10);
    StripLights_Trigger(1); 
}
void setSpin (int motors[]){
    if(motors[0] && motors[1] && motors[2] && motors[3])
    {
        oneColor();
    }
    if (motors[0] == 0){
            chooseSide(1, stopCoords[3]);
            Pin_Output_LEFT_Write(0);
            Pin_Output_LEFT_GROUND_Write(0);
    } else{
            Pin_Output_LEFT_Write(1);
            Pin_Output_LEFT_GROUND_Write(1); 
        }
        
        if (motors[1] == 0){
            chooseSide(1, stopCoords[1]);
            Pin_Output_RIGHT_Write(0);
            Pin_Output_RIGHT_GROUND_Write(0); 
        }
        else{
            Pin_Output_RIGHT_Write(1);
            Pin_Output_RIGHT_GROUND_Write(1); 
        }
        if (motors[2] == 0){
            chooseSide(1, stopCoords[0]);
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

void chooseSide(uint8 cycles, uint8 sideCoord){
    StripLights_DisplayClear(StripLights_BLACK);
    StripLights_MemClear(StripLights_BLACK);
    
    StripLights_Pixel(0, 0, StripLights_BLACK);
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

void setDesiredVoltage(uint16 desired_voltage){
    volatile int16 adcResult = 0;
    volatile int16 voltage = 0;
    ADC_Start();
    ADC_StartConvert();
    adcResult = ADC_GetResult16(0);
    voltage = ADC_CountsTo_mVolts(0, adcResult);
    

    UART_UartPutString("readyyyy");
    if (abs(voltage - desired_voltage) > 90){
        Pin_Output_Serve_Write(0);    
        Pin_Motor_Write(0);
        if (voltage > desired_voltage){               
            while (voltage > desired_voltage){
                turnUp();
                
                char mes[100];
                sprintf(mes, "voltage: %u\r\n", voltage );
                UART_UartPutString(mes);
                ADC_StartConvert();
                voltage = ADC_CountsTo_mVolts(0, ADC_GetResult16(0));
            }                  
        } else if (voltage < desired_voltage){
            
            while (desired_voltage > voltage){
                turnDown();
                
                char mes[100];
                sprintf(mes, "voltage: %u\r\n", voltage );
                UART_UartPutString(mes);
                ADC_StartConvert();
                voltage = ADC_CountsTo_mVolts(0, ADC_GetResult16(0));
            }             
        }
        stopMoving();
        CyDelay(150); 
        Pin_Motor_Write(1);
        Pin_Output_Serve_Write(1);
    }
}

bool checkDifficultyChange(){
    return oldDifficulty != newDiffuculty;
};

void setDifficulty(){
    char mes[100];
    sprintf(mes, "counter: %u\r\n", ballCounter);
    UART_UartPutString(mes);
    if (checkDifficultyChange()){
        ballCounter = 0;
        oldDifficulty = newDiffuculty;
    }
    switch(oldDifficulty){
        case 0:{
            easyMode();
            break;
        }
        case 1:{
            mediumMode();
            break;
        }
        case 2:{
            hardMode();
            break;
        }
    }
}


void easyMode(){
    setDesiredVoltage(1950);
    if(ballCounter < 10){
        setDesiredVoltage(1950);
      //  CyDelay(300);
    } else{
        ballCounter = 0;
    }
    
}

void mediumMode(){
    if(ballCounter < 5){
        setDesiredVoltage(1810);
    } else if(ballCounter < 10){
        setDesiredVoltage(1930);
    } else {
        ballCounter = 0;
    }
    
}
void hardMode(){
    uint16 voltages [] = {1820, 1820, 1900, 1900, 2050, 2050,2050, 2050, 1900, 1900};
    if (ballCounter < 10){
        setDesiredVoltage(voltages[ballCounter]);
    } else{
        ballCounter = 0;
    }
}

/* [] END OF FILE */
