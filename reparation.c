/* 
 * reparation.c: Virtual Machine Placement Problem - Reparation Stage
 * Date: 23-10-2015
 * Author: Fabio Lopez Pires (flopezpires@gmail.com)
 * Corresponding article: "Many-Objective Virtual Machine Placement". Journal of Grid Computing.
 */

/* include reparation stage header */
#include "reparation.h"

/* check_individual: repairs not factible individuals
 * parameter: population matrix
 * parameter: utilization of the physical machines matrix
 * parameter: physical machines matrix
 * parameter: virtual machines matrix
 * parameter: number of individuals
 * parameter: number of physical machines
 * parameter: number of virtual machines
 * parameter: identificator of the not factible individual to repair
 * returns: nothing, it's void()
 */
int check_individual(int * individual, int ** H, int ** V, int **utilization, int *network_utilization, int h_size, int v_size, int l_size, int max_SLA)
{
	int iterator_virtual = 0;
	int factibility = 1;
	for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
        {
        	if (V[iterator_virtual][3] == max_SLA && individual[iterator_virtual] == 0)
                {
                	factibility=0;
			break;
                }
        }	
	/* iterate on each virtual machine to search for overloaded physical machines */
	for (iterator_virtual = 0; iterator_virtual < v_size; iterator_virtual++)
	{
		/* if the virtual machine was placed */
		if (individual[iterator_virtual] != 0)
		{
			/* verify is the physical machine assigned is overloaded in any physical resource */
			if (is_overloaded(H, utilization, individual[iterator_virtual]-1))
			{
                		factibility=0;
				break;
			}
		}
	}
	if (!factibility)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/* is_overloaded: verificates if a physical machine is overloaded
 * parameter: physical machine resources matrix
 * parameter: utilization of the physical machines matrix
 * parameter: identificator of the individual
 * parameter: identificator of the physical machine
 * returns: 1 if yes, 0 if no
 */
int is_overloaded(int ** H, int ** utilization, int physical)
{
	/* If the use of the VM exceeds the capacity of the physical machine return 1, otherwise return 0 */
	if ((utilization[physical][0] > H[physical][0]) 
	||  (utilization[physical][1] > H[physical][1])
	||  (utilization[physical][2] > H[physical][2]))
	{
		return 1;
	}
	return 0;
}
