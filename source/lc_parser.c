/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_parser.c
*
* @brief Description 	:	This defines implementation for the parser module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lc_defs.h>
#include <lc_scenario.h>
#include <lc_api.h>
#include <lc_parser.h>

uint8 lc_fillInputToa(struct lc_scenario *p_scenario)
{
	sint8 z_Buffer[LC_MAXLINE];
	char *p_token;
	uint8 u_numToas;

	u_numToas = 0;

	if (fgets(z_Buffer, LC_MAXLINE, p_scenario->h_File) != NULL)
	{
		p_token = strtok(z_Buffer, ",");

		while (u_numToas != LC_MAX_STATIONS)
		{
			if (p_token == NULL)
			{
				/* Wrong  formatted line, no CSV values*/
				p_scenario->x_lastError = LC_WRONG_TOALINE_FORMAT;
				return LC_ERROR;
			}

			p_scenario->z_signalInfo[u_numToas].w_status_flag &= (~LC_BIT_TOAVALID);

			/* If the TOA value is absent, it'll be marked with '-'*/
			if (*p_token == '-')
				p_scenario->z_signalInfo[u_numToas].d_toa = -1;
			else
			{
				dbl d_tokenVal;

				d_tokenVal = atof(p_token);
				if (d_tokenVal == 0)
				{
					/* Conversion failed, return error */
					p_scenario->x_lastError = LC_WRONG_TOALINE_FORMAT;
					return LC_ERROR;
				}
				p_scenario->z_signalInfo[u_numToas].d_toa = atof(p_token);
				p_scenario->z_signalInfo[u_numToas].w_status_flag |= LC_BIT_TOAVALID;
			}
				
			u_numToas++;
			p_token = strtok(NULL, ",");
		}
	}
	else
	{
		return LC_EOF;
	}

	if (p_token != NULL)
	{
		/* Extra characters present after 4 valid TOA values */
		p_scenario->x_lastError = LC_WRONG_TOALINE_FORMAT;
		return LC_ERROR;
	}

	return LC_OK;
}