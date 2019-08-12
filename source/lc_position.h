/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_position.h
*
* @brief Description 	:	This defines interface for position module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_POS_H
#define _LC_POS_H

#include <lc_defs.h>

#define LC_PRANGE_MAXJUMP_M	(1000)
struct lc_scenario;

typedef struct {
	dbl		d_xyt[3];
	dbl		d_xyFiltered[2];
	uint8	u_numStationsUsedInFix;
	dbl		d_residuals[4];
	uint16	w_status_flag;
} lc_rxPosition;

/**
* @brief Calculate user postion
*
* @param p_scenario --> Pointer to scenario object
*
* @return None
*
*/
void lc_calcPosition(struct lc_scenario *p_scenario);

#endif

