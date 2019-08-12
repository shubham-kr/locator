/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_parser.h
*
* @brief Description 	:	This defines interface for the parser module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_PARSER_H
#define _LC_PARSER_H

#include <lc_scenario.h>

#define LC_MAXLINE			(1024)

/* Forward declaration */
struct lc_scenario;

/**
* @brief Parse input scenario file and populate TOA
*
* @param p_scenario --> Pointer to scenario object
*
* @return lc_errorCodes
*
*/
uint8 lc_fillInputToa(struct lc_scenario *p_scenario);

#endif