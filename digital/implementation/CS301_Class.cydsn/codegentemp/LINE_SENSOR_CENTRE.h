/*******************************************************************************
* File Name: LINE_SENSOR_CENTRE.h  
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

#if !defined(CY_PINS_LINE_SENSOR_CENTRE_H) /* Pins LINE_SENSOR_CENTRE_H */
#define CY_PINS_LINE_SENSOR_CENTRE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LINE_SENSOR_CENTRE_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LINE_SENSOR_CENTRE__PORT == 15 && ((LINE_SENSOR_CENTRE__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LINE_SENSOR_CENTRE_Write(uint8 value);
void    LINE_SENSOR_CENTRE_SetDriveMode(uint8 mode);
uint8   LINE_SENSOR_CENTRE_ReadDataReg(void);
uint8   LINE_SENSOR_CENTRE_Read(void);
void    LINE_SENSOR_CENTRE_SetInterruptMode(uint16 position, uint16 mode);
uint8   LINE_SENSOR_CENTRE_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LINE_SENSOR_CENTRE_SetDriveMode() function.
     *  @{
     */
        #define LINE_SENSOR_CENTRE_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LINE_SENSOR_CENTRE_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LINE_SENSOR_CENTRE_DM_RES_UP          PIN_DM_RES_UP
        #define LINE_SENSOR_CENTRE_DM_RES_DWN         PIN_DM_RES_DWN
        #define LINE_SENSOR_CENTRE_DM_OD_LO           PIN_DM_OD_LO
        #define LINE_SENSOR_CENTRE_DM_OD_HI           PIN_DM_OD_HI
        #define LINE_SENSOR_CENTRE_DM_STRONG          PIN_DM_STRONG
        #define LINE_SENSOR_CENTRE_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LINE_SENSOR_CENTRE_MASK               LINE_SENSOR_CENTRE__MASK
#define LINE_SENSOR_CENTRE_SHIFT              LINE_SENSOR_CENTRE__SHIFT
#define LINE_SENSOR_CENTRE_WIDTH              1u

/* Interrupt constants */
#if defined(LINE_SENSOR_CENTRE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LINE_SENSOR_CENTRE_SetInterruptMode() function.
     *  @{
     */
        #define LINE_SENSOR_CENTRE_INTR_NONE      (uint16)(0x0000u)
        #define LINE_SENSOR_CENTRE_INTR_RISING    (uint16)(0x0001u)
        #define LINE_SENSOR_CENTRE_INTR_FALLING   (uint16)(0x0002u)
        #define LINE_SENSOR_CENTRE_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LINE_SENSOR_CENTRE_INTR_MASK      (0x01u) 
#endif /* (LINE_SENSOR_CENTRE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LINE_SENSOR_CENTRE_PS                     (* (reg8 *) LINE_SENSOR_CENTRE__PS)
/* Data Register */
#define LINE_SENSOR_CENTRE_DR                     (* (reg8 *) LINE_SENSOR_CENTRE__DR)
/* Port Number */
#define LINE_SENSOR_CENTRE_PRT_NUM                (* (reg8 *) LINE_SENSOR_CENTRE__PRT) 
/* Connect to Analog Globals */                                                  
#define LINE_SENSOR_CENTRE_AG                     (* (reg8 *) LINE_SENSOR_CENTRE__AG)                       
/* Analog MUX bux enable */
#define LINE_SENSOR_CENTRE_AMUX                   (* (reg8 *) LINE_SENSOR_CENTRE__AMUX) 
/* Bidirectional Enable */                                                        
#define LINE_SENSOR_CENTRE_BIE                    (* (reg8 *) LINE_SENSOR_CENTRE__BIE)
/* Bit-mask for Aliased Register Access */
#define LINE_SENSOR_CENTRE_BIT_MASK               (* (reg8 *) LINE_SENSOR_CENTRE__BIT_MASK)
/* Bypass Enable */
#define LINE_SENSOR_CENTRE_BYP                    (* (reg8 *) LINE_SENSOR_CENTRE__BYP)
/* Port wide control signals */                                                   
#define LINE_SENSOR_CENTRE_CTL                    (* (reg8 *) LINE_SENSOR_CENTRE__CTL)
/* Drive Modes */
#define LINE_SENSOR_CENTRE_DM0                    (* (reg8 *) LINE_SENSOR_CENTRE__DM0) 
#define LINE_SENSOR_CENTRE_DM1                    (* (reg8 *) LINE_SENSOR_CENTRE__DM1)
#define LINE_SENSOR_CENTRE_DM2                    (* (reg8 *) LINE_SENSOR_CENTRE__DM2) 
/* Input Buffer Disable Override */
#define LINE_SENSOR_CENTRE_INP_DIS                (* (reg8 *) LINE_SENSOR_CENTRE__INP_DIS)
/* LCD Common or Segment Drive */
#define LINE_SENSOR_CENTRE_LCD_COM_SEG            (* (reg8 *) LINE_SENSOR_CENTRE__LCD_COM_SEG)
/* Enable Segment LCD */
#define LINE_SENSOR_CENTRE_LCD_EN                 (* (reg8 *) LINE_SENSOR_CENTRE__LCD_EN)
/* Slew Rate Control */
#define LINE_SENSOR_CENTRE_SLW                    (* (reg8 *) LINE_SENSOR_CENTRE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LINE_SENSOR_CENTRE_PRTDSI__CAPS_SEL       (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LINE_SENSOR_CENTRE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LINE_SENSOR_CENTRE_PRTDSI__OE_SEL0        (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__OE_SEL0) 
#define LINE_SENSOR_CENTRE_PRTDSI__OE_SEL1        (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LINE_SENSOR_CENTRE_PRTDSI__OUT_SEL0       (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__OUT_SEL0) 
#define LINE_SENSOR_CENTRE_PRTDSI__OUT_SEL1       (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LINE_SENSOR_CENTRE_PRTDSI__SYNC_OUT       (* (reg8 *) LINE_SENSOR_CENTRE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LINE_SENSOR_CENTRE__SIO_CFG)
    #define LINE_SENSOR_CENTRE_SIO_HYST_EN        (* (reg8 *) LINE_SENSOR_CENTRE__SIO_HYST_EN)
    #define LINE_SENSOR_CENTRE_SIO_REG_HIFREQ     (* (reg8 *) LINE_SENSOR_CENTRE__SIO_REG_HIFREQ)
    #define LINE_SENSOR_CENTRE_SIO_CFG            (* (reg8 *) LINE_SENSOR_CENTRE__SIO_CFG)
    #define LINE_SENSOR_CENTRE_SIO_DIFF           (* (reg8 *) LINE_SENSOR_CENTRE__SIO_DIFF)
#endif /* (LINE_SENSOR_CENTRE__SIO_CFG) */

/* Interrupt Registers */
#if defined(LINE_SENSOR_CENTRE__INTSTAT)
    #define LINE_SENSOR_CENTRE_INTSTAT            (* (reg8 *) LINE_SENSOR_CENTRE__INTSTAT)
    #define LINE_SENSOR_CENTRE_SNAP               (* (reg8 *) LINE_SENSOR_CENTRE__SNAP)
    
	#define LINE_SENSOR_CENTRE_0_INTTYPE_REG 		(* (reg8 *) LINE_SENSOR_CENTRE__0__INTTYPE)
#endif /* (LINE_SENSOR_CENTRE__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LINE_SENSOR_CENTRE_H */


/* [] END OF FILE */
