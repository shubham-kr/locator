/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_position.c
*
* @brief Description 	:	This defines implementation for the position computation
*							module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <lc_defs.h>
#include <lc_scenario.h>
#include <lc_position.h>
#include <lc_reports.h>
#include <lc_matInvGJE.h>
#include <lc_wls.h>
#include <lc_filter.h>

void lc_calcPosition(struct lc_scenario *p_scenario)
{
	uint8 u_numMeas;
	dbl d_RxHat[4];
	dbl d_PRange[4];
	dbl d_TxLoc[4 * 2];
	dbl d_RangeCurr[4];
	dbl d_residuals[4];
	dbl d_W[] = { 1,1,1,1 };
	uint8 u_i;

	u_numMeas = 0;

	/* Set up initial position */
	d_RxHat[0] = p_scenario->z_rxPosition.d_xyt[0];
	d_RxHat[1] = p_scenario->z_rxPosition.d_xyt[1];
	d_RxHat[2] = p_scenario->z_rxPosition.d_xyt[2];

	for (u_i = 0; u_i < LC_MAX_STATIONS; u_i++)
	{
		dbl d_range;

		d_range = p_scenario->z_signalInfo[u_i].d_pRange;

		if (d_range != -1)
		{
			/* Valid range */
			d_PRange[u_numMeas] = p_scenario->z_signalInfo[u_i].d_pRange;
			d_TxLoc[u_numMeas * 2] = p_scenario->z_signalInfo[u_i].z_Loc[0];
			d_TxLoc[u_numMeas * 2 + 1] = p_scenario->z_signalInfo[u_i].z_Loc[1];

			if (p_scenario->d_rangePrev[u_i] != -1)
			{
				/* if previous range information is available, perform filtering*/
				if (d_range - p_scenario->d_rangePrev[u_i] < LC_PRANGE_MAXJUMP_M)
				{
					/* Reasonbale change in range, allow it*/
					u_numMeas++;
					d_RangeCurr[u_i] = d_range;
				}
				else
				{
					/* Too much variation, mark invalid */
					d_RangeCurr[u_i] = p_scenario->d_rangePrev[u_i];
					p_scenario->z_signalInfo[u_i].w_status_flag &= (~LC_BIT_PRANGEVALID);
				}
			}
			else
			{
				/* No prior information, accept the measurement*/
				u_numMeas++;
				d_RangeCurr[u_i] = d_range;
			}

		}
		else
		{
			d_RangeCurr[u_i] = -1;
		}
	}

	/* Print PRNG message */
	lc_reportPrange(p_scenario);

	/* Try LS solution */
	if (lc_wls(d_TxLoc, d_PRange, d_W, u_numMeas, d_RxHat, d_residuals) == SUCCESS)
	{
		/* Success in LS, update position and report*/
		p_scenario->z_rxPosition.d_xyt[0] = d_RxHat[0];
		p_scenario->z_rxPosition.d_xyt[1] = d_RxHat[1];
		p_scenario->z_rxPosition.d_xyt[2] = d_RxHat[2];

		p_scenario->u_numFixes++;
		p_scenario->z_rxPosition.u_numStationsUsedInFix = u_numMeas;
		
		/* Extract residuals and perform position filtering */
		for(u_i = 0; u_i < u_numMeas; u_i++)
			p_scenario->z_rxPosition.d_residuals[u_i] = d_residuals[u_i];

		lc_fixFilterUpdate(p_scenario, d_residuals);

		p_scenario->u_firstFix = 0;

		lc_reportWLSFix(p_scenario, d_RxHat);
		lc_reportFilterFix(p_scenario);
	}

	for (u_i = 0; u_i < 4; u_i++)
	{
		p_scenario->d_rangePrev[u_i] = d_RangeCurr[u_i];
	}

}
