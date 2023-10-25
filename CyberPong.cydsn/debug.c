#include "debug.h"
#include "ballServeController.h"
#include "motorController.h"

void Print(char text[]) {
    UART_UartPutString(text);
}
void Println(char text[]) {
    UART_UartPutString(text);
    UART_UartPutChar('\n');
    UART_UartPutChar('\r');
}

int counter = 0;
int variances[4];
int n = 0;
void PrintMotorSpeeds() {
    if(disablePrintIfZeroRPM && FanController_GetActualSpeed(1)==0 && FanController_GetActualSpeed(2)==0 && 
       FanController_GetActualSpeed(3)==0 && FanController_GetActualSpeed(4)==0)
        return;

    if (counter < 25000) {
        counter++;
        return;
    }
    else
        counter=0;
    
    n++;
    int current_rpm = 0, desired_rpm = 0;
    for (int i = 1; i < MOTOR_COUNT + 1; i++) {
        
        Print(MotorDirectionStr[i-1]);
        Print(":");
        
        current_rpm = FanController_GetActualSpeed(i);
        sprintf(uart_rpm_buff, "%u ", current_rpm / 2);
        Print(uart_rpm_buff);
        
        desired_rpm = FanController_GetDesiredSpeed(i);
        sprintf(uart_rpm_buff, "%u  ", desired_rpm / 2);
        Print(uart_rpm_buff);
        
        variances[i] += ((current_rpm-desired_rpm)*(current_rpm-desired_rpm));
        sprintf(uart_rpm_buff, "%u  ", variances[i]/n/1000);
        Print(uart_rpm_buff);
        
    }
    UART_UartPutChar('\n');
    UART_UartPutChar('\r');
}

void HandleUARTInput(){
    char ch = UART_UartGetChar();
    if (ch == 'a') {
        disablePrintIfZeroRPM = !disablePrintIfZeroRPM;
    }
    else if (ch == 's') {
        doServe = true;
    }
    else if(ch=='d'){
        variances[1] = 0;
        variances[2] = 0;
        variances[3] = 0;
        variances[4] = 0;
        n = 0;
    }
}

/* [] END OF FILE */