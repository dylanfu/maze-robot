/*******************************************************************************
* File Name: v_bat.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_v_bat_H) /* Pins v_bat_H */
#define CY_PINS_v_bat_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "v_bat_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 v_bat__PORT == 15 && ((v_bat__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    v_bat_Write(uint8 value);
void    v_bat_SetDriveMode(uint8 mode);
uint8   v_bat_ReadDataReg(void);
uint8   v_bat_Read(void);
void    v_bat_SetInterruptMode(uint16 position, uint16 mode);
uint8   v_bat_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the v_bat_SetDriveMode() function.
     *  @{
     */
        #define v_bat_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define v_bat_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define v_bat_DM_RES_UP          PIN_DM_RES_UP
        #define v_bat_DM_RES_DWN         PIN_DM_RES_DWN
        #define v_bat_DM_OD_LO           PIN_DM_OD_LO
        #define v_bat_DM_OD_HI           PIN_DM_OD_HI
        #define v_bat_DM_STRONG          PIN_DM_STRONG
        #define v_bat_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define v_bat_MASK               v_bat__MASK
#define v_bat_SHIFT              v_bat__SHIFT
#define v_bat_WIDTH              1u

/* Interrupt constants */
#if defined(v_bat__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in v_bat_SetInterruptMode() function.
     *  @{
     */
        #define v_bat_INTR_NONE      (uint16)(0x0000u)
        #define v_bat_INTR_RISING    (uint16)(0x0001u)
        #define v_bat_INTR_FALLING   (uint16)(0x0002u)
        #define v_bat_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define v_bat_INTR_MASK      (0x01u) 
#endif /* (v_bat__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define v_bat_PS                     (* (reg8 *) v_bat__PS)
/* Data Register */
#define v_bat_DR                     (* (reg8 *) v_bat__DR)
/* Port Number */
#define v_bat_PRT_NUM                (* (reg8 *) v_bat__PRT) 
/* Connect to Analog Globals */                                                  
#define v_bat_AG                     (* (reg8 *) v_bat__AG)                       
/* Analog MUX bux enable */
#define v_bat_AMUX                   (* (reg8 *) v_bat__AMUX) 
/* Bidirectional Enable */                                                        
#define v_bat_BIE                    (* (reg8 *) v_bat__BIE)
/* Bit-mask for Aliased Register Access */
#define v_bat_BIT_MASK               (* (reg8 *) v_bat__BIT_MASK)
/* Bypass Enable */
#define v_bat_BYP                    (* (reg8 *) v_bat__BYP)
/* Port wide control signals */                                                   
#define v_bat_CTL                    (* (reg8 *) v_bat__CTL)
/* Drive Modes */
#define v_bat_DM0                    (* (reg8 *) v_bat__DM0) 
#define v_bat_DM1                    (* (reg8 *) v_bat__DM1)
#define v_bat_DM2                    (* (reg8 *) v_bat__DM2) 
/* Input Buffer Disable Override */
#define v_bat_INP_DIS                (* (reg8 *) v_bat__INP_DIS)
/* LCD Common or Segment Drive */
#define v_bat_LCD_COM_SEG            (* (reg8 *) v_bat__LCD_COM_SEG)
/* Enable Segment LCD */
#define v_bat_LCD_EN                 (* (reg8 *) v_bat__LCD_EN)
/* Slew Rate Control */
#define v_bat_SLW                    (* (reg8 *) v_bat__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define v_bat_PRTDSI__CAPS_SEL       (* (reg8 *) v_bat__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define v_bat_PRTDSI__DBL_SYNC_IN    (* (reg8 *) v_bat__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define v_bat_PRTDSI__OE_SEL0        (* (reg8 *) v_bat__PRTDSI__OE_SEL0) 
#define v_bat_PRTDSI__OE_SEL1        (* (reg8 *) v_bat__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define v_bat_PRTDSI__OUT_SEL0       (* (reg8 *) v_bat__PRTDSI__OUT_SEL0) 
#define v_bat_PRTDSI__OUT_SEL1       (* (reg8 *) v_bat__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define v_bat_PRTDSI__SYNC_OUT       (* (reg8 *) v_bat__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(v_bat__SIO_CFG)
    #define v_bat_SIO_HYST_EN        (* (reg8 *) v_bat__SIO_HYST_EN)
    #define v_bat_SIO_REG_HIFREQ     (* (reg8 *) v_bat__SIO_REG_HIFREQ)
    #define v_bat_SIO_CFG            (* (reg8 *) v_bat__SIO_CFG)
    #define v_bat_SIO_DIFF           (* (reg8 *) v_bat__SIO_DIFF)
#endif /* (v_bat__SIO_CFG) */

/* Interrupt Registers */
#if defined(v_bat__INTSTAT)
    #define v_bat_INTSTAT            (* (reg8 *) v_bat__INTSTAT)
    #define v_bat_SNAP               (* (reg8 *) v_bat__SNAP)
    
	#define v_bat_0_INTTYPE_REG 		(* (reg8 *) v_bat__0__INTTYPE)
#endif /* (v_bat__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_v_bat_H */


/* [] END OF FILE */
