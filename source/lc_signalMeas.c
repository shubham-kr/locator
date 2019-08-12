/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_signalMeas.c
*
* @brief Description 	:	This defines implementation for the signal Measurement module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <stdio.h>
#include "lc_defs.h"
#include <lc_scenario.h>
#include <lc_api.h>
#include <lc_signalMeas.h>

void lc_genPseudoRange(struct lc_scenario *p_scenario)
{
	uint8 u_i;
	dbl		d_toa;
	uint32	q_ints;

	for (u_i = 0; u_i < LC_MAX_STATIONS; u_i++)
	{
		p_scenario->z_signalInfo[u_i].w_status_flag &= (~LC_BIT_PRANGEVALID);
		if (p_scenario->z_signalInfo[u_i].d_toa != -1)
		{
			d_toa = p_scenario->z_signalInfo[u_i].d_toa;
			/* Extract integer portion */
			q_ints = (int)d_toa;

			/* If  TOA is early, then integer portion has to be adjusted by 1s*/
			if ((d_toa - q_ints) > 0.5)
				q_ints += 1;

			/* Calcualte and set prange validity*/
			p_scenario->z_signalInfo[u_i].d_pRange = (d_toa - q_ints) * VLIGHT;
			p_scenario->z_signalInfo[u_i].w_status_flag |= (LC_BIT_PRANGEVALID);
		}
	}

	/* Use integer portion as a timestamp*/
	p_scenario->q_ints = q_ints;
}