/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_signalMeas.h
*
* @brief Description 	:	This defines interface for  signal Measurment module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_SIGNALMEAS_H
#define _LC_SIGNALMEAS_H

#include "lc_defs.h"

/* Bit definitions for the status word */
#define	LC_BIT_TOAVALID			(1 << 0)
#define	LC_BIT_PRANGEVALID		(1 << 1)
#define	LC_BIT_POSVALID			(1 << 2)
#define	LC_BIT_PRANGEREMOVED	(1 << 3)

/* Forward declrations */
struct lc_scenario;

typedef struct {
	dbl		d_toa;			/* TOA*/
	dbl		d_pRange;		/* PRANGE in m*/
	dbl		z_Loc[2];		/* (X,Y)*/
	uint16	w_status_flag;
} signalMeas;

/**
* @brief Generate pseudo-range from TOA
*
* @param p_scenario --> Pointer to scenario object
*
* @return None
*
*/
void lc_genPseudoRange(struct lc_scenario *p_scenario);

#endif

