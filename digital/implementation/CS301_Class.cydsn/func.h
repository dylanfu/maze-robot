/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
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
//* PATH */
// Path Generation Logic
uint16 get_food_list_path_length();
uint16 get_traverse_path_length();
void generate_food_list_path(int8 path[][2], uint16 path_length);
void generate_traverse_path(int8 path[][2]);

// Path Algorithms
uint16 find_shortest_path(uint8 pos[2], uint8 des[2], int8 path[][2]);
uint16 find_traverse_path(uint8 pos[2], int8 path[][2]);

// Path Assistant Functions
void get_num_map_nodes();
void init_path(int8 path[][2], uint16 path_length);
int32 get_node_index(uint8 node[2], uint8 nodes[][2]);
int32 get_array_min_index(float array[], uint8 cons[]);
uint8 is_next_to(uint8 node_1[2], uint8 node_2[2]);
//* ========================================
//* TACHO */
// Robot Path Follower Logic
uint8 follow_path(int8 path[][2], uint16 path_length);
void follow_line();
void turn_robot(int8 path[][2]);

// Robot Sensors
void get_light_sensors();
void get_wheel_quadrature();
void get_distance();
void get_next_event_index(int8 path[][2], uint16 path_length);
void update_robot_position(int8 path[][2], uint16 path_length);
//* ========================================
/* [] END OF FILE */
