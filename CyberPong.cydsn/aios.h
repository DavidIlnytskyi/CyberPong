#if !defined(BluetoothAios_H)
#define BluetoothAios_H

    
#include "project.h"
#include "main_data.h"
#include "debug.h"
#include "motorController.h"
    
    
void AIOS_Handler(uint32 eventCode, void *eventParams);
void AIOS_Callback(uint32 eventCode, void *eventParam);


#endif
/* [] END OF FILE */
