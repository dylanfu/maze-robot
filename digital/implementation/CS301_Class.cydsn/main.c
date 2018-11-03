/* ========================================
 * Fully working code: 
 * PWM      : 
 * Encoder  : 
 * ADC      :
 * USB      : port displays speed and position.
 * CMD: "PW xx"
 * Copyright Univ of Auckland, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Univ of Auckland.
 *
 * ========================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <project.h>
//* ========================================
#include "defines.h"
#include "func.h"
#include "vars.h"
#include "map.h"
//* ========================================
// USBUART
void usbPutString(char *s);
void usbPutChar(char c);
//* ========================================
CY_ISR_PROTO(handle_timer_tc);
CY_ISR_PROTO(handle_adc_reading);
//* ========================================
CY_ISR(handle_timer_tc)
{
    tc_cnt += TC_TIMEOUT;
    
    if (tc_cnt % TC_BATTERY == 0)
        flag_adc_ready = 0;
    
    if (tc_cnt == TC_RESET)
        tc_cnt = 0;
    
    Timer_TS_ReadStatusRegister();
}
//* ========================================
CY_ISR(handle_adc_reading)
{
    flag_adc_ready = 1;
}
//* ========================================
int main()
{
// --------------------------------
// ----- INITIALIZATIONS ----------
    // Start timer
    Timer_TS_Start();
    isr_TS_StartEx(handle_timer_tc);
    
    // Start ADC
    ADC_Start();
    isr_eoc_StartEx(handle_adc_reading);
    
    // Activate global interupts
    CYGlobalIntEnable;
    
    // Set mode of operation by reading dip switches
    uint8 mode = (SW1 << 1) | (SW0);
    
    // Find number of nodes in map
    get_num_map_nodes();
    // Exit if map has no nodes
    if (!num_map_nodes)
        return 1;
    
    // Find path legnth
	uint16 path_length = 0;
    switch (mode) {
        case 0:
            path_length = get_food_list_path_length();
            break;
        case 2:
            path_length = get_traverse_path_length();
            break;
    }
    if (!path_length || path_length == INF)
        return 1;
    
    // Generate path
	int8 path[path_length][2];
	init_path(path, path_length);
    switch (mode) {
        case 0:
            generate_food_list_path(path, path_length);
            break;
        case 2:
            generate_traverse_path(path);
            break;
    }
    
    // Allow light sensors to settle after power up
    CyDelay(TC_PROJECTOR);
    
    // Start quadrature decoders
    QuadDec_M1_Start();
    QuadDec_M2_Start();
    
    // Start pwm for both motors
    PWM_1_Start();
    PWM_2_Start();
    
    // Set both PWM to initial duty cycle
    PWM_1_WriteCompare(pwm_cmp_left);
    PWM_2_WriteCompare(pwm_cmp_right);
    
    // Activate Robot
    if (SW2) {
        MOVE_FORWARD
        robot_direction = FORWARD;
        COAST_ON
    }

// ------USB SETUP ----------------    
#ifdef USE_USB    
    USBUART_Start(0,USBUART_5V_OPERATION);
#endif
    // Run robot
    for(;;)
    {
        // follow generated path and stop all operations
        // when end of path is reached
        get_light_sensors();
        if (!follow_path(path, path_length)) {
            COAST_OFF
            robot_direction = STAT;
            
            PWM_1_Stop();
            PWM_2_Stop();
            
            QuadDec_M1_Stop();
            QuadDec_M2_Stop();
            
            ADC_Stop();
            isr_eoc_Stop();
            
            Timer_TS_Stop();
            isr_TS_Stop();
            
            break;
        }
        
        // monitor battery level and stop all operations if it drops below 7.15V
        if (!flag_adc_ready) {
            ADC_StartConvert();
        }
        else if (flag_adc_ready == 1) {
            int16 adc_bat_value = ADC_CountsTo_mVolts(ADC_GetResult16());
            if ((int)((float)adc_bat_value*V_DIV) < 7150) {
                LED_ON
                COAST_OFF
                robot_direction = STAT;
                
                PWM_1_Stop();
                PWM_2_Stop();
                
                QuadDec_M1_Stop();
                QuadDec_M2_Stop();
                
                ADC_Stop();
                isr_eoc_Stop();
                
                Timer_TS_Stop();
                isr_TS_Stop();
                
                break;
            }
            flag_adc_ready = 2;
        }
    }
    return 0;
}
//* ========================================
//* PATH */
//* ========================================
//* Path Generation Logic */
//* ========================================
/*
Return the path distance to visit every given food_list item
from the current robot x,y coordinates.
*/
uint16 get_food_list_path_length()
{
    // initialise variables
    uint8 pos[2] = {robot_y_pos, robot_x_pos};
    uint8 des[2];
    int8 temp_path[num_map_nodes][2];
	init_path(temp_path, num_map_nodes);
    uint16 path_length = 0;
    
    // find length of path to visit every food list item
    int i;
    for (i = 0; i < FOOD; i++) {
        // set current food list item as destination
        des[0] = food_list[i][0];
        des[1] = food_list[i][1];
        // find distatnce 
		uint16 dist = find_shortest_path(pos, des, temp_path);
        // return INF if one of the food list items is not reachable
		if (dist == INF)
			return INF;
		else 
			path_length += dist;
        // set next pos to current found food list item
        pos[0] = des[0];
        pos[1] = des[1];
    }
    return path_length;
}
//* ========================================
/*
Return the path distance to visit every node on the given map
from the current robot x,y coordinates.
*/
uint16 get_traverse_path_length()
{
    // initialise variables
    uint8 pos[2] = {robot_y_pos, robot_x_pos};
	uint16 path_length_temp = 2*ROW*COL;
    int8 temp_path[path_length_temp][2];
	init_path(temp_path, path_length_temp);
    // return length of path
    return find_traverse_path(pos, temp_path);
}
//* ========================================
/*
Generate and return the path to visit every given food_list item
from the current robot x,y coordinates.
*/
void generate_food_list_path(int8 path[][2], uint16 path_length)
{
    // initialise variables
    uint8 pos[2] = {robot_y_pos, robot_x_pos};
    uint8 des[2];
    int8 temp_path[path_length][2];
	init_path(temp_path, path_length);
    uint16 current_path_length = 0;
    
    int i;
    for (i = 0; i < FOOD; i++) {
        // set current food list item as destination
        des[0] = food_list[i][0];
        des[1] = food_list[i][1];
        // generate path from pos to des
		uint16 j = current_path_length;
        current_path_length += find_shortest_path(pos, des, temp_path);
        // concatenate generated path to total path
		int k = 0;
        while (j < current_path_length) {
            path[j][0] = temp_path[k][0];
            path[j][1] = temp_path[k][1];
            j++;
			k++;
        }
        // set next pos to current found food list item and reset temp path
        pos[0] = des[0];
        pos[1] = des[1];
		init_path(temp_path, path_length);
    }
}
//* ========================================
/*
Generate and return the path distance to visit every node on the given map
from the current robot x,y coordinates.
*/
void generate_traverse_path(int8 path[][2])
{
    // initialise position
    uint8 pos[2] = {robot_y_pos, robot_x_pos};
    // generate path
    find_traverse_path(pos, path);
}
//* ========================================
//* Path Algorithms */
//* ========================================
/*
Generate the shortest path between a position and destination
using A* path finding algorithm and return the path distance.
If the destination is not reachable return INF.
*/
uint16 find_shortest_path(uint8 pos[2], uint8 des[2], int8 path[][2])
{
    // define arrays
	uint8 nodes[num_map_nodes][2];      // traverseable map nodes
	uint8 cons[num_map_nodes];          // nodes considered by algorithm
	float heurst[num_map_nodes];        // heuristic dist from pos to each map node
	uint16 dist[num_map_nodes];         // path dist from pos to each map node
	float d_h[num_map_nodes];           // heust dist + path dist for each node
	int8 prev[num_map_nodes][2];        // previous node used to reach map node
    
    // init arrays
	uint16 i = 0;
    int r, c;
	for (r = 0; r < ROW; r++) {
		for (c = 0; c < COL; c++) {
			if (!map[r][c]) {
				nodes[i][0] = r;
				nodes[i][1] = c;
				cons[i] = 0;
                // straight line distance
				heurst[i] = sqrt(pow((des[0]-r),2) + pow((des[1]-c),2));
				dist[i] = INF;
				d_h[i] = INF;
				prev[i][0] = -1;
				prev[i][1] = -1;
				i++;
			}
		}
	}
	
	// return INF if pos and des are not traveseable nodes
	int32 pos_index = get_node_index(pos, nodes);
	int32 des_index = get_node_index(des, nodes);
	if (pos_index == -1 || des_index == -1)
		return INF;
	
	// init dist parameters for starting pos
	dist[pos_index] = 0;
	d_h[pos_index] = heurst[pos_index];
    
    // Perform A* by considering every closest non-considered reachable node
    // and finding the distance to all surrounding nodes.
    // while loop should never run more times than there are nodes
    uint16 safety = 0;
	while (safety < num_map_nodes) {
        // find non-considered node with smallest path + heurst dist
		int32 cur_node_index = get_array_min_index(d_h, cons);
        // end algorithm if current node is des or all nodes have been considered
		if (cur_node_index == get_node_index(des, nodes) || cur_node_index == -1)
		    break;
	    
        // find all non-considered nodes next to current node
        i = 0;
	    while (i < num_map_nodes) {
			uint8 node_1[2] = {nodes[i][0], nodes[i][1]};
			uint8 node_2[2] = {nodes[cur_node_index][0], nodes[cur_node_index][1]};
	        if (!cons[i] && is_next_to(node_1, node_2)) {
	            dist[i] = 1 + dist[cur_node_index];     // weight of dist between nodes is 1
	            d_h[i] = dist[i] + heurst[i];
	            prev[i][0] = nodes[cur_node_index][0];
	            prev[i][1] = nodes[cur_node_index][1];
	        }
            i++;
	    }
	    cons[cur_node_index] = 1;
	    safety++;
	}
	
	// ensure des is reachable
	if (dist[des_index] == INF)
		return INF;
	
    // initialise variables to retrieve the reversed path to des
	int8 reverse_path[num_map_nodes][2];
	init_path(reverse_path, num_map_nodes);
	uint8 cur_path_node[2] = {des[0], des[1]};
	
    // Start at the des node and add the prev node to reversed path
    // until pos node is reached.
    // while loop should never run more times than there are nodes
	i = 0;
	safety = 0;
	while (safety < num_map_nodes) {
		// don't include pos node in path as it is already reached
		if (cur_path_node[0] == pos[0] && cur_path_node[1] == pos[1])
	        break;
		
        // add current path node to reverse path
        reverse_path[i][0] = cur_path_node[0];
        reverse_path[i][1] = cur_path_node[1];
		
        // set the prev node of current node as current node
        int32 cur_node_index = get_node_index(cur_path_node, nodes);
        cur_path_node[0] = prev[cur_node_index][0];
        cur_path_node[1] = prev[cur_node_index][1];
	    
	    i++;
	    safety++;
	}
	// if pos == des path is zero
	if (!i)
		return 0;
	
	// traverse backwards through the reverse path to generate path and
    // determine length of path
    int32 cur_node_index = num_map_nodes - 1;
	uint16 path_length = 0;
	// copy all non -1 elements in reverse path backwards to path
	while (cur_node_index >= 0) {
		if (reverse_path[cur_node_index][0] != -1) {
			path[path_length][0] = reverse_path[cur_node_index][0];
			path[path_length][1] = reverse_path[cur_node_index][1];
			path_length++;
		}
        cur_node_index--;
	}
	
	return path_length;
}
//* ========================================
/*
Generate the map traversal path from a starting position using a
combination of breadth-first and A* path finding algorithms to
ensure each map node is visited and return the path distance.
*/
uint16 find_traverse_path(uint8 pos[2], int8 path[][2])
{
    // init traversed map to be a copy of map
	int8 traversed_map[ROW][COL];
    uint8 r, c;
    for (r = 0; r < ROW; r++) {
		for (c = 0; c < COL; c++) {
			traversed_map[r][c] = map[r][c];
        }
    }
    // set starting pos as traversed
	traversed_map[pos[0]][pos[1]] = -1;
    
    // set initial orientation
	uint8 current_orientation = robot_orientation;
	int8* traverse_orientation = &orientation[current_orientation][0];
	uint8 original_orientation = UNKNOWN;
	#define NEXT_TRAVERSE_ROW pos[0]+(*traverse_orientation)
	#define NEXT_TRAVERSE_COL pos[1]+(*(traverse_orientation+1))
    
    uint16 path_length = 0;
	uint16 safety = 0;
	while (safety < 500) {
		// if next node in current orientation is empty and not traversed
		if (!traversed_map[NEXT_TRAVERSE_ROW][NEXT_TRAVERSE_COL]) {
            // move to next node and set current node as traversed
			pos[0] = NEXT_TRAVERSE_ROW;
			pos[1] = NEXT_TRAVERSE_COL;
			traversed_map[pos[0]][pos[1]] = -1;
            
			// add node moved to to path
			path[path_length][0] = pos[0];
			path[path_length][1] = pos[1];
			path_length++;
			
			original_orientation = UNKNOWN;
		}
		// if next point is wall
		else {
            // if other orientations not considered
			if (original_orientation == UNKNOWN) {
				// start turning process
				original_orientation = current_orientation;
				
				// change orientation to the right of current
				(current_orientation == LEFT) ? (current_orientation = UP) : (current_orientation++);
				traverse_orientation = &orientation[current_orientation][0];
			}
            // if all other orientations not yet considered
			else if (original_orientation != current_orientation) {
				// change orientation
				(current_orientation == LEFT) ? (current_orientation = UP) : (current_orientation++);
				traverse_orientation = &orientation[current_orientation][0];
			}
            // if all other orienations considered
			else if (original_orientation == current_orientation) {
				// find nearest non-traversed node
				uint8 map_traversed = 1;
				uint16 min_dist = INF;
                uint8 des[2];
				uint8 min_des[2] = {pos[0], pos[1]};
                for (r = 0; r < ROW; r++) {
            		for (c = 0; c < COL; c++) {
                        // find shortest distance to every non-traversed node
            			if (!traversed_map[r][c]) {
							des[0] = r;
							des[1] = c;
                            int8 temp_path[num_map_nodes][2];
							init_path(temp_path, num_map_nodes);
							uint16 dist = find_shortest_path(pos, des, temp_path);
                            // retain closest node
							if (dist < min_dist) {
								min_dist = dist;
								min_des[0] = r;
								min_des[1] = c;
								map_traversed = 0;
							}
						}
                    }
                }
                // if whole map has not been traversed 
				if (!map_traversed) {
                    // set destination to closest node
					des[0] = min_des[0];
					des[1] = min_des[1];
                    
                    // generate shortest path to closest node
                    int8 temp_path[min_dist][2];
                    init_path(temp_path, min_dist);
					find_shortest_path(pos, des, temp_path);
                    
                    // add shortest path to total path
                    uint16 i = 0;
                    while (i < min_dist) {
						path[path_length][0] = temp_path[i][0];
						path[path_length][1] = temp_path[i][1];
						path_length++;
                        i++;
                    }
					
					// reset path, pos and dir
					pos[0] = des[0];
					pos[1] = des[1];
                    traversed_map[pos[0]][pos[1]] = -1;
                    
                    // reset orientation
					current_orientation = UP;
					traverse_orientation = &orientation[current_orientation][0];
					original_orientation = UNKNOWN;
				}
				else {
					return path_length;
				}
			}
		}
		safety++;
	}
    return 0;
}
//* ========================================
//* Path Assistant Functions */
//* ========================================
/*
Return number of traverseable nodes in the given map
*/
void get_num_map_nodes()
{
	int r, c;
    for (r = 0; r < ROW; r++) {
		for (c = 0; c < COL; c++) {
			if (!map[r][c])
				num_map_nodes++;
        }
    }
}
//* ========================================
/*
Set each value of path to -1
*/
void init_path(int8 path[][2], uint16 path_length)
{
    uint16 i = 0;
	while (i < path_length) {
		path[i][0] = -1;
		path[i][1] = -1;
        i++;
	}
}
//* ========================================
/*
Return index of specified node in array of nodes.
If node does not exist return -1.
*/
int32 get_node_index(uint8 node[2], uint8 nodes[][2])
{
    int32 i = 0;
	while (i < num_map_nodes) {
		if (node[0] == nodes[i][0] && node[1] == nodes[i][1])
			return i;
        i++;
	}
	return -1;
}
//* ========================================
/*
Find non-considered node with minimum value.
If all nodes have been considered return -1.
*/
int32 get_array_min_index(float array[], uint8 cons[])
{
	// find first non considered element in array
    int32 min = -1;
    uint16 i = 0;
    while (i < num_map_nodes) {
        if (!cons[i]) {
            min = i;
            break;
        }
        i++;
    }
	// return if all elements have been considered
    if (min == -1)
        return -1;
    
	// find min non-considered element in array
    i = 0;
    while (i < num_map_nodes) {
        if (array[i] < array[min] && !cons[i])
            min = i;
        i++;
    }
    return min;
}
//* ========================================
/*
Return whether two nodes are adjacent to each other.
*/
uint8 is_next_to(uint8 node_1[2], uint8 node_2[2])
{
    if (((node_1[0]==node_2[0]-1 || node_1[0]==node_2[0]+1) && node_1[1]==node_2[1]) ||
			((node_1[1]==node_2[1]-1 ||  node_1[1]==node_2[1]+1) && node_1[0]==node_2[0]))
        return 1;
    return 0;
}
//* ========================================
//* TACHO */
//* ========================================
//* Robot Path Follower Logic */
//* ========================================
/*
Use robot sensors and logic to follow along the given path.
This is done by determining what the next event will be that
is reached by the robot; intersection, deadend, or u-turn in
middle of straight line.
Intersection light sensors are used to detect intersection.
Centre light sensor is used to detect dead end.
Quadrature is used to determine if u-turn point is reached.
When even is reached robot decides whether to turn or continue
straight and then finds next event.
Return 0 if end of path is rechead otherwise return 1.
*/
uint8 follow_path(int8 path[][2], uint16 path_length)
{
    // determine whether path event has changed path orienatation and turn accordingly
	if (flag_new_path_index) {
        // return 0 if end of path is reached
        if (path_index == path_length-1)
            return 0;
		// otherwise determine whether current orientation follows path
		else if (NEXT_ROW(path_index) != path[path_index+1][0] || NEXT_COL(path_index) != path[path_index+1][1]) {
            // turn robot and reset quadrature if path does not continue straight ahead
            turn_robot(path);
            //flag_turning = 1;
        }
        // reset flag
		flag_new_path_index = 0;
	}
	// find next intersection, dead end or pellet in line event on path
	else if (next_event_index == path_index) {
        get_next_event_index(path, path_length);
    }
    // poll quadrature to determine robot position if next event is pellet in line
    else if (flag_next_event_u_turn) {
        if (robot_position_index == next_event_index) {
            // update path index
            path_index = next_event_index;
            
            // set flags
    		flag_new_path_index = 1;
            flag_next_event_u_turn = 0;
        }
        else {
            follow_line();
            update_robot_position(path, path_length);
        }
    }
    // ensure centre sensor is back on line before polling for dead ends after turn
    else if (flag_next_event_deadend) {
        // poll centre sensor for dead ends if next event is dead end
        if (flag_centre_on_line_after_turn && !line_sensor_centre) {
            // update path index
    		path_index = next_event_index;
            flag_new_path_index = 1;
            
            // set robot position as light sensor events take priority over quadrature measures
            robot_y_pos = path[path_index][0];
            robot_x_pos = path[path_index][1];
            robot_position_index = path_index;
            
            // reset flag
            flag_next_event_deadend = 0;
            flag_centre_on_line_after_turn = 0;
        }
        else if (!flag_centre_on_line_after_turn && line_sensor_centre)
            flag_centre_on_line_after_turn = 1;
        else
    		follow_line();
    }
    // poll intersection sensors for intersection events
	else if (flag_next_event_intersection) {
        // move past intersection before updating position and path index
        if (flag_passing_next_int) {
            // once past intersection so robot centre is on intersection
    		if (!int_sensor_left && !int_sensor_right) {
                // update path index
    			path_index = next_event_index;
    			flag_new_path_index = 1;
                
                // set robot position as light sensor events take priority over quadrature measures
                robot_y_pos = path[path_index][0];
                robot_x_pos = path[path_index][1];
                robot_position_index = path_index;
                
                // reset flags
                flag_passing_next_int = 0;
                flag_next_event_intersection = 0;
    		}
    		else
    			follow_line();
        }
        else if (int_sensor_left || int_sensor_right)
		    flag_passing_next_int = 1;
        else
    		follow_line();
    }
	return 1;
}
//* ========================================
/*
Uses light sensors to follow along a straight line, ignoring intersections.
*/
void follow_line()
{
    // both line sensors off line and veering -> move straight
    if (!line_sensor_left && !line_sensor_right && flag_veering) {
        PWM_2_WriteCompare(pwm_cmp_right);
        flag_veering = 0;
    }
    // left line and int on line -> ignore intersection
    else if (line_sensor_left && int_sensor_left) {
        // use line right to keep straight
        if (line_sensor_right && !flag_veering) {
            PWM_2_WriteCompare(pwm_cmp_right - PWM_VEER_ADJUST);
            flag_veering = 1;
        }
        else if (!line_sensor_right && flag_veering) {
            PWM_2_WriteCompare(pwm_cmp_right);
            flag_veering = 0;
        }
    }
    // right line and int on line -> ignore intersection
    else if (line_sensor_right && int_sensor_right) {
        // use line left to keep straight
        if (line_sensor_left && !flag_veering) {
            PWM_2_WriteCompare(pwm_cmp_right + PWM_VEER_ADJUST);
            flag_veering = 1;
        }
        else if (!line_sensor_left && flag_veering) {
            PWM_2_WriteCompare(pwm_cmp_right);
            flag_veering = 0;
        }
    }
    // follow line -> no intersection
    else if (line_sensor_left && !int_sensor_left && !flag_veering) {
        PWM_2_WriteCompare(pwm_cmp_right + PWM_VEER_ADJUST);
        flag_veering = 1;
    }
    else if (line_sensor_right && !int_sensor_right && robot_direction != TURNING_RIGHT) {
        PWM_2_WriteCompare(pwm_cmp_right - PWM_VEER_ADJUST);
        flag_veering = 1;
    }
}
//* ========================================
/*
Determines whether robot must turn left, right or around to stay on
path and turns robot.
*/
void turn_robot(int8 path[][2])
{
    // stop robot
    CyDelay(80);
    COAST_OFF
    CyDelay(200);
    
    // ensure pwm values not for veering so they are equal
    PWM_2_WriteCompare(pwm_cmp_right);
    flag_veering = 0;
    
    uint8 new_orient;
    // check if robot needs to turn left to follow path
    (robot_orientation == UP) ? (new_orient = LEFT) : (new_orient = robot_orientation - 1);
    if (PATH_CHANGED_TO(new_orient)) {
        // turn robot left
        robot_orientation = new_orient;
        path_orientation = &orientation[robot_orientation][0];
        TURN_LEFT
        robot_direction = TURNING_LEFT;
    }
    
    // check if robot needs to turn right or around to follow path
    if (robot_direction != TURNING_LEFT) {
        // if robot does not need to turn right it needs to turn around
        (robot_orientation == LEFT) ? (new_orient = UP) : (new_orient = robot_orientation + 1);
        if (!PATH_CHANGED_TO(new_orient)) {
            flag_turn_around = 1;
            // set new orienattion to 180 degrees
            (new_orient == LEFT) ? (robot_orientation = UP) : (robot_orientation = new_orient + 1);
        }
        else
            robot_orientation = new_orient;
        // turn robot
        path_orientation = &orientation[robot_orientation][0];
        TURN_RIGHT
        robot_direction = TURNING_RIGHT;
    }
    
    // reset quadrature and start robot so it starts turning
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    COAST_ON
    
    // measure quadrature to turm either 90 or 180 degrees
    uint8 turn_quad;
    (flag_turn_around) ? (turn_quad = 195) : (turn_quad = 93);
    do {
        get_wheel_quadrature();
        // once partial turn complete use line sensor to ensure not over turning
        if (quad_cnt_left > 120 && line_sensor_left) {
            break;
        }
    } while (quad_cnt_left < turn_quad);
    
    // stop robot
    COAST_OFF
    CyDelay(200);
    flag_turn_around = 0;
    
    // reset quadrature and start moving robot forward after turn
    MOVE_FORWARD
    robot_direction = FORWARD;
    QuadDec_M1_SetCounter(0);
    QuadDec_M2_SetCounter(0);
    COAST_ON
}
//* ========================================
//* Robot Sensors */
//* ========================================
void get_light_sensors()
{
    // read light sensors
    int_sensor_left = INT_SENSOR_LEFT_Read();
    int_sensor_right = INT_SENSOR_RIGHT_Read();
    line_sensor_centre = LINE_SENSOR_CENTRE_Read();
    line_sensor_left = LINE_SENSOR_LEFT_Read();
    line_sensor_right = LINE_SENSOR_RIGHT_Read();
}
//* ========================================
/*
Get the absolute values of the motor quadrature decoders.
*/
void get_wheel_quadrature()
{
    // get the quadrature counts
    quad_cnt_left = QuadDec_M1_GetCounter();
    quad_cnt_right = QuadDec_M2_GetCounter();
    
    // take the absolute of the quadrature counts
    if (quad_cnt_left < 0)
        quad_cnt_left = quad_cnt_left * -1;
    if (quad_cnt_right < 0)
        quad_cnt_right = quad_cnt_right * -1;
}
//* ========================================
/*
Get the distance travelled along a straight line using motor quadrature.
Update distance every quarter wheel rotation.
*/
void get_distance()
{
    get_wheel_quadrature();
    
    // reset prev value if quadrature has been reset
    if (quad_cnt_left < quad_cnt_prev) {
        quad_cnt_prev = quad_cnt_left;
        straight_line_distance = 4;
    }
    
    // if difference between prev value and quad cnt is a quarter turn
    // update distance and update prev
    if (quad_cnt_left - quad_cnt_prev >= QUARTER_ROT) {
        straight_line_distance += QUARTER_CIRC;
        quad_cnt_prev = quad_cnt_left;
    }
}
//* ========================================
/*
Finds what the next map event is along the given path,
update index flag of next event and set appropriate event flag.
Events include intersections, deadends and the path changing
orientation by 180 degrees in the middle of a straight line (u-turn).
*/
void get_next_event_index(int8 path[][2], uint16 path_length)
{
    // loop through remainder of path from path index and look for next event
    uint16 i;
    (!path_index) ? (i = 0) : (i = path_index + 1);
	while (i < path_length) {
        // look for intersections
		if (robot_orientation == UP || robot_orientation == DOWN) {
			// look left and right for intersection
			if (!map[path[i][0]][path[i][1]-1] || !map[path[i][0]][path[i][1]+1]) {
				next_event_index = i;
                flag_next_event_intersection = 1;
				break;
			}
        }
        else if (robot_orientation == LEFT || robot_orientation == RIGHT) {
			// look up and down for intersection
			if (!map[path[i][0]-1][path[i][1]] || !map[path[i][0]+1][path[i][1]]) {
				next_event_index = i;
                flag_next_event_intersection = 1;
				break;
			}
        }
        // look ahead for dead end
        if (map[NEXT_ROW(i)][NEXT_COL(i)]) {
            next_event_index = i;
            flag_next_event_deadend = 1;
			break;
        }
        // if final path node is not intersection or dead end it must be pellet in line
        else if (i == path_length - 1) {
            next_event_index = i;
            flag_next_event_u_turn = 1;
			break;
        }
        // if no intersections or dead ends found and not end of end of path look u-turn in path
        else {
            // if path does not follow straight ahead it must be a u-turn as no intersections or
            // dead ends were found
            if (NEXT_ROW(i) != path[i+1][0] || NEXT_COL(i) != path[i+1][1]) {
                next_event_index = i;
                flag_next_event_u_turn = 1;
    			break;
            }
        }
        i++;
	}
}
//* ========================================
/*
Update robot position based on the distance travelled along a straight line.
*/
void update_robot_position(int8 path[][2], uint16 path_length)
{
    get_distance();
    
    // reset prev value if distance has been reset
    if (straight_line_distance < distance_prev)
        distance_prev = 0;
    
    // if difference between prev value and distance is a physical
    // projected map block distance update robot position and prev
    if (straight_line_distance - distance_prev >= BLOCK_DIST) {
        robot_position_index++;
        if (robot_position_index < path_length) {
            // set robot position
            robot_y_pos = path[robot_position_index][0];
            robot_x_pos = path[robot_position_index][1];
        }
        distance_prev = straight_line_distance;
    }
}
//* ========================================
//* USBUART */
//* ========================================
void usbPutString(char *s)
{
// !! Assumes that *s is a string with allocated space >=64 chars     
//  Since USB implementation retricts data packets to 64 chars, this function truncates the
//  length to 62 char (63rd char is a '!')

#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    s[63]='\0';
    s[62]='!';
    USBUART_PutData((uint8*)s,strlen(s));
#endif
}
//* ========================================
void usbPutChar(char c)
{
#ifdef USE_USB     
    while (USBUART_CDCIsReady() == 0);
    USBUART_PutChar(c);
#endif    
}
//* ========================================
/* [] END OF FILE */
