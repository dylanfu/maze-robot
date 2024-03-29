/*******************************************************************************
* File Name: H_BRIDGE_CONTROL.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_H_BRIDGE_CONTROL_H) /* CY_CONTROL_REG_H_BRIDGE_CONTROL_H */
#define CY_CONTROL_REG_H_BRIDGE_CONTROL_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} H_BRIDGE_CONTROL_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    H_BRIDGE_CONTROL_Write(uint8 control) ;
uint8   H_BRIDGE_CONTROL_Read(void) ;

void H_BRIDGE_CONTROL_SaveConfig(void) ;
void H_BRIDGE_CONTROL_RestoreConfig(void) ;
void H_BRIDGE_CONTROL_Sleep(void) ; 
void H_BRIDGE_CONTROL_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define H_BRIDGE_CONTROL_Control        (* (reg8 *) H_BRIDGE_CONTROL_Sync_ctrl_reg__CONTROL_REG )
#define H_BRIDGE_CONTROL_Control_PTR    (  (reg8 *) H_BRIDGE_CONTROL_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_H_BRIDGE_CONTROL_H */


/* [] END OF FILE */
