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

#include <project.h>
#include "defines.h"
//* ========================================
// Motor Quadrature
int16 quad_cnt_left = 0;
int16 quad_cnt_right = 0;
int16 quad_cnt_prev = 0;
uint8 straight_line_distance = 0;
uint8 distance_prev = 0;

// Motor PWM
uint8 pwm_cmp_left = 115;
uint8 pwm_cmp_right= 117;
//* ========================================
// Robot Movement
enum directions {FORWARD=0, TURNING_LEFT=3, TURNING_RIGHT=1, STAT=2};
uint8 robot_direction = STAT;

// Robot Position
uint8 robot_x_pos = 1;
uint8 robot_y_pos = 1;

// Map
uint16 num_map_nodes = 0;

// Orientations
int8 orientation[4][2] = {
	{-1, 0},		                // UP
	{0, 1},			                // RIGHT
	{1, 0},			                // DOWN
	{0, -1}			                // LEFT
};
enum orientations {UP, RIGHT, DOWN, LEFT};
uint8 robot_orientation = DOWN;
int8* path_orientation = &orientation[DOWN][0];

// Path Indexing
uint16 path_index = 0;
uint16 robot_position_index = 0;
uint16 next_event_index = 0;

// Movement State Flags
uint8 flag_turn_around = 0;
uint8 flag_veering = 0;
uint8 flag_new_path_index = 0;
uint8 flag_passing_next_int = 0;
uint8 flag_next_event_deadend = 0;
uint8 flag_next_event_u_turn = 0;
uint8 flag_centre_on_line_after_turn = 0;
uint8 flag_next_event_intersection = 0;

// Light Sensors
uint8 int_sensor_left = 0;
uint8 int_sensor_right = 0;
uint8 line_sensor_centre = 0;
uint8 line_sensor_left = 0;
uint8 line_sensor_right = 0;
//* ========================================
// Timer Interrupt
uint16 tc_cnt = 0;

// ADC Interupt Flag
uint8 flag_adc_ready = 0;
//* ========================================
/* [] END OF FILE */
