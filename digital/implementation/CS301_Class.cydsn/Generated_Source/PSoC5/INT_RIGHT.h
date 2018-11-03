/*******************************************************************************
* File Name: INT_RIGHT.h  
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

#if !defined(CY_PINS_INT_RIGHT_H) /* Pins INT_RIGHT_H */
#define CY_PINS_INT_RIGHT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "INT_RIGHT_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 INT_RIGHT__PORT == 15 && ((INT_RIGHT__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    INT_RIGHT_Write(uint8 value);
void    INT_RIGHT_SetDriveMode(uint8 mode);
uint8   INT_RIGHT_ReadDataReg(void);
uint8   INT_RIGHT_Read(void);
void    INT_RIGHT_SetInterruptMode(uint16 position, uint16 mode);
uint8   INT_RIGHT_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the INT_RIGHT_SetDriveMode() function.
     *  @{
     */
        #define INT_RIGHT_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define INT_RIGHT_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define INT_RIGHT_DM_RES_UP          PIN_DM_RES_UP
        #define INT_RIGHT_DM_RES_DWN         PIN_DM_RES_DWN
        #define INT_RIGHT_DM_OD_LO           PIN_DM_OD_LO
        #define INT_RIGHT_DM_OD_HI           PIN_DM_OD_HI
        #define INT_RIGHT_DM_STRONG          PIN_DM_STRONG
        #define INT_RIGHT_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define INT_RIGHT_MASK               INT_RIGHT__MASK
#define INT_RIGHT_SHIFT              INT_RIGHT__SHIFT
#define INT_RIGHT_WIDTH              1u

/* Interrupt constants */
#if defined(INT_RIGHT__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in INT_RIGHT_SetInterruptMode() function.
     *  @{
     */
        #define INT_RIGHT_INTR_NONE      (uint16)(0x0000u)
        #define INT_RIGHT_INTR_RISING    (uint16)(0x0001u)
        #define INT_RIGHT_INTR_FALLING   (uint16)(0x0002u)
        #define INT_RIGHT_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define INT_RIGHT_INTR_MASK      (0x01u) 
#endif /* (INT_RIGHT__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define INT_RIGHT_PS                     (* (reg8 *) INT_RIGHT__PS)
/* Data Register */
#define INT_RIGHT_DR                     (* (reg8 *) INT_RIGHT__DR)
/* Port Number */
#define INT_RIGHT_PRT_NUM                (* (reg8 *) INT_RIGHT__PRT) 
/* Connect to Analog Globals */                                                  
#define INT_RIGHT_AG                     (* (reg8 *) INT_RIGHT__AG)                       
/* Analog MUX bux enable */
#define INT_RIGHT_AMUX                   (* (reg8 *) INT_RIGHT__AMUX) 
/* Bidirectional Enable */                                                        
#define INT_RIGHT_BIE                    (* (reg8 *) INT_RIGHT__BIE)
/* Bit-mask for Aliased Register Access */
#define INT_RIGHT_BIT_MASK               (* (reg8 *) INT_RIGHT__BIT_MASK)
/* Bypass Enable */
#define INT_RIGHT_BYP                    (* (reg8 *) INT_RIGHT__BYP)
/* Port wide control signals */                                                   
#define INT_RIGHT_CTL                    (* (reg8 *) INT_RIGHT__CTL)
/* Drive Modes */
#define INT_RIGHT_DM0                    (* (reg8 *) INT_RIGHT__DM0) 
#define INT_RIGHT_DM1                    (* (reg8 *) INT_RIGHT__DM1)
#define INT_RIGHT_DM2                    (* (reg8 *) INT_RIGHT__DM2) 
/* Input Buffer Disable Override */
#define INT_RIGHT_INP_DIS                (* (reg8 *) INT_RIGHT__INP_DIS)
/* LCD Common or Segment Drive */
#define INT_RIGHT_LCD_COM_SEG            (* (reg8 *) INT_RIGHT__LCD_COM_SEG)
/* Enable Segment LCD */
#define INT_RIGHT_LCD_EN                 (* (reg8 *) INT_RIGHT__LCD_EN)
/* Slew Rate Control */
#define INT_RIGHT_SLW                    (* (reg8 *) INT_RIGHT__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define INT_RIGHT_PRTDSI__CAPS_SEL       (* (reg8 *) INT_RIGHT__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define INT_RIGHT_PRTDSI__DBL_SYNC_IN    (* (reg8 *) INT_RIGHT__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define INT_RIGHT_PRTDSI__OE_SEL0        (* (reg8 *) INT_RIGHT__PRTDSI__OE_SEL0) 
#define INT_RIGHT_PRTDSI__OE_SEL1        (* (reg8 *) INT_RIGHT__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define INT_RIGHT_PRTDSI__OUT_SEL0       (* (reg8 *) INT_RIGHT__PRTDSI__OUT_SEL0) 
#define INT_RIGHT_PRTDSI__OUT_SEL1       (* (reg8 *) INT_RIGHT__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define INT_RIGHT_PRTDSI__SYNC_OUT       (* (reg8 *) INT_RIGHT__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(INT_RIGHT__SIO_CFG)
    #define INT_RIGHT_SIO_HYST_EN        (* (reg8 *) INT_RIGHT__SIO_HYST_EN)
    #define INT_RIGHT_SIO_REG_HIFREQ     (* (reg8 *) INT_RIGHT__SIO_REG_HIFREQ)
    #define INT_RIGHT_SIO_CFG            (* (reg8 *) INT_RIGHT__SIO_CFG)
    #define INT_RIGHT_SIO_DIFF           (* (reg8 *) INT_RIGHT__SIO_DIFF)
#endif /* (INT_RIGHT__SIO_CFG) */

/* Interrupt Registers */
#if defined(INT_RIGHT__INTSTAT)
    #define INT_RIGHT_INTSTAT            (* (reg8 *) INT_RIGHT__INTSTAT)
    #define INT_RIGHT_SNAP               (* (reg8 *) INT_RIGHT__SNAP)
    
	#define INT_RIGHT_0_INTTYPE_REG 		(* (reg8 *) INT_RIGHT__0__INTTYPE)
#endif /* (INT_RIGHT__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_INT_RIGHT_H */


/* [] END OF FILE */
