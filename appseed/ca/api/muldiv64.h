/*
 *   Header file:      muldiv64.h
 *   Author:            Richard van der Wal
 *   Contact:         R.vdWal@xs4all.nl
 *
 *   Description:
 *      Header file with prototype for 64 bit scaling functions
 *
 *   $Log: $
 *
 */

/******************************************************************************/
#pragma once
#ifndef __FULL_MULDIV64_
#define __FULL_MULDIV64_


/*
 * muldiv64
 * Multiplies an operant by a multiplier and divides the result by a divider
 * Used for scaling 64 bit integer values
 *     Xscaled = Xstart * Multiplier / Divider
 * Uses 128 bit intermediate result
 */
CLASS_DECL_ca int64_t _stdcall muldiv64(int64_t operant, int64_t multiplier, int64_t divider);


/*
 * mulshr64
 * Multiplies an operant by a multiplier and right shifts the result rshift times
 * Used for scaling 64 bit integer values
 *     Xscaled = (Xstart * Multiplier) SHR rshift
 * Uses 128 bit intermediate result
 */
CLASS_DECL_ca int64_t _stdcall mulshr64(int64_t operant, int64_t multiplier, unsigned char rshift);


CLASS_DECL_ca void mul64(uint64_t v1, uint64_t v2, uint64_t & hi, uint64_t & lo);

#endif //__FULL_MULDIV64_