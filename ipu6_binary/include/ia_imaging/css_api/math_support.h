/*
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2010 - 2017 Intel Corporation.
 * All Rights Reserved.
 *
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Intel Corporation
 * or licensors. Title to the Material remains with Intel
 * Corporation or its licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material may
 * be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No License under any patent, copyright, trade secret or other intellectual
 * property right is granted to or conferred upon you by disclosure or
 * delivery of the Materials, either expressly, by implication, inducement,
 * estoppel or otherwise. Any license under such intellectual property rights
 * must be express and approved by Intel in writing.
 */


#ifndef __MATH_SUPPORT_H
#define __MATH_SUPPORT_H

#include "storage_class.h" /* for STORAGE_CLASS_INLINE */
#if defined(__KERNEL__)
#include <linux/kernel.h> /* Override the definition of max/min from linux kernel*/
#endif /*__KERNEL__*/

#if defined(_MSC_VER)
#include <stdlib.h> /* Override the definition of max/min from stdlib.h*/
#endif /* _MSC_VER */

/* in case we have min/max/MIN/MAX macro's undefine them */
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#ifdef MIN /* also defined in include/hrt/numeric.h from SDK */
#undef MIN
#endif
#ifdef MAX
#undef MAX
#endif
#ifdef ABS
#undef ABS
#endif

#define IS_ODD(a)            ((a) & 0x1)
#define IS_EVEN(a)           (!IS_ODD(a))

/* force a value to a lower even value */
#define EVEN_FLOOR(x)        ((x) & ~1)

/* If the number is odd, find the next even number */
#define EVEN_CEIL(x)         ((IS_ODD(x)) ? ((x) + 1) : (x))

/* A => B */
#define IMPLIES(a, b)        (!(a) || (b))

#define ABS(a)               ((a) >= 0 ? (a) : -(a))

/* for preprocessor and array sizing use MIN and MAX
   otherwise use min and max */
#define MAX(a, b)            (((a) > (b)) ? (a) : (b))
#define MIN(a, b)            (((a) < (b)) ? (a) : (b))
#define ROUND_DIV(a, b)      ((b) ? ((a) + ((b) >> 1)) / (b) : 0)
#define CEIL_DIV(a, b)       ((b) ? ((a) + (b) - 1) / (b) : 0)
#define CEIL_MUL(a, b)       (CEIL_DIV(a, b) * (b))
#define CEIL_MUL2(a, b)      (((a) + (b) - 1) & ~((b) - 1))
#define CEIL_SHIFT(a, b)     (((a) + (1 << (b)) - 1)>>(b))
#define CEIL_SHIFT_MUL(a, b) (CEIL_SHIFT(a, b) << (b))
#define ROUND_HALF_DOWN_DIV(a, b)	((b) ? ((a) + (b / 2) - 1) / (b) : 0)
#define ROUND_HALF_DOWN_MUL(a, b)	(ROUND_HALF_DOWN_DIV(a, b) * (b))


/*To Find next power of 2 number from x */
#define bit2(x)            ((x)      | ((x) >> 1))
#define bit4(x)            (bit2(x)  | (bit2(x) >> 2))
#define bit8(x)            (bit4(x)  | (bit4(x) >> 4))
#define bit16(x)           (bit8(x)  | (bit8(x) >> 8))
#define bit32(x)           (bit16(x) | (bit16(x) >> 16))
#define NEXT_POWER_OF_2(x) (bit32(x-1) + 1)


/* min and max should not be macros as they will evaluate their arguments twice.
   if you really need a macro (e.g. for CPP or for initializing an array)
   use MIN() and MAX(), otherwise use min() and max().


*/

#if !defined(PIPE_GENERATION)

#ifndef INLINE_MATH_SUPPORT_UTILS
/*
This macro versions are added back as we are mixing types in usage of inline.
This causes corner cases of calculations to be incorrect due to conversions
between signed and unsigned variables or overflows.
Before the addition of the inline functions, max, min and ceil_div were macros
and therefore adding them back.

Leaving out the other math utility functions as they are newly added
*/

#define max(a, b)		(MAX(a, b))
#define min(a, b)		(MIN(a, b))
#define ceil_div(a, b)		(CEIL_DIV(a, b))

#else /* !defined(INLINE_MATH_SUPPORT_UTILS) */

STORAGE_CLASS_INLINE int max(int a, int b)
{
	return MAX(a, b);
}

STORAGE_CLASS_INLINE int min(int a, int b)
{
	return MIN(a, b);
}

STORAGE_CLASS_INLINE unsigned int ceil_div(unsigned int a, unsigned int b)
{
	return CEIL_DIV(a, b);
}
#endif /* !defined(INLINE_MATH_SUPPORT_UTILS) */

STORAGE_CLASS_INLINE unsigned int umax(unsigned int a, unsigned int b)
{
	return MAX(a, b);
}

STORAGE_CLASS_INLINE unsigned int umin(unsigned int a, unsigned int b)
{
	return MIN(a, b);
}


STORAGE_CLASS_INLINE unsigned int ceil_mul(unsigned int a, unsigned int b)
{
	return CEIL_MUL(a, b);
}

STORAGE_CLASS_INLINE unsigned int ceil_mul2(unsigned int a, unsigned int b)
{
	return CEIL_MUL2(a, b);
}

STORAGE_CLASS_INLINE unsigned int ceil_shift(unsigned int a, unsigned int b)
{
	return CEIL_SHIFT(a, b);
}

STORAGE_CLASS_INLINE unsigned int ceil_shift_mul(unsigned int a, unsigned int b)
{
	return CEIL_SHIFT_MUL(a, b);
}

STORAGE_CLASS_INLINE unsigned int round_half_down_div(unsigned int a, unsigned int b)
{
	return ROUND_HALF_DOWN_DIV(a, b);
}

STORAGE_CLASS_INLINE unsigned int round_half_down_mul(unsigned int a, unsigned int b)
{
	return ROUND_HALF_DOWN_MUL(a, b);
}

/** @brief Next Power of Two
 *
 *  @param[in] unsigned number
 *
 *  @return next power of two
 *
 * This function rounds input to the nearest power of 2 (2^x)
 * towards infinity
 *
 * Input Range: 0 .. 2^(8*sizeof(int)-1)
 *
 * IF input is a power of 2
 *     out = in
 * OTHERWISE
 *     out = 2^(ceil(log2(in))
 *
 */

STORAGE_CLASS_INLINE unsigned int ceil_pow2(unsigned int a)
{
	if (a == 0) {
		return 1;
	}
	/* IF input is already a power of two*/
	else if ((!((a)&((a)-1)))) {
		return a;
	}
	else {
		unsigned int v = a;
		v |= v>>1;
		v |= v>>2;
		v |= v>>4;
		v |= v>>8;
		v |= v>>16;
		return (v+1);
	}
}

#endif /* !defined(PIPE_GENERATION) */

#if !defined(__ISP) && !defined(__SP)
/*
 * For SP and ISP, SDK provides the definition of OP_std_modadd.
 * We need it only for host
 */
#define OP_std_modadd(base, offset, size) ((base+offset)%(size))
#endif /* !defined(__ISP) && !defined(__SP) */

#if !defined(__KERNEL__)
#define clamp(a, min_val, max_val) MIN(MAX((a), (min_val)), (max_val))
#endif /* !defined(__KERNEL__) */

#endif /* __MATH_SUPPORT_H */