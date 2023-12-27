
#include "project.h"
#include "main_data.h"
#include "motorController.h"
#include "debug.h"
#include "aios.h"
#include "ballServeController.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>


void turnDown(void){
   
    IN1_P_01_Write(1);
    IN2_P_00_Write(0);
}

void turnUp(void){
    
    IN1_P_01_Write(0);
    IN2_P_00_Write(1);
}

void stopMoving(){
    ENA_P_16_Write(0);
    PWM_Down_WriteCompare(0);
}

void setDesiredVoltage(uint16 desired_voltage){
    volatile int16 adcResult = 0;
    volatile int16 voltage = 0;
    ADC_StartConvert();
    adcResult = ADC_GetResult16(0);
    voltage = ADC_CountsTo_mVolts(0, adcResult);
    PWM_Down_WriteCompare(750);
    if (abs(voltage - desired_voltage) > 80){
        if (voltage > desired_voltage){               
            while (voltage > desired_voltage){    
                turnUp();
                ADC_StartConvert();
                voltage = ADC_CountsTo_mVolts(0, ADC_GetResult16(0));
            }
                
                                                
        } else if (voltage < desired_voltage){
            while ( desired_voltage > voltage){
                    
                    turnDown();
                    ADC_StartConvert();
                    voltage = ADC_CountsTo_mVolts(0, ADC_GetResult16(0));
                }               
        }
        stopMoving();
        
        CyDelay(150); 
    }
}

void easyMode(){
    pin_motor_Write(0);
    Pin_Output_Serve_Write(0);
    setDesiredVoltage(1930);

    for(;;){
    pin_motor_Write(1);
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

void noneSpin(){
    Pin_Output_LEFT_Write(1);
    Pin_Output_LEFT_GROUND_Write(1);
    
    Pin_Output_RIGHT_Write(1);
    Pin_Output_RIGHT_GROUND_Write(1);
    
    Pin_Output_UP_Write(1);
    Pin_Output_UP_GROUND_Write(1);
    
    Pin_Output_DOWN_Write(1);
    Pin_Output_DOWN_GROUND_Write(1);
}
void leftSpin(){
    Pin_Output_LEFT_Write(0);
    Pin_Output_LEFT_GROUND_Write(0);
    
    Pin_Output_RIGHT_Write(1);
    Pin_Output_RIGHT_GROUND_Write(1);
    
    Pin_Output_UP_Write(1);
    Pin_Output_UP_GROUND_Write(1);
    
    Pin_Output_DOWN_Write(1);
    Pin_Output_DOWN_GROUND_Write(1);
}

void rightSpin(){
    Pin_Output_LEFT_Write(1);
    Pin_Output_LEFT_GROUND_Write(1);
    
    Pin_Output_RIGHT_Write(0);
    Pin_Output_RIGHT_GROUND_Write(0);
    
    Pin_Output_UP_Write(1);
    Pin_Output_UP_GROUND_Write(1);
    
    Pin_Output_DOWN_Write(1);
    Pin_Output_DOWN_GROUND_Write(1);
}


void upSpin(){
    Pin_Output_LEFT_Write(1);
    Pin_Output_LEFT_GROUND_Write(1);
    
    Pin_Output_RIGHT_Write(1);
    Pin_Output_RIGHT_GROUND_Write(1);
    
    Pin_Output_UP_Write(0);
    Pin_Output_UP_GROUND_Write(0);
    
    Pin_Output_DOWN_Write(1);
    Pin_Output_DOWN_GROUND_Write(1);
}

void downSpin(){
    Pin_Output_LEFT_Write(1);
    Pin_Output_LEFT_GROUND_Write(1);
    
    Pin_Output_RIGHT_Write(1);
    Pin_Output_RIGHT_GROUND_Write(1);
    
    Pin_Output_UP_Write(1);
    Pin_Output_UP_GROUND_Write(1);
    
    Pin_Output_DOWN_Write(0);
    Pin_Output_DOWN_GROUND_Write(0);
}

extern const uint32 StripLights_CLUT[ ];
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
        CyDelay(50);
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



int main(void){
    CyGlobalIntEnable;
    stopMoving();
    // Set everything up
    UART_Start();
    ISR_Ball_Trigger_StartEx(Pin_Input_BallTrigger_Handler);
    // StopBallServe();
    // Bluetooth
    // CyBle_Start(AIOS_Handler);
    // CyBle_AiosRegisterAttrCallback(AIOS_Callback);
    
    // Set up flags
    disablePrintIfZeroRPM = false;
    
    motorsEnabled = true;
    // SetMotorsEnabled(false);
    volatile int16 adcResult = 0;
    volatile int16 voltage = 0;
    char uartBuff[50u];
     
    
    ADC_Start();
    UART_UartPutString("Starting measurements...");
 
    CyDelay(1000);

    ENA_P_16_Write(0);
    int16 desired_voltage = 1900;
    // 1820 - lowest position
    // ~2100 - highest 
    PWM_Start();
    PWM_Down_Start();
    PWM_Down_WriteCompare(700);
    pin_motor_Write(1);
    Pin_Output_Serve_Write(1);
    
    StripLights_Start();
    StripLights_Dim(2); 
    
    StripLights_DisplayClear(StripLights_BLACK);
	StripLights_MemClear(StripLights_BLACK);
 
    StripLights_Pixel(0, 0, StripLights_BLACK);
    
    chooseSide(2, 19);
    for(;;){   
        ADC_StartConvert();
        adcResult = ADC_GetResult16(0);
        voltage = ADC_CountsTo_mVolts(0, adcResult);
        
        sprintf(uartBuff, "ADC voltage = %u mV \r\n",  voltage);
        UART_UartPutString(uartBuff);
        PWM_WriteCompare(1000);
        leftSpin();
        easyMode();
        CyDelay(300);
        
        
       // setDesiredVoltage(2000);
       // CyDelay(5000);
       // Control_Rotation_Write(1);
        
    }
}

/* [] END OF FILE */
