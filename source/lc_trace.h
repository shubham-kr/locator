/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_trace.h
*
* @brief Description 	:	This defines interface for the trace module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_TRACE_H
#define _LC_TRACE_H

#define LC_TRACE_MAXLINE	(1024)

/* Forward declaration */
struct lc_scenario;

/**
* @brief Trace print
*
* @param p_scenario --> Pointer to scenario object
*
* @param format_string --> Format string for the VAR 
*						   argument list
*
* @return None
*
*/
void lc_trace(struct lc_scenario *p_scenario, char *formatString, ...);

#endif