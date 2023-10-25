/*******************************************************************************
* File Name: Control_DOWN_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Control_DOWN.h"

/* Check for removal by optimization */
#if !defined(Control_DOWN_Sync_ctrl_reg__REMOVED)

static Control_DOWN_BACKUP_STRUCT  Control_DOWN_backup = {0u};

    
/*******************************************************************************
* Function Name: Control_DOWN_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_DOWN_SaveConfig(void) 
{
    Control_DOWN_backup.controlState = Control_DOWN_Control;
}


/*******************************************************************************
* Function Name: Control_DOWN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Control_DOWN_RestoreConfig(void) 
{
     Control_DOWN_Control = Control_DOWN_backup.controlState;
}


/*******************************************************************************
* Function Name: Control_DOWN_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_DOWN_Sleep(void) 
{
    Control_DOWN_SaveConfig();
}


/*******************************************************************************
* Function Name: Control_DOWN_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Control_DOWN_Wakeup(void)  
{
    Control_DOWN_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
