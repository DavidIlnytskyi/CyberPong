/*******************************************************************************
* File Name: ENA_P_16.h  
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

#if !defined(CY_PINS_ENA_P_16_ALIASES_H) /* Pins ENA_P_16_ALIASES_H */
#define CY_PINS_ENA_P_16_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ENA_P_16_0			(ENA_P_16__0__PC)
#define ENA_P_16_0_PS		(ENA_P_16__0__PS)
#define ENA_P_16_0_PC		(ENA_P_16__0__PC)
#define ENA_P_16_0_DR		(ENA_P_16__0__DR)
#define ENA_P_16_0_SHIFT	(ENA_P_16__0__SHIFT)
#define ENA_P_16_0_INTR	((uint16)((uint16)0x0003u << (ENA_P_16__0__SHIFT*2u)))

#define ENA_P_16_INTR_ALL	 ((uint16)(ENA_P_16_0_INTR))


#endif /* End Pins ENA_P_16_ALIASES_H */


/* [] END OF FILE */
