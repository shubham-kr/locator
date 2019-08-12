/*******************************************************************************
(c) Copyright Shubham Kumar, All rights reserved.

Email: shubhamkr@gmail.com
*******************************************************************************/

/**
* @file lc_wls.h
*
* @brief Description 	:	This defines interface for the WLS module.
*
* @author	 Shubham K <shubahmkr@gmail.com>
*/

#ifndef _LC_WLS_H
#define _LC_WLS_H

#include <math.h>
#include <lc_matInvGJE.h>

/* Number of iterations for LS to converge*/
#define MAX_ITER 10
#define ENUDIM   2
#define HMATDIM  3

/**
* @brief Generate H matrix
*
* @param p_rxLoc --> Pointer to transmitter location
*
* @param p_rxLoc --> Pointer to receive locations
*
* @param u_numTx --> Number of receive stations (upto 4)
*
* @param p_h --> H matrix to be populated
*
* @param p_prHat --> Pointer to Pr^
*
* @return None
*
*/
void lc_genH(dbl *p_rxLoc, dbl *p_txLoc, uint8 u_numTx, dbl *p_h, dbl *p_prHat);

/**
* @brief Calcualte Ht * H
*
* @param p_hMat --> Pointer to H matrix
*
* @param p_w --> Pointer to weights array
*
* @param p_hWHt --> H * W * Ht
*
* @param u_numTx --> Number of  transmitters
*
* @param dimCount --> Dimensions  of HtWH
*
* @return None
*
*/
void lc_calcHtWH(dbl *p_hMat, dbl *p_w, dbl *p_hWHt, uint16 u_NumTx, int dimCount);

/**
* @brief Perform C = A * B
*
* @param p_a --> Pointer to A
*
* @param u_nRowA --> Number of rows in A
*
* @param u_nColA --> Number of columns in A
*
* @param p_b --> Pointer to B
*
* @param u_nRowB --> Number of rows in B
*
* @param u_nColB --> Number of columns in B
*
* @param p_c --> Result matrix C
*
*
* @return None
*
*/
void lc_matrixMulAB(dbl *p_a, uint16 u_nRowA, uint16 u_nColA, dbl *p_b, uint16 u_nRowB, uint16 u_nColB, dbl *p_c);

/**
* @brief Perform C = At * B
*
* @param p_a --> Pointer to A
*
* @param u_nRowA --> Number of rows in A
*
* @param u_nColA --> Number of columns in A
*
* @param p_b --> Pointer to B
*
* @param u_nRowB --> Number of rows in B
*
* @param u_nColB --> Number of columns in B
*
* @param p_c --> Result matrix C
*
*
* @return None
*
*/
void lc_matrixMulAtB(dbl *p_a, uint8 u_nRowA, uint8 u_nColA, dbl *p_b, uint8 u_nRowB, uint8 u_nColB, dbl *p_c);

/**
* @brief Perform C = A * Bt
*
* @param p_a --> Pointer to A
*
* @param u_nRowA --> Number of rows in A
*
* @param u_nColA --> Number of columns in A
*
* @param p_b --> Pointer to B
*
* @param u_nRowB --> Number of rows in B
*
* @param u_nColB --> Number of columns in B
*
* @param p_c --> Result matrix C
*
*
* @return None
*
*/
void lc_matrixMulABt(dbl *p_a, uint16 u_nRowA, uint16 u_nColA, dbl *p_b, uint16 u_nRowB, uint16 u_nColB, dbl *p_c);

/**
* @brief Perform C = A Diag B
*
* @param p_a --> Pointer to A
*
* @param u_nRowA --> Number of rows in A
*
* @param u_nColA --> Number of columns in A
*
* @param p_b --> Pointer to B
*
* @return None
*
*/void lc_matrixMulADiagB(dbl *p_a, uint16 u_nRowA, uint16 u_nColA, dbl *p_b);

/**
* @brief Calculate position
*
* @param p_m --> Pointer to HtWH
*
* @param p_H --> H mat
*
* @param p_w --> Weight matrix
*
* @param p_diffPr --> Range differences
*
* @param u_numTx --> Number of stations
*
* @param p_pos --> Update differences
*
* @param dimCount --> Dimension count
*
* @return None
*
*/
void lc_calcPos(dbl *p_m, dbl *p_h, dbl *p_w, dbl *p_diffPr, uint16 u_numTx, dbl *p_pos, int dimCount);

/**
* @brief Least squares method
*
* @param p_txLoc --> Pointer to station locations
*
* @param p_pRange --> Pointer to ranges array
*
* @param p_w --> Pointer to weights array
*
* @param u_numTx --> Pointer to number of stations
*
* @param p_rxHat --> Initial position estimate
*
* @param p_residuals --> Range residuals
*
*
* @return None
*
*/
uint8 lc_wls(dbl *p_txLoc, dbl *p_pRange, dbl *p_w, uint8 u_numTx, dbl *p_rxHat, dbl *p_residuals);

/**
* @brief Calculate HDOP
*
* @param p_rxLoc --> Pointer to user location
*
* @param p_txLoc --> Pointer to station locations
*
* @param u_numTx --> Number of stations
*
*
* @return None
*
*/
dbl lc_findHDOP(dbl *p_rxLoc, dbl *p_txLoc, uint8 u_numTx);

#endif
