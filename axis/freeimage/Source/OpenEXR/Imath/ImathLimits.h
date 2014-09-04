///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2002, Industrial Light & Magic, a division of Lucas
// Digital Ltd. LLC
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Industrial Light & Magic nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////



#ifndef INCLUDED_IMATHLIMITS_H
#define INCLUDED_IMATHLIMITS_H

//----------------------------------------------------------------
//
//	Limitations of the basic C++ numerical data types
//
//----------------------------------------------------------------

#include <float.h>
#include <limits.h>

//------------------------------------------
// In Windows, MIN and MAX are macros.  Yay.
//------------------------------------------

/*#if defined _WIN32 || defined _WIN64
    #ifdef MIN
        #undef MIN
    #endif
    #ifdef MAX
        #undef MAX
    #endif
#endif*/

namespace Imath {


//-----------------------------------------------------------------
//
// Template class limits<T> returns information about the limits
// of numerical data type T:
//
//	minimum()		largest possible negative value of type T
//
//	maximum()		largest possible positive value of type T
//
//	smallest()	smallest possible positive value of type T
//			(for float and double: smallest normalized
//			positive value)
//
//	epsilon()	smallest possible e of type T, for which
//			1 + e != 1
//
//	isIntegral()	returns true if T is an integral type
//
//	isSigned()	returns true if T is signed
//
// Class limits<T> is useful to implement template classes or
// functions which depend on the limits of a numerical type
// which is not known in advance; for example:
//
//	template < class T > MAX (T x[], int n)
//	{
//	    T m = limits<T>::minimum();
//
//	    for (int i = 0; i < n; i++)
//		if (m < x[i])
//		    m = x[i];
//
//	    return m;
//	}
//
// Class limits<T> has been implemented for the following types:
//
//	char, signed char, unsigned char
//	short, unsigned short
//	int, unsigned int
//	long, unsigned long
//	float
//	double
//	long double
//
// Class limits<T> has only static member functions, all of which
// are implemented as inlines.  No objects of type limits<T> are
// ever created.
//
//-----------------------------------------------------------------


template < class T > struct limits
{
    static T	minimum();
    static T	maximum();
    static T	smallest();
    static T	epsilon();
    static bool	isIntegral();
    static bool	isSigned();
};


//---------------
// Implementation
//---------------

template <>
struct limits <char>
{
    static char			minimum()		{return CHAR_MIN;}
    static char			maximum()		{return CHAR_MAX;}
    static char			smallest()	{return 1;}
    static char			epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return (char) ~0 < 0;}
};

template <>
struct limits <signed char>
{
    static signed char		minimum()		{return SCHAR_MIN;}
    static signed char		maximum()		{return SCHAR_MAX;}
    static signed char		smallest()	{return 1;}
    static signed char		epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return true;}
};

template <>
struct limits <unsigned char>
{
    static unsigned char	minimum()		{return 0;}
    static unsigned char	maximum()		{return UCHAR_MAX;}
    static unsigned char	smallest()	{return 1;}
    static unsigned char	epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return false;}
};

template <>
struct limits <short>
{
    static short		minimum()		{return SHRT_MIN;}
    static short		maximum()		{return SHRT_MAX;}
    static short		smallest()	{return 1;}
    static short		epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return true;}
};

template <>
struct limits <unsigned short>
{
    static unsigned short	minimum()		{return 0;}
    static unsigned short	maximum()		{return USHRT_MAX;}
    static unsigned short	smallest()	{return 1;}
    static unsigned short	epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return false;}
};

template <>
struct limits <int>
{
    static int			minimum()		{return INT_MIN;}
    static int			maximum()		{return INT_MAX;}
    static int			smallest()	{return 1;}
    static int			epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return true;}
};

template <>
struct limits <unsigned int>
{
    static unsigned int		minimum()		{return 0;}
    static unsigned int		maximum()		{return UINT_MAX;}
    static unsigned int		smallest()	{return 1;}
    static unsigned int		epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return false;}
};

template <>
struct limits <long>
{
    static long			minimum()		{return LONG_MIN;}
    static long			maximum()		{return LONG_MAX;}
    static long			smallest()	{return 1;}
    static long			epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return true;}
};

template <>
struct limits <unsigned long>
{
    static unsigned long	minimum()		{return 0;}
    static unsigned long	maximum()		{return ULONG_MAX;}
    static unsigned long	smallest()	{return 1;}
    static unsigned long	epsilon()	{return 1;}
    static bool			isIntegral()	{return true;}
    static bool			isSigned()	{return false;}
};

template <>
struct limits <float>
{
    static float		minimum()		{return -FLT_MAX;}
    static float		maximum()		{return FLT_MAX;}
    static float		smallest()	{return FLT_MIN;}
    static float		epsilon()	{return FLT_EPSILON;}
    static bool			isIntegral()	{return false;}
    static bool			isSigned()	{return true;}
};

template <>
struct limits <double>
{
    static double		minimum()		{return -DBL_MAX;}
    static double		maximum()		{return DBL_MAX;}
    static double		smallest()	{return DBL_MIN;}
    static double		epsilon()	{return DBL_EPSILON;}
    static bool			isIntegral()	{return false;}
    static bool			isSigned()	{return true;}
};

template <>
struct limits <long double>
{
    static long double		minimum()		{return -LDBL_MAX;}
    static long double		maximum()		{return LDBL_MAX;}
    static long double		smallest()	{return LDBL_MIN;}
    static long double		epsilon()	{return LDBL_EPSILON;}
    static bool			isIntegral()	{return false;}
    static bool			isSigned()	{return true;}
};


} // namespace Imath

#endif
