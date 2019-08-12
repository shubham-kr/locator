/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_reports.h
*
* @brief Description 	:	This defines interface  for the reporting module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_REPORT_H
#define _LC_REPORT_H

#include "lc_defs.h"

/* Forward  declaration */
struct lc_scenario;

/**
* @brief Report pseduorange message
*
* @param p_scenario --> Pointer to scenario object
*
* @return None
*
*/
void lc_reportPrange(struct lc_scenario * p_scenario);

/**
* @brief Report position message
*
* @param p_scenario --> Pointer to scenario object
*
* @return None
*
*/
void lc_reportWLSFix(struct lc_scenario * p_scenario, dbl *d_RxHat);

/**
* @brief Report Filtered position
*
* @param p_scenario --> Pointer to scenario object
*
* @return None
*
*/
void lc_reportFilterFix(struct lc_scenario * p_scenario);

#endif