/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_scenario.c
*
* @brief Description 	:	This defines implementation for scenario object.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lc_defs.h>
#include <lc_scenario.h>
#include <lc_trace.h>
#include <lc_scenario.h>
#include <lc_api.h>
#include <lc_parser.h>
#include <lc_position.h>

const char *s_suffix = "_proc";

/*  Error strings have to be ordered as per the enum in lc_api.h*/
char *z_errors[] = {
	"Never seee this value!",
	"Exceeded number of allowed stations",	//LC_NUMSTATIONS_EXCEEDED
	"Failed to create output file",			//LC_SCENARIO_OUTFILE_CREATE_FAILED,
	"Failed to allocate memory",			//LC_SCENARIO_MEMALLOC_FAIL,
	"Scenario file not found",				//LC_SCENARIO_FILENOTFOUND,
	"Incorrectly formatted line in scenario file",
											//LC_WRONG_TOALINE_FORMAT,
	"LC generic error",						//LC_ERROR,
	"End of scenario input file",			//LC_EOF,
	"OK"									//LC_OK
};

struct lc_scenario *lc_initScenario(char *p_scenarioName)
{
	struct lc_scenario *p_scenario = (struct lc_scenario *)malloc(sizeof(struct lc_scenario));
	int len = strlen(p_scenarioName);
	uint8 u_i;

	if (p_scenario == NULL)
	{
		/* Failed to allocate memory for scenario object */
		return NULL;
	}

	memset(p_scenario, 0, sizeof(struct lc_scenario));

	/* Reset the error state */
	p_scenario->x_lastError = LC_OK;

	p_scenario->s_scenarioFileName = (char *)malloc((len + 1) * sizeof(char));
	if (p_scenario->s_scenarioFileName == NULL)
	{
		/* Failed to allocate memory for scenario file name, set error state */
		p_scenario->x_lastError = LC_SCENARIO_MEMALLOC_FAIL;
		return p_scenario;
	}

	/* Store scenario file name */
	strcpy(p_scenario->s_scenarioFileName, p_scenarioName);
	
	p_scenario->h_File = fopen(p_scenario->s_scenarioFileName, "r");
	if (p_scenario->h_File == NULL)
	{
		/* Failed to open scenario input file, set error state */
		p_scenario->x_lastError = LC_SCENARIO_FILENOTFOUND;
		return p_scenario;
	}

	p_scenario->s_outputFileName = (char *)malloc((len + 1 + strlen(s_suffix)) * sizeof(char));
	if (p_scenario->s_outputFileName == NULL)
	{
		/* Failed to allocate memory for scenario output file name, set error state */
		p_scenario->x_lastError = LC_SCENARIO_MEMALLOC_FAIL;
		return p_scenario;
	}

	strcpy(p_scenario->s_outputFileName, p_scenario->s_scenarioFileName);
	
	/* Look for the '.' in the last 10 char of the file name */
	for (u_i = len - 1; u_i > (len - 10) && u_i != 0; u_i--)
	{
		if (p_scenario->s_scenarioFileName[u_i] == '.')
		{
			p_scenario->s_outputFileName[u_i] = '\0';
			break;
		}
	}

	/* Append suffix and store output file name 
	 * TBD: Consider adding a timestamp to prevent file over write on each run 
	 */
	sprintf(p_scenario->s_outputFileName, "%s%s.csv", p_scenario->s_outputFileName, s_suffix);

	p_scenario->h_outputFile = fopen(p_scenario->s_outputFileName, "w");
	if (p_scenario->h_outputFile == NULL)
	{
		/* Failed to open scenario output file, set error state */
		p_scenario->x_lastError = LC_SCENARIO_OUTFILE_CREATE_FAILED;
		return p_scenario;
	}

	/* All Ok, set the scenario state variables*/
	p_scenario->u_firstFix = 1;
	
	for (u_i = 0; u_i < LC_MAX_STATIONS; u_i++)
	{
		p_scenario->d_rangePrev[u_i] = -1;
	}

	return p_scenario;
}

void lc_addStations(struct lc_scenario *p_scenario, uint8 u_numStations, dbl *d_loc)
{
	uint8 u_i;

	/* Reset the error state */
	p_scenario->x_lastError = LC_OK;

	/* Only LC_MAX_STATIONS are supported*/
	if (u_numStations > LC_MAX_STATIONS)
	{
		p_scenario->x_lastError = LC_NUMSTATIONS_EXCEEDED;
		return;
	}

	/* No error check here, implicit assumption is that d_loc is big
	 * enough to hold u_numStations worth of (x,y)
	*/

	p_scenario->u_numStations = u_numStations;

	/* Extract and store station (x,y)*/
	for (u_i = 0; u_i < u_numStations; u_i++)
	{
		p_scenario->z_signalInfo[u_i].z_Loc[0] = d_loc[u_i * 2];
		p_scenario->z_signalInfo[u_i].z_Loc[1] = d_loc[u_i * 2 + 1];
		p_scenario->z_signalInfo[u_i].w_status_flag |= (LC_BIT_POSVALID);

	}
}

void lc_processScenario(struct lc_scenario *p_scenario)
{
	/* Reset the error state */
	p_scenario->x_lastError = LC_OK;

	if (p_scenario->u_firstFix == 1)
	{
		/* For the first fix, we don't have any prior Rx position 
		 * Use a random point as seed.
		 */
		p_scenario->z_rxPosition.d_xyt[0] = 100;
		p_scenario->z_rxPosition.d_xyt[1] = 200;
		p_scenario->z_rxPosition.d_xyt[2] = 0;
	}

	while(1) // Continue till TOA Fill returns EOF or error
	{
		if (lc_fillInputToa(p_scenario) != LC_OK)
			break;

		/* Successful attempt, increment counter*/
		p_scenario->u_numAttempts++;

		/* Calculate Pseudo ranges */
		lc_genPseudoRange(p_scenario);

		/* Attempt position update*/
		lc_calcPosition(p_scenario);
	}

}

sint8 lc_getLastError(struct lc_scenario *p_scenario)
{
	return p_scenario->x_lastError;
}

char *lc_getLastErrorVerbose(sint8 u_error)
{
	/* Return pointer to error strings*/
	return z_errors[u_error - LC_MIN_ENUM_VAL];
}

void lc_exitScenario(struct lc_scenario *p_scenario)
{
	/* Clean-up scenario object */
	if (p_scenario != NULL)
	{
		if (p_scenario->s_scenarioFileName != NULL)
			free(p_scenario->s_scenarioFileName);

		if (p_scenario->s_outputFileName != NULL)
			free(p_scenario->s_outputFileName);
		
		if (p_scenario->h_File != NULL)
			fclose(p_scenario->h_File);
		
		if (p_scenario->h_outputFile != NULL)
			fclose(p_scenario->h_outputFile);

		free(p_scenario);
	}
}

void lc_getScenarioStat(struct lc_scenario *p_scenario, lc_stats *p_stats)
{
	p_stats->p_scenarioName = p_scenario->s_scenarioFileName;
	p_stats->u_numAttempts = p_scenario->u_numAttempts;
	p_stats->u_numFixes = p_scenario->u_numFixes;
}