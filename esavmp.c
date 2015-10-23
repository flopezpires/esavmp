/* 
 * esavmp.c: Exhaustive Search Algorithm (ESA) for Many-Objective Virtual Machine Placement (MaVMP)
 * Date: 23-10-2015
 * Author: Fabio Lopez Pires (flopezpires@gmail.com)
 * Corresponding article: "Many-Objective Virtual Machine Placement". Journal of Grid Computing.
 */

/*
 * TODO: 
 * 1. MAX_SLA as argv[]
 * 2. datacenter file parsing
 * 3. code optimization
 */
  
/* structure of a Pareto element */
struct pareto_element{
	int *solution;
	float *costs;
	struct pareto_element *prev;
	struct pareto_element *next;
};

/* include libraries */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/* include own headers */
#include "common.h"
#include "reparation.h"
#include "network.h"
#include "pareto.h"
#include "variation.h"
/* definitions */
#define MAX_SLA 1

/* main: Exhaustive Search Algorithm (ESA) for Many-Objective Virtual Machine Placement (MaVMP)
 * parameter: path to the datacenter file
 * returns: exit state
 */
int main (int argc, char *argv[]) {
    /* parameters verification */	
	if (argc == 1)
	{
		/* wrong parameters */	
		printf("[ERROR] usage: %s datacenter_file\n", argv[0]);
		/* finish him */
		return 1;
	}
    /* good parameters */	
	else
	{
		/* get the number of physical machines, virtual machines and network links from the datacenter file (argv[1] = path to the datacenter file) */
		int h_size = get_h_size(argv[1]);
		int v_size = get_v_size(argv[1]);
		int l_size = get_l_size(argv[1]);
		/* load physical machines resources, virtual machines requirements and network topology from the datacenter file */
		int **H = load_H(h_size, argv[1]);
		int **V = load_V(v_size, argv[1]);
		int **T = load_T(v_size, argv[1]);
		int **G = load_G(h_size, l_size, argv[1]);
		int *K 	= load_K(l_size, argv[1]);

		printf("\nDATACENTER LOADED SUCCESSFULLY\n");
		printf("\nPMS: %d\tVMs: %d\tNetwork Links: %d\n",h_size,v_size,l_size);

		/* general purpose variables */
		int iterator_individual;
		int value;
		int iterator = 0;
		int iterator_feasible = 0;
		struct pareto_element *pareto_head = NULL;
		int H_size = h_size+1;
		int *physical_machines = (int *) malloc (H_size *sizeof (int));

		/* load the physical machine position */
		for (iterator_individual = 0 ; iterator_individual < H_size ; iterator_individual ++)
		{
			physical_machines[iterator_individual] = iterator_individual;
		}
		/* auxiliary matrix */
		int *auxiliary_matrix = (int *) malloc (v_size *sizeof (int));
		/* initializes the auxiliary_matrix with zero */
		for (iterator_individual = 0 ; iterator_individual < v_size ; iterator_individual ++)
		{
			  auxiliary_matrix[iterator_individual] = 0;
		}
		do
		{
			int *individual = (int *) malloc (v_size *sizeof (int));
			for (iterator_individual = 0 ; iterator_individual < v_size ; iterator_individual++)
			{
				individual[iterator_individual] = physical_machines[auxiliary_matrix[iterator_individual]];
			}
			int **utilization = (int **)load_utilization(individual, H, V, h_size, v_size);	
			int *network_utilization = (int *)load_network_utilization(individual, G, T, l_size, v_size);
			if(check_individual(individual, H, V, utilization, network_utilization, h_size, v_size, l_size, MAX_SLA)==1)
			{
				float *objectives_functions = load_objectives(individual, utilization, H, V, T, h_size, v_size, K, network_utilization, l_size);
				pareto_head = (struct pareto_element *) pareto_insert(pareto_head,v_size,individual,objectives_functions);
				iterator_feasible++;
			}
			else
			{
				free(individual);	
				free(network_utilization);
				for (iterator_individual = 0 ; iterator_individual < h_size ; iterator_individual++)
				{
					free(utilization[iterator_individual]);
				}
				free(utilization);
			}
			iterator++;
			for (iterator_individual = 0 ; iterator_individual < v_size && ++auxiliary_matrix[iterator_individual] == H_size; iterator_individual++)
			{
				auxiliary_matrix[iterator_individual] = 0;
			}

		} while (iterator_individual < v_size);
		
		/* final messages */
		printf("number of possible solutions (X): %d\n",iterator);
		printf("number of feasible solutions (X_f): %d\n",iterator_feasible);
		report_best_population(pareto_head, G, T, H, V, v_size, h_size, l_size);
		printf("\n");
		/* finish him */
		return 0;
	}
}