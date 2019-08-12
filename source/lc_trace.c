/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file nn_rm_defs.h
*
* @brief Description 	:	This defines data structure for the ranging module.
*
* @author	 Shubham K <skumar@nextnav.com> , NextNav
*/

/**
* @file lc_trace.c
*
* @brief Description 	:	This defines implementation for the trace module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <stdio.h>
#include <stdarg.h>
#include <lc_trace.h>
#include <lc_scenario.h>

/*******************************************************************************
Function Name	:	lc_trace
Description 	:	This function decodes PDU.
Inputs			:
Outputs		:
ReturnCode     :
*******************************************************************************/
void lc_trace(struct lc_scenario *p_scenario, char *formatString, ...)
{
	char s_PrintStr[LC_TRACE_MAXLINE + 1];
	va_list list;

	/* Extract var args */
	va_start(list, formatString);

	vsprintf(s_PrintStr, formatString, list);

	/* At the moment, we will print the traces to a file */
	fprintf(p_scenario->h_outputFile, "%s\n", s_PrintStr);
}
