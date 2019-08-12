/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved. 

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_matInvGJE.c
*
* @brief Description 	:	This defines implementation for matrix inversion.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#include <math.h>
#include <lc_MatInvGJE.h>


uint8 lc_matInvGJE(dbl *p_mat, uint8 u_matrixSize, dbl *d_det )
{
	uint8  k,j;
	uint8  u_col;
	dbl    d_trace;
	dbl    d_pivot;
	dbl    d_tempDet;
	dbl    d_tempSwap;
	uint8  u_columnSwapInfo[MAX_MATRIX_SIZE],*p_columnSwapInfo = &u_columnSwapInfo[0];	/* This array is used for recording all swapping information. */
    dbl    *p_matTmp;


	d_tempDet = 1.0F;

	for (u_col = 0; u_col < u_matrixSize; u_col++)
	{
		*p_columnSwapInfo++ = u_col;
	}

	for (u_col=0; u_col < u_matrixSize; u_col++)
	{
		d_pivot = 0.0F;
		j = u_col;

		/* Pivot is the largest absolute value in a row. */
        p_matTmp = p_mat + u_col*u_matrixSize + u_col ;
		for (k = u_col; k < u_matrixSize; k++)
		{
			if (fabs(d_pivot) < fabs(*p_matTmp))
			{
				j = k;
				d_pivot = *p_matTmp ;
			}
			p_matTmp++ ;
		}

		/* Swap the column to make the Pivot as the first non zero element in the row  */
		if (u_col!=j)
		{
			k = u_columnSwapInfo[j];
			u_columnSwapInfo[j] = u_columnSwapInfo[u_col];
			u_columnSwapInfo[u_col] = k;

			for(k = 0; k < u_matrixSize; k++)
			{
				d_tempSwap = p_mat[k*u_matrixSize +u_col];
				p_mat[k*u_matrixSize +u_col] = p_mat[k*u_matrixSize +j];
				p_mat[k*u_matrixSize +j] = d_tempSwap;
			}
		}

		/* Divide the row by the d_pivot, making the leading element
		 * 1.0 and multiplying the determinant by the d_pivot.
		*/

		p_mat[u_col*u_matrixSize +u_col] = 1.0F;

		d_tempDet *= d_pivot;   	/* Determinant of the matrix. */

		if (fabs(d_tempDet) < 1.0E-10)
		{
			*d_det = d_tempDet;
			return (FAILURE);		/* Pivot = 0 therefore singular matrix. */
		}


		for (j = 0; j < u_matrixSize; j++)
		{
			p_mat[u_col *u_matrixSize +j] /= d_pivot;
		}

		/* Gauss-Jordan elimination.  Subtract the appropriate multiple
		 * of the current row from all subsequent rows to get the matrix
		 * into row echelon form.
		*/

		for (j=0; j < u_matrixSize; j++)
		{
			if (u_col==j) continue;

			d_pivot = p_mat[j*u_matrixSize +u_col];

			if (d_pivot==0.0F) continue;

			p_mat[j*u_matrixSize +u_col] = 0.0F;

			for (k = 0; k < u_matrixSize; k++)
			{
				p_mat[j*u_matrixSize +k] -= (d_pivot*p_mat[u_col*u_matrixSize +k]);
			}
		}
	}

	/* Swap the columns back into their correct places. */
	for (u_col=0; u_col < u_matrixSize; u_col++)
	{
		if (u_columnSwapInfo[u_col] == u_col) continue;

		/* Find out where the column wound up after column swapping. */
		for (j = u_col+1; j < u_matrixSize; j++)
		{
			if (u_columnSwapInfo[j] == u_col)
				break;
		}

		u_columnSwapInfo[j] = u_columnSwapInfo[u_col];

		for (k = 0; k < u_matrixSize; k++)
		{
			d_pivot = p_mat[u_col*u_matrixSize +k];
			p_mat[u_col*u_matrixSize +k] = p_mat[j*u_matrixSize +k];
			p_mat[j*u_matrixSize +k] = d_pivot;
		}

		u_columnSwapInfo[u_col] = u_col;
	}

	/* Test for the inverse. */
	*d_det = d_tempDet;

	d_trace=0.0F ;
	for (u_col=0; u_col<3; u_col++)
	{
		d_trace += p_mat[u_col*u_matrixSize +u_col];
	}

	/* A nearly signular matrix can produce a physically impossible PDOP. */
	if (d_trace < 0.0001F) return (FAILURE);

	return (SUCCESS);
}
