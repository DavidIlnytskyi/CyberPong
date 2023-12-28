#include "project.h"
#include "main_data.h"
#include "motorController.h"
#include "debug.h"
#include "aios.h"
#include "ballServeController.h"
#include "time.h"

extern const uint32 StripLights_CLUT[ ];

int main(void){
    CyGlobalIntEnable;
    
    // Set everything up
    UART_Start();
    ISR_Ball_Trigger_StartEx(Pin_Input_BallTrigger_Handler);
    StopBallServe();

    // Bluetooth
    CyBle_Start(AIOS_Handler);
    CyBle_AiosRegisterAttrCallback(AIOS_Callback);
    
    // Set up flags
    disablePrintIfZeroRPM = false;
    motorsEnabled = true;
    
    //LED 
    StripLights_Start();
    StripLights_Dim(2); 
	
    StripLights_DisplayClear(StripLights_BLACK);
	StripLights_MemClear(StripLights_BLACK);
 
    StripLights_Pixel(0, 0, StripLights_BLACK);

    SetMotorsEnabled(false);
    Pin_Output_Serve_Write(1);
    Pin_Motor_Write(1);
    for(;;){
        CyBle_ProcessEvents();
        PrintMotorSpeeds();
        HandleUARTInput();
        CheckForBallServeRequest();
        UpdateServing();
    }
}


/* [] END OF FILE */
