/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_api.h
*
* @brief Description 	:	This defines interface for the Locator module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_API_H_
#define _LC_API_H_

#include "lc_defs.h"

enum {
	LC_MIN_ENUM_VAL = -8,
	LC_NUMSTATIONS_EXCEEDED = -7,
	LC_SCENARIO_OUTFILE_CREATE_FAILED = -6,
	LC_SCENARIO_MEMALLOC_FAIL = -5,
	LC_SCENARIO_FILENOTFOUND = -4,
	LC_WRONG_TOALINE_FORMAT = -3,
	LC_ERROR = -2,
	LC_EOF = -1,
	LC_OK = 0
} lc_errorCodes;

/* Forward declaration */
struct lc_scenario;

typedef struct {
	char *p_scenarioName;
	uint8	u_numAttempts;
	uint8	u_numFixes;
} lc_stats;

/**
* @brief Create and Initialize scenario
*
* @param p_scenarioName --> Name of scenario file
*
* @return Pointer to created scenario
*
*/
struct lc_scenario *lc_initScenario(char *p_scenarioName);

/**
* @brief Inject positions of base stations for the scenario
*
* @param p_scenarioName --> Pointer to scenario object
*
* @param u_numStations --> Number of stations
*
* @param d_loc --> Array of (x,y)
*
* @return None
*
*/
void lc_addStations(struct lc_scenario *p_scenario, uint8 u_numStations, dbl *d_loc);

/**
* @brief Process scenario for position computation
*
* @param p_scenarioName --> Pointer to scenario object
*
* @return Pointer to created scenario
*
*/
void lc_processScenario(struct lc_scenario *p_scenario);

/**
* @brief Used to obtain error after latest API call
*
* @param p_scenarioName --> Pointer to scenario object
*
* @return Error code from lc_errorCodes
*
*/
sint8 lc_getLastError(struct lc_scenario *p_scenario);

/**
* @brief Used to obtain verbose description about the
*        error code
*
* @param x_error --> Error code
*
* @return Char string containing description
*
*/
char *lc_getLastErrorVerbose(sint8 x_error);

/**
* @brief Clean-up scenario object prior to exiting
*
* @param p_scenarioName --> Pointer to scenario object
*
* @return None
*
*/
void lc_exitScenario(struct lc_scenario *p_scenario);

/**
* @brief Used to obtain scenario stats after processing
*
* @param p_scenarioName --> Pointer to scenario object
*
* @param p_stat --> Pointer to statistics object to be 
*					populated
*
* @return None
*
*/
void lc_getScenarioStat(struct lc_scenario *p_scenario, lc_stats *p_stat);

#endif