/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_filters.h
*
* @brief Description 	:	This defines interface for the position filter.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/
#ifndef _LC_FILTER_H_
#define _LC_FILTER_H_

/* Forward declaration */
struct lc_scenario;

/**
* @brief Position filtering
*
* @param p_scenarioName --> Pointer to scenario object
*
* @param d_residuals --> Ranging residuals after LS 
*						 iterations
*
* @return None
*
*/
void  lc_fixFilterUpdate(struct lc_scenario *p_scenario, dbl *d_residuals);

#endif