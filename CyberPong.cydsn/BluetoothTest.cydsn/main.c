/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"



int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    CyBle_Start(Stack_Handler);
    CyBle_IasRegisterAttrCallback(Ias_Handler);
    
    PWM_Start();

    for(;;)
    {
        CyBle_ProcessEvents();   
    }
}

/* [] END OF FILE */
