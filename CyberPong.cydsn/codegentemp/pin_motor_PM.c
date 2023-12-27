/*******************************************************************************
* File Name: pin_motor.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "pin_motor.h"

static pin_motor_BACKUP_STRUCT  pin_motor_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: pin_motor_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet pin_motor_SUT.c usage_pin_motor_Sleep_Wakeup
*******************************************************************************/
void pin_motor_Sleep(void)
{
    #if defined(pin_motor__PC)
        pin_motor_backup.pcState = pin_motor_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            pin_motor_backup.usbState = pin_motor_CR1_REG;
            pin_motor_USB_POWER_REG |= pin_motor_USBIO_ENTER_SLEEP;
            pin_motor_CR1_REG &= pin_motor_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pin_motor__SIO)
        pin_motor_backup.sioState = pin_motor_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        pin_motor_SIO_REG &= (uint32)(~pin_motor_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: pin_motor_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to pin_motor_Sleep() for an example usage.
*******************************************************************************/
void pin_motor_Wakeup(void)
{
    #if defined(pin_motor__PC)
        pin_motor_PC = pin_motor_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            pin_motor_USB_POWER_REG &= pin_motor_USBIO_EXIT_SLEEP_PH1;
            pin_motor_CR1_REG = pin_motor_backup.usbState;
            pin_motor_USB_POWER_REG &= pin_motor_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(pin_motor__SIO)
        pin_motor_SIO_REG = pin_motor_backup.sioState;
    #endif
}


/* [] END OF FILE */
