#include "ballServeController.h"

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
        Pin_Output_Serve_Write(counter > 5);
    }
}


CY_ISR(Pin_Input_BallTrigger_Handler){
    StopBallServe();

    Pin_Input_BallTrigger_ClearInterrupt();
}