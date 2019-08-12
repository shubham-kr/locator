/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_defs.h
*
* @brief Description 	:	Defines data types and global definitions 
*							for the locator module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_DEFS_H_
#define _LC_DEFS_H_

/* Type definitions for LC module */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;
typedef signed long long sint64;
typedef unsigned long long uint64;
typedef double dbl;
typedef float flt;

/* Common definitions are placed here */
#define LC_MAX_STATIONS				(4)
#define VLIGHT (299792457.888)  /** Speed of light in meter/second */

#endif
