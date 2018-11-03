/* ========================================
 *
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

// Code setup
#define USE_USB
//* ========================================
#define FALSE 0
#define TRUE 1
#define UNKNOWN 10
//* ========================================
// General Debug
#define LED_ON          LED_Write(1);
#define LED_OFF         LED_Write(0);
#define LED_TOGGLE      LED_Write(~LED_Read());
//* ========================================
// Switches
#define SW0             SW0_Read()
#define SW1             SW1_Read()
#define SW2             SW2_Read()
//* ========================================
// Map
#define ROW             15
#define COL             19
#define INF             9000
#define FOOD            6
//* ========================================
// Motor
// H-Bridge Control
#define COAST_ON            H_BRIDGE_CONTROL_Write(1);
#define COAST_OFF           H_BRIDGE_CONTROL_Write(0);

// Direction Mux Control
#define MOVE_FORWARD        PWM_CONTROL_Write(0);           // drive M1 and M2 forward
#define MOVE_REVERSE        PWM_CONTROL_Write(0b11);        // drive M1 and M2 reverse
#define TURN_LEFT           PWM_CONTROL_Write(0b01);        // drive M1 reverse and M2 forward
#define TURN_RIGHT          PWM_CONTROL_Write(0b10);        // drive M1 forward and M2 reverse

// PWM
#define PWM_MAX             255                         // maximum value of pwm
#define PWM_MIN             0                           // minimum value of pwm
#define PWM_VEER_ADJUST     15                          // adjustment value to veer robot

// Quadrature Decoder
#define FULL_ROT            228                         // (3 enc cycles per motor rot) x (4 cnts per cycle) x (19 gear ratio)
#define QUARTER_ROT         57
#define QUARTER_CIRC        5                           // quarter wheel circumference in cm
#define BLOCK_DIST          13                          // distance of map block in cm
//* ========================================
#define NEXT_ROW(index)	        path[index][0] + (*path_orientation)
#define NEXT_COL(index)	        path[index][1] + (*(path_orientation+1))
#define ROW_CHANGE(orient)	    (path[path_index][0] + orientation[orient][0] == path[path_index+1][0])
#define COL_CHANGE(orient)	    (path[path_index][1] + orientation[orient][1] == path[path_index+1][1])
#define PATH_CHANGED_TO(orient) (ROW_CHANGE(orient) && COL_CHANGE(orient))
//* ========================================
// Timer Timeout Values In ms
#define TC_TIMEOUT      5                               // timer updates every 5ms
#define TC_BATTERY      10000                           // refresh battery reading every 10s
#define TC_RESET        65530                           // max value of tc_cnt
#define TC_PROJECTOR    8                               // frequency of projector refresh rate
//* ========================================
// USBUART
#define BUF_SIZE        64                              // USBUART fixed buffer size
#define CHAR_NULL       '0'
#define CHAR_CR         0x0A                            // carriage return (\r)
#define CHAR_LF         0x0D                            // line feed (\n)
#define CHAR_BACKSP     0x08
#define CHAR_DEL        0x7F
#define CHAR_ENTER      0x0D
#define CHAR_ZERO       '0'
#define CHAR_NINE       '9'
//* ========================================
//RF 
#define RF_SOP          0xAA
#define RF_PACKET_SIZE  32
#define RX_STRING_SIZE  255
//* ========================================
// ADC
#define V_DIV           4.94                            // voltage divider value
//* ========================================
/* [] END OF FILE */
