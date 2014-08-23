/*
 *   Source file:      muldiv64.cpp
 *   Author:            Richard van der Wal
 *   Contact:         R.vdWal@xs4all.nl
 *
 *   Description:
 *      Implementation for muldiv64 and mulshr64
 *
 *   $Log: $
 */


/*
 * muldiv64
 * Multiplies an operant by a multiplier and divides the result by a divider
 * Used for scaling 64 bit integer values
 *     Xscaled = Xstart * Multiplier / Divider
 * Uses 128 bit intermediate result
 */

#include "framework.h"

#define ABS64(num) (num >=0 ? num : -num)


// http://www.cs.uaf.edu/~cs301/notes/Chapter5/node5.html
/*
 Multiply two 32-bit numbers, V1 and V2, to produce
 a 64 bit result in the HI/LO registers.
 The algorithm is high-school math:

         A B
       x C D
       ------
       AD || BD
 AC || CB || 0

 where A and B are the high and low int16_t words of V1,
 C and D are the int16_t words of V2, AD is the product of
 A and D, and X || Y is (X << 16) + Y.
 Since the algorithm is programmed in C, we need to be
 careful not to overflow.
*/


void mul64(uint64_t v1, uint64_t v2, uint64_t & hi, uint64_t & lo)
{
  uint64_t a, ca;
   uint64_t b, d;
   uint64_t x, y;

  a = (v1 >> 32) & 0xffffffff;
  b = v1 & 0xffffffff;
  ca = (v2 >> 32) & 0xffffffff;
  d = v2 & 0xffffffff;

  lo = b * d;                   /* BD */
  x = a * d + ca * b;            /* AD + CB */
  y = ((lo >> 32) & 0xffffffff) + x;

  lo = (lo & 0xffffffff) | ((y & 0xffffffff) << 32);
  hi = (y >> 32) & 0xffffffff;

  hi += a * ca;                  /* AC */
}

void mul64(int64_t v1, int64_t v2, int64_t & hi, uint64_t & lo)
{
   if(v1 > 0)
   {
      if(v2 > 0)
      {
         mul64((uint64_t) v1, (uint64_t) v2, (uint64_t &) hi, lo);
      }
      else
      {
         mul64((uint64_t) v1, (uint64_t) -(int64_t)v2, (uint64_t &) hi, lo);
         hi = -hi;
         lo = (uint64_t)-(int64_t)lo;
      }
   }
   else
   {
      if(v2 > 0)
      {
         mul64((uint64_t) -v1, (uint64_t) v2, (uint64_t &) hi, lo);
         hi = -hi;
         lo = (uint64_t)-(int64_t)lo;
      }
      else
      {
         mul64((uint64_t) -(int64_t)v1, (uint64_t) -(int64_t)v2, (uint64_t &) hi, lo);
      }
   }
}


// http://stackoverflow.com/questions/1870158/uint32_t-128-bit-division-on-64-bit-machine
   //64t hi, lo;
   //32t div;

   //64t rhi = hi/div;
   //64t rlo = hi % div + lo /div;
uint64_t div128_64(uint64_t hi, uint64_t lo, uint64_t div, uint64_t & remainder)
{
   for(size_t i = 1; i <= 64; ++i)
   {
      uint64_t t = int64_t(hi) >> 63;
      // t is all ones if x(63) = 1
      // Shift the hi|lo left one bit
      hi = (hi << 1) | (lo >> 63);
      lo = lo << 1;

      if((hi | t) >= div)
      {
         hi -= div;
         lo += 1;
      }
   }
   remainder = hi;
   return lo;
}

int64_t div128_64(int64_t hi, uint64_t lo, int64_t div, uint64_t & remainder)
{
   if(hi > 0)
   {
      if(div > 0)
      {
         return div128_64((uint64_t) hi, lo, (uint64_t) div, remainder);
      }
      else
      {
         return -(int64_t)div128_64((uint64_t) hi, lo, (uint64_t) -(int64_t)div, remainder);
      }
   }
   else
   {
      if(div > 0)
      {
         return -(int64_t)div128_64((uint64_t) -(int64_t)hi, (uint64_t)-(int64_t)lo, (uint64_t) div, remainder);
      }
      else
      {
         return div128_64((uint64_t) -(int64_t)hi, (uint64_t)-(int64_t)lo, (uint64_t) -(int64_t)div, remainder);
      }
   }
}



/*void div128(int64_t hi, int64_t lo, int64_t divisor, int64_t & result_hi, int64_t & result_lo, int64_t & remainder)
{

   result_hi = hi / divisor;
   result_lo = hi % divisor + lo / divisor;
   remainder =


  a = (v1 >> 32) & 0xffffffff;
  b = v1 & 0xffffffff;
  ca = (v2 >> 32) & 0xffffffff;
  d = v2 & 0xffffffff;

  lo = b * d;                   /* BD */
  /*x = a * d + ca * b;            /* AD + CB */
  /*y = ((lo >> 32) & 0xffffffff) + x;

  lo = (lo & 0xffffffff) | ((y & 0xffffffff) << 32);
  hi = (y >> 32) & 0xffffffff;

  hi += a * ca;                  /* AC */
//}


/** the two 32 bit parts of an 64 bit integer */
typedef struct  {
    uint32_t l : 32;
    uint32_t h : 32;
} uint64_uint32;

/**
 * determine the msb of a value in O(log log n)
 * @author Sean Eron Anderson
 */
inline uint32_t msb(uint64_t value)
{
    const int32_t MAX_LOGLOG = 6;
    const uint64_t BIT_LL[MAX_LOGLOG] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000, 0xFFFFFFFF00000000uLL};
    const uint32_t EXP_LL[MAX_LOGLOG] = {1, 2, 4, 8, 16, 32};
    uint32_t r = 0;
    for (int32_t i = MAX_LOGLOG-1; i >= 0; i--)  {
        if (value & BIT_LL[i])  {
            value >>= EXP_LL[i];
            r |= EXP_LL[i];
        }
    }
    return r;
}

/**
 * multiply a 64 and a 32 bit value and divide them by a 64 bit value.
 * result bits above 64 are ignored, so overflow flags are not set.
 * @author Axel Plinge
 * @param number       64 bit multiplicant
 * @param numerator    32 bit multiplicant
 * @param denominator  64 bit divisor
 * @return  (number*numerator)/denominator (+/-) 1
 */
/*inline uint64_t Mul32Div64(uint64_t number,uint32_t numerator,uint64_t denominator)
{
    uint64_t num_h = ((uint64_uint32*)&number)->h;
    uint64_t num_l = ((uint64_uint32*)&number)->l;
    uint64_t mul = numerator;
    uint64_t res;
    // lower 32bit portions yield 64 bit product
    // that can be divded directly giving 64 bits of result
    res = (num_l * mul)/denominator;
    // upper 32bit have to be shifted, calculate modulus 2^32
    uint64_t product_h = num_h*mul;
    uint64_t div_h = product_h/denominator; // division main
    uint64_t mod_h = product_h - denominator*div_h; // modulus
    // upper bits
    res += div_h<<32;
    if (mod_h==0)  {
   return res;
    }
    // remainder of division
    // if msb modulus < 32 we can be quick about it
    if ((mod_h>>32)==0) {
        res += (mod_h<<32)/denominator;
        return res;
    }
    // if we reach this point we have full 64 bit values i.e. a 96bit dividend
    // calculate an approximate result by shifting according to msb set
    int32_t msb_nominator = msb(mod_h)+32;
    int32_t msb_denominator = msb(denominator);
    int32_t msb = std::max(msb_nominator,msb_denominator);
    int32_t shift = msb-63;
    res += (mod_h << (32-shift)) / (denominator>>shift);
    return res;
}*/


static uint64_t const g_base = 1ULL<<32;
static uint64_t const g_maxdiv = (g_base-1)*g_base + (g_base-1);

uint64_t my_multdiv_64(uint64_t a, uint64_t b, uint64_t c)
{
    // First get the easy thing
    if(c == 0)
      return 0;

    uint64_t res = (a/c) * b + (a%c) * (b/c);
    a %= c;
    b %= c;
    // Are we done?
    if (a == 0 || b == 0)
        return res;
    // Is it easy to compute what remain to be added?
    if (c < g_base)
        return res + (a*b/c);
    // Now 0 < a < c, 0 < b < c, c >= 1ULL
    // Normalize
    uint64_t norm = g_maxdiv/c;
    c *= norm;
    a *= norm;
    // split into 2 digits
    uint64_t ah = a / g_base, al = a % g_base;
    uint64_t bh = b / g_base, bl = b % g_base;
    uint64_t ch = c / g_base, cl = c % g_base;
    // compute the product
    uint64_t p0 = al*bl;
    uint64_t p1 = p0 / g_base + al*bh;
    p0 %= g_base;
    uint64_t p2 = p1 / g_base + ah*bh;
    p1 = (p1 % g_base) + ah * bl;
    p2 += p1 / g_base;
    p1 %= g_base;
    // p2 holds 2 digits, p1 and p0 one

    // first digit is easy, not null only in case of overflow
//    uint64_t q2 = p2 / c;
    p2 = p2 % c;

    // second digit, estimate
    uint64_t q1 = p2 / ch;
    // and now adjust
    uint64_t rhat = p2 % ch;
    // the loop can be unrolled, it will be executed at most twice for
    // even g_bases -- three times for odd one -- due to the normalisation above
    while (q1 >= g_base || (rhat < g_base && q1*cl > rhat*g_base+p1)) {
        q1--;
        rhat += ch;
    }
    // subtract
    p1 = ((p2 % g_base) * g_base + p1) - q1 * cl;
    p2 = (p2 / g_base * g_base + p1 / g_base) - q1 * ch;
    p1 = p1 % g_base + (p2 % g_base) * g_base;

    // now p1 hold 2 digits, p0 one and p2 is to be ignored
    uint64_t q0 = p1 / ch;
    rhat = p1 % ch;
    while (q0 >= g_base || (rhat < g_base && q0*cl > rhat*g_base+p0)) {
        q0--;
        rhat += ch;
    }
    // we don't need to do the subtraction (needed only to get the remainder,
    // in which case we have to divide it by norm)
    return res + q0 + q1 * g_base; // + q2 *g_base*g_base
}


//
int64_t _stdcall muldiv64(int64_t number, int64_t numerator, int64_t denominator)
{
   return my_multdiv_64(number, numerator, denominator);

   int64_t hi;
   uint64_t lo;
   mul64(number, numerator, hi, lo);
   uint64_t remainder;
   return div128_64(hi, lo, denominator, remainder);
/*    uint64_t num_h = ((uint64_uint32*)&number)->h;
    uint64_t num_l = ((uint64_uint32*)&number)->l;
    uint64_t mul = numerator;
    uint64_t res;
    // lower 32bit portions yield 64 bit product
    // that can be divded directly giving 64 bits of result
    res = Mul32Div64(mul, num_l, denominator);
    // upper 32bit have to be shifted, calculate modulus 2^32
    uint64_t product_h = num_h*mul;
    uint64_t div_h = product_h/denominator; // division main
    uint64_t mod_h = product_h - denominator*div_h; // modulus
    // upper bits
    res += div_h<<32;
    if (mod_h==0)  {
   return res;
    }
    // remainder of division
    // if msb modulus < 32 we can be quick about it
    if ((mod_h>>32)==0) {
        res += (mod_h<<32)/denominator;
        return res;
    }
    // if we reach this point we have full 64 bit values i.e. a 96bit dividend
    // calculate an approximate result by shifting according to msb set
    int32_t msb_nominator = msb(mod_h)+32;
    int32_t msb_denominator = msb(denominator);
    int32_t msb = std::max(msb_nominator,msb_denominator);
    int32_t shift = msb-63;
    res += (mod_h << (32-shift)) / (denominator>>shift);
    return res;
   /*
   // Declare 128bit storage
   struct{
      unsigned long DW[4];
   }var128, quotient;
   // Change semantics for intermediate results for Full Div
   // by renaming the vars
   #define REMAINDER quotient
   #define QUOTIENT edi

   // Save combined sign on stack
   _asm{
      mov      eax, dword ptr[operant+4]
      xor      eax, dword ptr[multiplier+4]
      xor      eax, dword ptr[divider+4]
      pushfd
   }

   // Take absolute values because algorithm is for uint32_t only
   operant      = ABS64(operant);
   multiplier   = ABS64(multiplier);
   divider      = ABS64(divider);

   _asm{
      // First check divider for 0
      mov      eax, dword ptr[divider+4]
      or      eax, dword ptr[divider]
      jnz      dividerOK
      div      eax
dividerOK:
      lea      edi,[var128]               // edi = &var128
      // Check multiplier for 1 or 0
      xor      eax, eax
      cmp      eax, dword ptr[multiplier+4]
      jnz      startMUL
      cmp      eax, dword ptr[multiplier]
      jnz      multiNotNUL
      xor      edx, edx
      popfd                           // cleanup stack
      jmp      done
multiNotNUL:
      // set result HI part to 0
      xor      eax,eax
      mov      dword ptr[edi+12], eax
      mov      dword ptr[edi+8], eax
      mov      eax, 1
      cmp      eax, dword ptr[multiplier]
      jnz      smallMUL
      // Multiplier is 1 so just copy operant to result
      mov      eax, dword ptr[operant+4]
      mov      dword ptr[edi+4], eax
      mov      eax, dword ptr[operant]
      mov      dword ptr[edi], eax
      jmp      startDIV
smallMUL:
      // Test for 32/32 bit multiplication
        xor      eax, eax
        mov      ecx, dword ptr[operant+4]
        or      ecx, eax         ;test for both hiwords zero.
      jnz      startMUL
      // Do 32/32 bit multiplication
        mov      ecx, dword ptr[multiplier]
      mov      eax, dword ptr[operant]
      mul      ecx
      mov      dword ptr[edi+4], edx
      mov      dword ptr[edi], eax
      jmp      startDIV
startMUL:
      // Check signs
      // Multiply: var128 = operant * multiplier
      mov      eax, dword ptr[multiplier]      // eax = LO(multiplier)
      mul      dword ptr[operant]            // edx:eax = eax * LO(operant)
      mov      dword ptr[edi], eax            // var128.DW0 = eax
      mov      ecx, edx                  // ecx = edx

      mov      eax, dword ptr[multiplier]      // eax = LO(multiplier)
      mul      dword ptr[operant+4]         // edx:eax = eax * HI(operant)
      add      eax, ecx                  // eax = eax + ecx
      adc      edx, 0                     // edx = edx + 0 + carry
      mov      ebx, eax
      mov      ecx, edx

      mov      eax, dword ptr[multiplier+4]
      mul      dword ptr[operant]
      add      eax, ebx
      mov      dword ptr[edi+4], eax
      adc      ecx, edx
      pushfd

      mov      eax, dword ptr[multiplier+4]
      mul      dword ptr[operant+4]
      popfd
      adc      eax, ecx
      adc      edx, 0
      mov      dword ptr[edi+8], eax
      mov      dword ptr[edi+12], edx
startDIV:
      // Divide: var128 = var128 / divider
      //
      // Test divider = 32bit value
      mov      eax, dword ptr[divider+4]
      cmp      eax, 0
      jnz      fullDIV
      mov      ecx, dword ptr[divider]
      cmp      ecx, 1
      jz      applySign

      // Start 128/32 bit division
      mov      eax, dword ptr[edi+12]
      xor      edx, edx
      div      ecx
      mov      dword ptr[quotient+12], eax

      mov      eax, dword ptr[edi+8]
      div      ecx
      mov      dword ptr[quotient+8], eax

      mov      eax, dword ptr[edi+4]
      div      ecx
      mov      dword ptr[quotient+4], eax

      mov      eax, dword ptr[edi]
      div      ecx
      mov      dword ptr[quotient], eax

      // copy the quotient to the result storage (var128)
      mov      eax, dword ptr[quotient+12]
      mov      dword ptr[edi+12], eax
      mov      eax, dword ptr[quotient+8]
      mov      dword ptr[edi+8], eax
      mov      eax, dword ptr[quotient+4]
      mov      dword ptr[edi+4], eax
      mov      eax, dword ptr[quotient]
      mov      dword ptr[edi], eax
      // To sign correction and return
      jmp      applySign

fullDIV:
      // Full 128/64 bit division
      xor      eax, eax
      mov      dword ptr[REMAINDER+12], eax
      mov      dword ptr[REMAINDER+8], eax
      mov      dword ptr[REMAINDER+4], eax
      mov      dword ptr[REMAINDER], eax

      mov      ecx, 128
loop1:
      // Compute REMAINDER:QUOTIENT = REMAINDER:QUOTIENT shl 1
      shl      dword ptr[QUOTIENT], 1
      rcl      dword ptr[QUOTIENT+4], 1
      rcl      dword ptr[QUOTIENT+8], 1
      rcl      dword ptr[QUOTIENT+12], 1
      rcl      dword ptr[REMAINDER], 1
      rcl      dword ptr[REMAINDER+4], 1
      rcl      dword ptr[REMAINDER+8], 1
      rcl      dword ptr[REMAINDER+12], 1

      // Test (REMAINDER >= Divider)
      xor      eax, eax
      cmp      dword ptr[REMAINDER+12], eax
      ja      iftrue
      jb      iffalse

      cmp      dword ptr[REMAINDER+8], eax
      ja      iftrue
      jb      iffalse

      mov      eax, dword ptr[REMAINDER+4]
      cmp      eax, dword ptr[divider+4]
      ja      iftrue
      jb      iffalse

      mov      eax, dword ptr[REMAINDER]
      cmp      eax, dword ptr[divider]
      jb      iffalse
iftrue:
      // Remainder = remainder - divider
      mov      eax, dword ptr[divider]
      sub      dword ptr[REMAINDER], eax
      mov      eax, dword ptr[divider+4]
      sbb      dword ptr[REMAINDER+4], eax
      xor      eax, eax
      sbb      dword ptr[REMAINDER+8], eax
      sbb      dword ptr[REMAINDER+12], eax
      // Quotient = quotient +1
      add      dword ptr[QUOTIENT], 1
      adc      dword ptr[QUOTIENT+4], 0
      adc      dword ptr[QUOTIENT+8], 0
      adc      dword ptr[QUOTIENT+12], 0
iffalse:
      // Loop size = 101 bytes, is less than 127 so loop is possible
      loop   loop1

applySign:
      // Correct the sign of the result based on the stored combined sign
      popfd
      jns      storeRes
      not      dword ptr[edi+12]
      not      dword ptr[edi+ 8]
      not      dword ptr[edi+ 4]
      not      dword ptr[edi]
      add      dword ptr[edi], 1
      adc      dword ptr[edi+ 4], 0
      adc      dword ptr[edi+ 8], 0
      adc      dword ptr[edi+12], 0

storeRES:
      // get low order qword from var128
      mov      edx, dword ptr[edi+4]
      mov      eax, dword ptr[edi]
done:
   }
   // result is returned in edx:eax
   */
}

/*
 * mulshr64
 * Multiplies an operant by a multiplier and right shifts the result rshift times
 * Used for scaling 64 bit integer values
 *     Xscaled = (Xstart * Multiplier) SHR rshift
 * Uses 128 bit intermediate result
 */
int64_t _stdcall mulshr64(int64_t operant, int64_t multiplier, uchar rshift)
{
   return (operant * multiplier) >> rshift;
/*   // Declare 128bit storage
   struct{
      unsigned long DW[4];
   }var128;

   // Save combined sign on stack
   _asm{
      mov      eax, dword ptr[operant+4]
      xor      eax, dword ptr[multiplier+4]
      pushfd
   }

   // Take absolute values because algorithm is for uint32_t only
   operant      = ABS64(operant);
   multiplier   = ABS64(multiplier);

   _asm{
      // Test rshift for >128
      mov      al, byte ptr[rshift]
      cmp      al, 80
      jl      shiftOK
      popfd                           // cleanup stack
      xor      edx, edx
      xor      eax, eax
      jmp      done
shiftOK:
      lea      edi,[var128]               // edi = &var128
      // Check multiplier for 1 or 0
      xor      eax, eax
      cmp      eax, dword ptr[multiplier+4]
      jnz      startMUL
      cmp      eax, dword ptr[multiplier]
      jnz      multiNotNUL
      xor      edx, edx
      popfd                           // cleanup stack
      jmp      done
multiNotNUL:
      // set result HI part to 0
      xor      eax,eax
      mov      dword ptr[edi+12], eax
      mov      dword ptr[edi+8], eax
      mov      eax, 1
      cmp      eax, dword ptr[multiplier]
      jnz      smallMUL
      // Multiplier is 1 so just copy operant to result
      mov      eax, dword ptr[operant+4]
      mov      dword ptr[edi+4], eax
      mov      eax, dword ptr[operant]
      mov      dword ptr[edi], eax
      jmp      startDIV
smallMUL:
      // Test for 32/32 bit multiplication
        xor      eax, eax
        mov      ecx, dword ptr[operant+4]
        or      ecx, eax         ;test for both hiwords zero.
      jnz      startMUL
      // Do 32/32 bit multiplication
        mov      ecx, dword ptr[multiplier]
      mov      eax, dword ptr[operant]
      mul      ecx
      mov      dword ptr[edi+4], edx
      mov      dword ptr[edi], eax
      jmp      startDIV
startMUL:
      // Check signs
      // Multiply: var128 = operant * multiplier
      mov      eax, dword ptr[multiplier]      // eax = LO(multiplier)
      mul      dword ptr[operant]            // edx:eax = eax * LO(operant)
      mov      dword ptr[edi], eax            // var128.DW0 = eax
      mov      ecx, edx                  // ecx = edx

      mov      eax, dword ptr[multiplier]      // eax = LO(multiplier)
      mul      dword ptr[operant+4]         // edx:eax = eax * HI(operant)
      add      eax, ecx                  // eax = eax + ecx
      adc      edx, 0                     // edx = edx + 0 + carry
      mov      ebx, eax
      mov      ecx, edx

      mov      eax, dword ptr[multiplier+4]
      mul      dword ptr[operant]
      add      eax, ebx
      mov      dword ptr[edi+4], eax
      adc      ecx, edx
      pushfd

      mov      eax, dword ptr[multiplier+4]
      mul      dword ptr[operant+4]
      popfd
      adc      eax, ecx
      adc      edx, 0
      mov      dword ptr[edi+8], eax
      mov      dword ptr[edi+12], edx
startDIV:
      // Divide: var128 = var128 / (2^rshift)
      //
      xor      eax, eax
      mov      al, byte ptr[rshift]
      cmp      al, 0
      jz      applySign

      // Start 128bit right shift
      //
      // Test shift for multiples of 32
      mov      cl, 0x20
      div      cl
      mov      cl, al                  // Store number of 32 blocks in counter
      mov      char ptr[rshift], ah      // Store remaining number of shifts
      // Test shift not equal or larger than 4*32 already done at the begining
      // Do dword shift cl times (MAX = 3)
      xor      ch, ch
      xor      edx, edx
      jcxz   bitShift
      mov      eax, dword ptr[edi+4]
      mov      dword ptr[edi], eax
      mov      eax, dword ptr[edi+8]
      mov      dword ptr[edi+4], eax
      mov      eax, dword ptr[edi+12]
      mov      dword ptr[edi+8], eax
      mov      dword ptr[edi+12], edx
      dec      cx
      jcxz   bitShift
      mov      eax, dword ptr[edi+4]
      mov      dword ptr[edi], eax
      mov      eax, dword ptr[edi+8]
      mov      dword ptr[edi+4], eax
      mov      dword ptr[edi+8], edx
      dec      cx
      jcxz   bitShift
      mov      eax, dword ptr[edi+4]
      mov      dword ptr[edi], eax
      mov      dword ptr[edi+4], edx

bitShift:
      // Do multiple precision bitshift
      mov      cl, byte ptr[rshift]
      mov      eax, dword ptr[edi+4]
      shrd   dword ptr[edi], eax, cl
      mov      eax, dword ptr[edi+8]
      shrd   dword ptr[edi+4], eax, cl
      mov      eax, dword ptr[edi+12]
      shrd   dword ptr[edi+8], eax, cl
      // To sign correction and return

applySign:
      // Correct the sign of the result based on the stored combined sign
      popfd
      jns      storeRes
      not      dword ptr[edi+12]
      not      dword ptr[edi+ 8]
      not      dword ptr[edi+ 4]
      not      dword ptr[edi]
      add      dword ptr[edi], 1
      adc      dword ptr[edi+ 4], 0
      adc      dword ptr[edi+ 8], 0
      adc      dword ptr[edi+12], 0

storeRES:
      // get low order qword from var128
      mov      edx, dword ptr[edi+4]
      mov      eax, dword ptr[edi]
done:
   }
   // result is returned in edx:eax*/
}


