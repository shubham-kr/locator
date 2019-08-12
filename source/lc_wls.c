/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_wls.c
*
* @brief Description 	:	This defines implementation for the WLS module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <stdio.h>
#include <lc_wls.h>

void lc_genH(dbl *p_rxLoc, dbl *p_txLoc, uint8 u_numTx, dbl *p_h, dbl *p_prHat)
{
	uint16 w_i;
	uint8  u_txCnt;
	dbl d_dVec[ENUDIM];


	for (u_txCnt = 0; u_txCnt< u_numTx; u_txCnt++)
	{
		for (w_i = 0; w_i < ENUDIM; w_i++)
		{
			d_dVec[w_i] = p_rxLoc[w_i] - p_txLoc[u_txCnt * ENUDIM + w_i];
		}

		p_prHat[u_txCnt] = sqrt(d_dVec[0] * d_dVec[0] + d_dVec[1] * d_dVec[1]);

		p_h[u_txCnt*HMATDIM + 0] = d_dVec[0] / p_prHat[u_txCnt];
		p_h[u_txCnt*HMATDIM + 1] = d_dVec[1] / p_prHat[u_txCnt];
		p_h[u_txCnt*HMATDIM + 2] = 1;
	}
}



void lc_calcHtWH(dbl *p_hmat, dbl *p_w, dbl *p_hWHt, uint16 u_numTx, int dimCount)
{
	uint16 r, c;
	uint16  u_txCnt;
	dbl d_sum;
	dbl *p_hT, *p_h, *p_wTmp;

	for (r = 0; r < dimCount; r++)
	{
		for (c = 0; c < dimCount; c++)
		{
			d_sum = 0.0;
			p_hT = p_hmat + r;
			p_h = p_hmat + c;
			p_wTmp = p_w;
			for (u_txCnt = 0; u_txCnt< u_numTx; u_txCnt++)
			{
				d_sum += (*p_hT) * (*p_wTmp)  * (*p_h);
				p_hT += dimCount;
				p_h += dimCount;
				p_wTmp++;
			}
			*p_hWHt = d_sum;
			p_hWHt++;
		}
	}
}

void lc_matrixMulAB(dbl *p_a, uint16 u_nRowA, uint16 u_nColA, dbl *p_b, uint16 u_nRowB, uint16 u_nColB, dbl *p_c)
{
	uint16  l, m, n;//j=0;
	dbl *p_aTmp, *p_bTmp, *p_cTmp;

	p_cTmp = p_c;
	for (l = 0; l < u_nRowA; l++)
	{
		for (m = 0; m < u_nColB; m++)
		{
			*p_cTmp = 0.0;
			p_aTmp = p_a + l*u_nColA;
			p_bTmp = p_b + m;
			for (n = 0; n < u_nColA; n++)
			{
				//				p_c[l*u_nColB+m] += p_a[l*u_nColA+n] * p_b[n*u_nColB+m] ;
				*p_cTmp += (*p_aTmp) * (*p_bTmp);
				p_aTmp++;
				p_bTmp += u_nColB;
			}
			p_cTmp++;
		}
	}
}

void lc_matrixMulAtB(dbl *p_a, uint8 u_nRowA, uint8 u_nColA, dbl *p_b, uint8 u_nRowB, uint8 u_nColB, dbl *p_c)
{
	uint8  l, m, n;
	dbl *p_aTmp, *p_bTmp, *p_cTmp;

	p_cTmp = p_c;
	for (l = 0; l < u_nColA; l++)
	{
		for (m = 0; m < u_nColB; m++)
		{
			*p_cTmp = 0.0;
			p_aTmp = p_a + l;
			p_bTmp = p_b + m;
			for (n = 0; n < u_nRowA; n++)
			{
				//				p_c[l][m] += p_a[n][l] * p_b[n][m] ;
				*p_cTmp += (*p_aTmp) * (*p_bTmp);
				p_aTmp += u_nColA;
				p_bTmp += u_nColB;
			}
			p_cTmp++;
		}
	}
}

void lc_matrixMulABt(dbl *p_a, uint16 u_nRowA, uint16 u_nColA, dbl *p_b, uint16 u_nRowB, uint16 u_nColB, dbl *p_c)
{
	uint16  l, m, n;
	dbl *p_aTmp, *p_bTmp, *p_cTmp;

	p_cTmp = p_c;
	for (l = 0; l < u_nRowA; l++)
	{
		for (m = 0; m < u_nRowB; m++)
		{
			*p_cTmp = 0.0;
			p_aTmp = p_a + l*u_nColA;
			p_bTmp = p_b + m*u_nColB;
			for (n = 0; n < u_nColA; n++)
			{
				//				p_c[l][m] += p_a[l][n] * p_b[m][n] ;
				*p_cTmp += (*p_aTmp) * (*p_bTmp);
				p_aTmp++;
				p_bTmp++;
			}
			p_cTmp++;
		}
	}
}

void lc_matrixMulADiagB(dbl *p_a, uint16 u_nRowA, uint16 u_nColA, dbl *p_b)
{
	uint16  l, m;
	dbl *p_aTmp, *p_bTmp;

	p_aTmp = p_a;
	for (l = 0; l < u_nRowA; l++)
	{
		p_bTmp = p_b;
		for (m = 0; m < u_nColA; m++)
		{
			*p_aTmp = (*p_aTmp) * (*p_bTmp);
			p_aTmp++;
			p_bTmp++;
		}
	}
}

void lc_calcPos(dbl *p_M, dbl *p_h, dbl *p_w, dbl *p_DiffPr, uint16 u_numTx, dbl *p_Pos, int dimCount)
{
	dbl    d_A[HMATDIM * LC_MAX_STATIONS], *p_a = &d_A[0];

	lc_matrixMulABt(p_M, dimCount, dimCount, p_h, u_numTx, dimCount, p_a);
	lc_matrixMulADiagB(p_a, dimCount, u_numTx, p_w);
	lc_matrixMulAB(p_a, dimCount, u_numTx, p_DiffPr, u_numTx, 1, p_Pos);
}

uint8 lc_wls(dbl *p_txLoc, dbl *p_PRange, dbl *p_w,	uint8 u_numTx, dbl *p_RxHat, dbl *p_residuals)
{
	uint16 u_iter, u_txCnt, u_dim;
	dbl d_prHat[LC_MAX_STATIONS];
	dbl d_diffPr[LC_MAX_STATIONS];
	dbl d_h[HMATDIM*LC_MAX_STATIONS];
	dbl d_htWH[HMATDIM*HMATDIM];
	dbl d_det;
	dbl d_diffPos[HMATDIM];
	int dimCount = ENUDIM + 1;
	uint8 u_status;
	uint8 k;

	for (k = 0; k < u_numTx; k++) {
		p_PRange[k] += p_RxHat[2];
	}

	for (u_iter = 0; u_iter < MAX_ITER; u_iter++)
	{
		lc_genH(p_RxHat, p_txLoc, u_numTx, d_h, d_prHat);

		for (u_txCnt = 0; u_txCnt< u_numTx; u_txCnt++)
		{
			d_diffPr[u_txCnt] = p_PRange[u_txCnt] - d_prHat[u_txCnt] - p_RxHat[2];
		}

		lc_calcHtWH(d_h, p_w, d_htWH, u_numTx, dimCount);
		u_status = lc_matInvGJE(d_htWH, dimCount, &d_det);

		if (u_status)
		{
			lc_calcPos(d_htWH, d_h, p_w, d_diffPr, u_numTx, d_diffPos, dimCount);

			for (u_dim = 0; u_dim < dimCount; u_dim++)
			{
				p_RxHat[u_dim] = p_RxHat[u_dim] + d_diffPos[u_dim];
			}
		}
		else
		{			
			return u_status;
		}
	}

	for (u_iter = 0; u_iter < u_numTx; u_iter++)
		p_residuals[u_iter] = d_diffPr[u_iter];

	return u_status;
}

dbl lc_findHDOP(dbl *p_rxLoc, dbl *p_txLoc, uint8 u_numTx)
{
	dbl d_prHat[LC_MAX_STATIONS];
	dbl d_h[HMATDIM*LC_MAX_STATIONS];
	dbl d_htH[HMATDIM*HMATDIM];
	dbl d_det;

	lc_genH(p_rxLoc, p_txLoc, u_numTx, d_h, d_prHat);
	lc_matrixMulAtB(d_h, u_numTx, HMATDIM, d_h, u_numTx, HMATDIM, (dbl *)&d_htH[0]);
	lc_matInvGJE(d_htH, HMATDIM, &d_det);

	return sqrt(d_htH[0] + d_htH[5]);
}

