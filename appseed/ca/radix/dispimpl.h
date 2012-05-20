// This is ca2 API library.
//
//
//
//
//
//
//
//

/////////////////////////////////////////////////////////////////////////////
// Platform specific defines

#include "cafxv_cpu.h"

#ifdef _X86_
#define _STACK_CHAR     long
#define _STACK_SHORT    long
#define _STACK_LONG     long
#define _STACK_LONGLONG int64_t
#define _STACK_FLOAT    float
#define _STACK_DOUBLE   double
#define _STACK_PTR      void *
#define _SCRATCH_SIZE   16
#define _STACK_OFFSET   0
#define _STACK_MIN      0
#endif

#ifdef _IA64_
#define _ALIGN_DOUBLES  8
#define _ALIGN_STACKPOINTER   16
#define _ALIGN_STACK   8
#define _STACK_CHAR      int64_t
#define _STACK_SHORT   int64_t
#define _STACK_INT      int64_t
#define _STACK_LONG     int64_t
#define _STACK_LONGLONG   int64_t
#define _STACK_FLOAT    float
#define _STACK_DOUBLE   double
#define _STACK_PTR      void *
#define _SCRATCH_SIZE   (16+(_SHADOW_DOUBLES*sizeof(double)))
#define _STACK_OFFSET   48
#define _STACK_MIN      64 // 8 64-bit registers
#endif

#ifdef _AMD64_
//#define _ALIGN_DOUBLES  8
#define _ALIGN_STACKPOINTER   16
#define _ALIGN_STACK   8
#define _STACK_CHAR      int64_t
#define _STACK_SHORT   int64_t
#define _STACK_INT      int64_t
#define _STACK_LONG     int64_t
#define _STACK_LONGLONG   int64_t
#define _STACK_FLOAT    float
#define _STACK_DOUBLE   double
#define _STACK_PTR      void *
#define _SCRATCH_SIZE   32
#define _STACK_OFFSET   0
#define _STACK_MIN      0
#endif

/////////////////////////////////////////////////////////////////////////////
