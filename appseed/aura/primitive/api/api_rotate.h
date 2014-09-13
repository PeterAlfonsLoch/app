/* RotateDefs.h -- Rotate functions
2009-02-07 : Igor Pavlov : Public domain */
// from 7-zip on 2012-12-23, lunch time
#pragma once

BEGIN_EXTERN_C


#ifdef _MSC_VER



#define rotlFixed(x, n) _rotl((x), (n))
#define rotrFixed(x, n) _rotr((x), (n))

#else

#define rotlFixed(x, n) (((x) << (n)) | ((x) >> (32 - (n))))
#define rotrFixed(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

#endif


END_EXTERN_C
