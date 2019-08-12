/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_locatorApp.c
*
* @brief Description 	:	This implements the main locator application.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <lc_defs.h>
#include <lc_api.h>

dbl d_TxLocStore[] = {
	   0,        0,
	   1000,     0,
	   1000,  1000,
	   2000, -1000
};

void checkForErrors(struct lc_scenario *p_scenario)
{
	sint8 x_error;

	x_error = lc_getLastError(p_scenario);

	if (x_error != LC_OK)
	{
		printf("Application exited with error code %d: %s\n", x_error, lc_getLastErrorVerbose(x_error));
		lc_exitScenario(p_scenario);
		exit(-1);
	}
}

void main(int argc, char **argv)
{
	uint8 u_i;
	
	/* Need atleast one scenario file to process*/
	if (argc < 2)
	{
		printf("Usage: Locator filename [filename]...\n");
		exit(-1);
	}

	for (u_i = 1; u_i < argc; u_i++)
	{
		struct lc_scenario *p_scenario;

		/* Initialize the scenario*/
		p_scenario = lc_initScenario(argv[u_i]);

		if (p_scenario == NULL)
		{
			printf("Failed to create scenario object\n");
			exit(-1);
		}

		checkForErrors(p_scenario);

		/* Inject the stations (X,Y) */
		lc_addStations(p_scenario, 4, d_TxLocStore);

		checkForErrors(p_scenario);

		/* This is a good point to spawn a thread for parallel processing */
		/* TBD */

		/* All set, process the position computations */
		lc_processScenario(p_scenario);

		if (lc_getLastError(p_scenario) == LC_OK)
		{
			lc_stats z_stats;

			/* Succesfully processed, print the yield */
			lc_getScenarioStat(p_scenario, &z_stats);

			/* Print Scenario statistics */
			printf("Processed Scenario: %s, Yield: %3.1f%%\n", z_stats.p_scenarioName, z_stats.u_numFixes / (flt) z_stats.u_numAttempts * 100);
		}
		else
		{
			/* Something went wrong, print and exit */
			checkForErrors(p_scenario);
		}

		lc_exitScenario(p_scenario);
	}
}