#include "ballServeController.h"
#include "main_data.h"
#include "motorController.h"

void CheckForBallServeRequest() {
    if(doServe) {
        doServe = false;
        if(motorsEnabled == false)
            return;
        isServing = true;
        Pin_Output_Serve_Write(1);
    }
}

void StopBallServe() {
    Pin_Output_Serve_Write(0);
    isServing = false;
}

void UpdateServing() {
    // turn on and off to reduce speed
    if(isServing) {
        counter = (counter + 1) % 8;
        Pin_Output_Serve_Write(counter > 3);
    }
}


CY_ISR(Pin_Input_BallTrigger_Handler){
    StopBallServe();
    ballCounter++;
    Pin_Output_Serve_Write(0);
    CyDelay(400);
    Pin_Output_Serve_Write(1);
    Pin_Input_BallTrigger_ClearInterrupt();
}
