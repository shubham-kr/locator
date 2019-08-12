/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_matInvGJE.h
*
* @brief Description 	:	This defines GJE function for matrix inversion.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef MATINVGJE_H
#define MATINVGJE_H

#include <lc_defs.h>

#define MAX_MATRIX_SIZE 4
#define FAILURE 0
#define SUCCESS 1

/**
* @brief Matrix inversion using GJE
*
* @param p_Mat --> Pointer to HtH
*
* @param u_MatrixSize --> Dimensrions of HMAT
*						 iterations
*
* @param d_Det --> Determinant from the inversion
*
* @return None
*
*/
uint8 lc_matInvGJE(dbl *p_Mat,uint8 u_matrixSize, dbl *d_det );


#endif
