/*******************************************************************************
* File Name: H_BRIDGE_CONTROL_PM.c
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

#include "H_BRIDGE_CONTROL.h"

/* Check for removal by optimization */
#if !defined(H_BRIDGE_CONTROL_Sync_ctrl_reg__REMOVED)

static H_BRIDGE_CONTROL_BACKUP_STRUCT  H_BRIDGE_CONTROL_backup = {0u};

    
/*******************************************************************************
* Function Name: H_BRIDGE_CONTROL_SaveConfig
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
void H_BRIDGE_CONTROL_SaveConfig(void) 
{
    H_BRIDGE_CONTROL_backup.controlState = H_BRIDGE_CONTROL_Control;
}


/*******************************************************************************
* Function Name: H_BRIDGE_CONTROL_RestoreConfig
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
void H_BRIDGE_CONTROL_RestoreConfig(void) 
{
     H_BRIDGE_CONTROL_Control = H_BRIDGE_CONTROL_backup.controlState;
}


/*******************************************************************************
* Function Name: H_BRIDGE_CONTROL_Sleep
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
void H_BRIDGE_CONTROL_Sleep(void) 
{
    H_BRIDGE_CONTROL_SaveConfig();
}


/*******************************************************************************
* Function Name: H_BRIDGE_CONTROL_Wakeup
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
void H_BRIDGE_CONTROL_Wakeup(void)  
{
    H_BRIDGE_CONTROL_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
