/* 
 * reparation.h: Virtual Machine Placement Problem - Reparation Stage Header
 * Date: 23-10-2015
 * Author: Fabio Lopez Pires (flopezpires@gmail.com)
 * Corresponding article: "Many-Objective Virtual Machine Placement". Journal of Grid Computing.
 */

/* include libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/* function headers definitions */
int check_individual(int * individual, int ** H, int ** V, int **utilization, int *network_utilization, int h_size, int v_size, int l_size, int max_SLA);
int is_overloaded(int ** H, int ** utilization, int physical);
