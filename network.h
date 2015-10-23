/* 
 * network.h: Virtual Machine Placement Problem - Networking Functions Header
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
/* definitions */
#define T_HEADER "NETWORK TRAFFIC"
#define L_HEADER "NETWORK TOPOLOGY"
#define C_HEADER "NETWORK LINK CAPACITY"
#define TAM_BUFFER BUFSIZ
/* get the number of network links */
int get_l_size(char path_to_file[]);
/* load datacenter network topology */
int** load_T(int v_size, char path_to_file[]);
int** load_G(int h_size, int l_size, char path_to_file[]);
int* load_K(int l_size, char path_to_file[]);
/* load utilization of network resources */
int* load_network_utilization(int *individual, int **G, int **T, int l_size, int v_size);
int** load_population_network_utilization(int **population, int **G, int **T, int number_of_individuals, int l_size, int v_size);
