/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_scenario.h
*
* @brief Description 	:	This defines the scenario object and functions.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_SCENARIO_H_
#define _LC_SCENARIO_H_

#include<stdio.h>
#include <lc_defs.h>
#include <lc_signalMeas.h>
#include <lc_position.h>

struct lc_scenario {
	/* Public */
	char	*s_scenarioFileName;
	uint8	u_numStations;

	/* Processing */
	char	*s_outputFileName;
	FILE	*h_File;
	FILE	*h_outputFile;
	sint8	x_lastError;
	uint8	u_numAttempts;		/* Number if fix attempts */
	uint8	u_numFixes;			/* Number of valid fixes */
	uint8	u_firstFix;			/* 1 -> First fix attempt*/
	uint32	q_ints;				/* Timstamp in seconds */
	dbl		d_rangePrev[4];		/* Previous epoch range */
	signalMeas	
			z_signalInfo[4];	/* Store the ranges for the epoch*/
	lc_rxPosition	z_rxPosition;
								/* Store the position reports for the epoch */
};

#endif