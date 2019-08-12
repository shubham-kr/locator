/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_filter.c
*
* @brief Description 	:	This defines implementation for the position filter.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <lc_defs.h>
#include <lc_scenario.h>
#include <lc_filter.h>

void  lc_fixFilterUpdate(struct lc_scenario *p_scenario, dbl *d_residuals)
{
	dbl d_sseResiduals;
	uint8 u_i;
	dbl	k;

	d_sseResiduals = 0;
	if (p_scenario->z_rxPosition.u_numStationsUsedInFix == 3)
	{
		/* Residuals wil be ~0 for 3 measurement case, deweight the solution*/
		k = 10;
	}
	else
	{

		/* Get Sum squared errors for this epoch*/
		for (u_i = 0; u_i < p_scenario->z_rxPosition.u_numStationsUsedInFix; u_i++)
		{
			d_sseResiduals += (p_scenario->z_rxPosition.d_residuals[u_i] * p_scenario->z_rxPosition.d_residuals[u_i]);
		}

		if (d_sseResiduals < 10)
			k = 2;	/* Very Good convergence*/
		else if (d_sseResiduals < 50)
			k = 4;	/* Good convergence */
		else if (d_sseResiduals < 100)
			k = 8; /* Average convergence*/
		else
			k = 16; /* Poor convergence */
	}

	if (p_scenario->u_firstFix == 1)
	{
		/* Initialize the filter */
		p_scenario->z_rxPosition.d_xyFiltered[0] = p_scenario->z_rxPosition.d_xyt[0];
		p_scenario->z_rxPosition.d_xyFiltered[1] = p_scenario->z_rxPosition.d_xyt[1];
	}
	else
	{
		/* Weight the solution */
		p_scenario->z_rxPosition.d_xyFiltered[0] = ((k - 1) / k) * p_scenario->z_rxPosition.d_xyFiltered[0] + (1 / k ) * p_scenario->z_rxPosition.d_xyt[0];
		p_scenario->z_rxPosition.d_xyFiltered[1] = ((k - 1) / k) * p_scenario->z_rxPosition.d_xyFiltered[1] + (1 / k)  * p_scenario->z_rxPosition.d_xyt[1];
	}
}