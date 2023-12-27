/*******************************************************************************
* File Name: pin_motor.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_pin_motor_ALIASES_H) /* Pins pin_motor_ALIASES_H */
#define CY_PINS_pin_motor_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define pin_motor_0			(pin_motor__0__PC)
#define pin_motor_0_PS		(pin_motor__0__PS)
#define pin_motor_0_PC		(pin_motor__0__PC)
#define pin_motor_0_DR		(pin_motor__0__DR)
#define pin_motor_0_SHIFT	(pin_motor__0__SHIFT)
#define pin_motor_0_INTR	((uint16)((uint16)0x0003u << (pin_motor__0__SHIFT*2u)))

#define pin_motor_INTR_ALL	 ((uint16)(pin_motor_0_INTR))


#endif /* End Pins pin_motor_ALIASES_H */


/* [] END OF FILE */
