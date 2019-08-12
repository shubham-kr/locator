/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_reports.c
*
* @brief Description 	:	This defines functions for reporting module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<lc_reports.h>
#include<lc_scenario.h>
#include <lc_signalMeas.h>
#include <lc_trace.h>

void lc_frct2String(char *str, sint32 val, sint32 nDigitsPass) {

	sint32 ten = 1;
	sint32 t;
	sint32 nDigits = nDigitsPass;

	// extracting each digit to convert
	// each digit from number to string (by adding with '0')
	while (nDigits--) {
		t = val % (ten * 10); str[nDigits] = (char)((t / ten) + '0'); val -= t;
		ten *= 10;
	}
	str[nDigitsPass] = 0;
}

void lc_int2String(char * str, sint32 val, sint32 nDigitsPass) {

	sint32 t, cntr1;
	sint32 nDigits = nDigitsPass;
	uint32 val1;
	sint32 maxValue = (sint32)pow((dbl)10, (dbl)nDigits) - 1;
	sint32 minValue = -maxValue;
	//if (abs((sint32)val) >= (sint32)maxValue )
	{
		if (val < minValue)
			val = minValue;
		else if (val > maxValue)
			val = maxValue;
	}
	cntr1 = nDigits;
	// extracting sign value
	{
		if (val < 0) {
			str[0] = '-';
			val1 = -val;
			cntr1--;
		}
		else
		{
			str[0] = ' ';
			val1 = val;
		}
	}

	// extracting each digit to convert
	// each digit from number to string (by adding with '0')
	while (cntr1--) {
		t = val1 % 10;
		str[--nDigits] = (char)(t + '0');
		val1 = val1 / 10;
	}
	str[nDigitsPass] = 0;
}

void lc_flt2String(char * str, dbl val, sint32 intbits, sint32 frctBits)
{
	sint32 base = 1;
	sint32 i;
	for (i = 0; i < frctBits; i++) base *= 10;

	dbl maxValue = pow((dbl)10, (dbl)intbits) - pow((dbl)10, (dbl)-frctBits);
	dbl minValue = -maxValue;
	//if (abs((sint32)val) >= (sint32)maxValue )
	{
		if (val < minValue)
			val = minValue;
		else if (val > maxValue)
			val = maxValue;
	}

	if (val < 0)
	{
		strcat(str, "-");
		val = -1 * val;
		intbits--;
	}


	lc_int2String(&str[strlen(str)], (sint32)val, intbits);

	strcat(str, ".");
	lc_frct2String(&str[strlen(str)], abs((sint32)((val - (sint32)val)*base)), frctBits);
}

void lc_reportPrange(struct lc_scenario *p_scenario)
{
	uint8 u_i;
	sint8 buf[512];
	signalMeas *p_signalMeas;
	sint32 w_len = 0;
	uint8 *ptrBuf;

	ptrBuf = &buf[0];
	p_signalMeas = p_scenario->z_signalInfo;

	w_len = sprintf(ptrBuf, "PRNG,"); ptrBuf += w_len;
	w_len = 3, lc_int2String(ptrBuf, p_scenario->q_ints, w_len); ptrBuf += w_len;
	

	for (u_i = 0; u_i < LC_MAX_STATIONS; u_i++)
	{
		w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

		w_len = 1, lc_int2String(ptrBuf, u_i, w_len); ptrBuf += w_len;
		w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

		w_len = 9, lc_flt2String(ptrBuf, p_signalMeas[u_i].d_pRange, 5, 3); ptrBuf += w_len;
		w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

		w_len = 9, lc_flt2String(ptrBuf, p_signalMeas[u_i].z_Loc[0], 5, 3); ptrBuf += w_len;
		w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

		w_len = 9, lc_flt2String(ptrBuf, p_signalMeas[u_i].z_Loc[1], 5, 3);  ptrBuf += w_len;
		w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;
		
		w_len = 6, sprintf(ptrBuf, "0x%04x", p_signalMeas[u_i].w_status_flag); ptrBuf += w_len;
	}

	lc_trace(p_scenario, "%s", buf);
}

void lc_reportWLSFix(struct lc_scenario * p_scenario, dbl *d_RxHat)
{
	sint8 buf[512];
	signalMeas *p_signalMeas;
	sint32 w_len = 0;
	uint8 *ptrBuf;

	ptrBuf = &buf[0];
	p_signalMeas = p_scenario->z_signalInfo;

	w_len = sprintf(ptrBuf, "WLS,"); ptrBuf += w_len;
	w_len = 3, lc_int2String(ptrBuf, p_scenario->q_ints, w_len); ptrBuf += w_len;

	w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

	w_len = 1, lc_int2String(ptrBuf, p_scenario->z_rxPosition.u_numStationsUsedInFix, w_len); ptrBuf += w_len;
	w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

	w_len = 9, lc_flt2String(ptrBuf, d_RxHat[0], 5, 3); ptrBuf += w_len;
	w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

	w_len = 9, lc_flt2String(ptrBuf, d_RxHat[1], 5, 3); ptrBuf += w_len;

	lc_trace(p_scenario, "%s", buf);
}

void lc_reportFilterFix(struct lc_scenario * p_scenario)
{
	sint8 buf[512];
	signalMeas *p_signalMeas;
	sint32 w_len = 0;
	uint8 *ptrBuf;

	ptrBuf = &buf[0];
	p_signalMeas = p_scenario->z_signalInfo;

	w_len = sprintf(ptrBuf, "FFIX,"); ptrBuf += w_len;
	w_len = 3, lc_int2String(ptrBuf, p_scenario->q_ints, w_len); ptrBuf += w_len;

	w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

	w_len = 1, lc_int2String(ptrBuf, p_scenario->z_rxPosition.u_numStationsUsedInFix, w_len); ptrBuf += w_len;
	w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

	w_len = 9, lc_flt2String(ptrBuf, p_scenario->z_rxPosition.d_xyFiltered[0], 5, 3); ptrBuf += w_len;
	w_len = 1, sprintf(ptrBuf, ","); ptrBuf += w_len;

	w_len = 9, lc_flt2String(ptrBuf, p_scenario->z_rxPosition.d_xyFiltered[1], 5, 3); ptrBuf += w_len;

	lc_trace(p_scenario, "%s", buf);
}