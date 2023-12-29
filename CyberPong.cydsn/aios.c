#include "aios.h"
#include "ballServeController.h"
#include "motorController.h"
#include "main_data.h"

void AIOS_Handler(uint32 eventCode, void *eventParams)
{
    switch(eventCode){
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
    }
}
void AIOS_Callback(uint32 eventCode, void *eventParam){
    CYBLE_AIOS_CHAR_VALUE_T *locCharValue = eventParam;

    switch(eventCode){
        case CYBLE_EVT_AIOSS_CHAR_WRITE: {
            char str[100];
            int motorSpeeds[4] = {5000};
            
            
            motorSpeeds[0] = CyBle_AiosGet16ByPtr(locCharValue->value->val);
            motorSpeeds[1] = CyBle_AiosGet16ByPtr(locCharValue->value->val+2);
            motorSpeeds[2] = CyBle_AiosGet16ByPtr(locCharValue->value->val+4);
            motorSpeeds[3] = CyBle_AiosGet16ByPtr(locCharValue->value->val+6);
            
            sprintf(str, "Motorspeeds are %d %d %d %d\r\n", motorSpeeds[0], motorSpeeds[1], motorSpeeds[2], motorSpeeds[3]);
            UART_UartPutString(str);
            
            setSpin(motorSpeeds);
            CyDelay(500);
            
            uint8 ZERO = 0;
            doServe = CyBle_AiosGet16ByPtr(locCharValue->value->val+8);
            CyBle_AiossSetCharacteristicValue(CYBLE_AIOS_ANALOG, 4, 2, &ZERO);
            
            bool enabled = CyBle_AiosGet16ByPtr(locCharValue->value->val+10);
            SetMotorsEnabled(true);
            
            newDiffuculty = CyBle_AiosGet16ByPtr(locCharValue->value->val+12);
            break;
         }
    }
} 

/* [] END OF FILE */
