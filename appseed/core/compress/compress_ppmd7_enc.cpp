/* Ppmd7Enc.ca -- PPMdH encoder
2010-03-12 : Igor Pavlov : Public domain
This code is based on PPMd var.H (2001): Dmitry Shkarin : Public domain */
// from 7-zip on 2012-12-23, dawn
#include "framework.h"

#define kTopValue (1 << 24)

void Ppmd7z_RangeEnc_Init(CPpmd7z_RangeEnc *p)
{
  p->Low = 0;
  p->range = 0xFFFFFFFF;
  p->Cache = 0;
  p->CacheSize = 1;
}

static void RangeEnc_ShiftLow(CPpmd7z_RangeEnc *p)
{
  if ((uint32_t)p->Low < (uint32_t)0xFF000000 || (uint32_t)(p->Low >> 32) != 0)
  {
    byte temp = p->Cache;
    do
    {
      p->Stream->Write(p->Stream, (byte)(temp + (byte)(p->Low >> 32)));
      temp = 0xFF;
    }
    while(--p->CacheSize != 0);
    p->Cache = (byte)((uint32_t)p->Low >> 24);
  }
  p->CacheSize++;
  p->Low = (uint32_t)p->Low << 8;
}

static void RangeEnc_Encode(CPpmd7z_RangeEnc *p, uint32_t start, uint32_t size, uint32_t total)
{
  p->Low += start * (p->range /= total);
  p->range *= size;
  while (p->range < kTopValue)
  {
    p->range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}

static void RangeEnc_EncodeBit_0(CPpmd7z_RangeEnc *p, uint32_t size0)
{
  p->range = (p->range >> 14) * size0;
  while (p->range < kTopValue)
  {
    p->range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}

static void RangeEnc_EncodeBit_1(CPpmd7z_RangeEnc *p, uint32_t size0)
{
  uint32_t newBound = (p->range >> 14) * size0;
  p->Low += newBound;
  p->range -= newBound;
  while (p->range < kTopValue)
  {
    p->range <<= 8;
    RangeEnc_ShiftLow(p);
  }
}

void Ppmd7z_RangeEnc_FlushData(CPpmd7z_RangeEnc *p)
{
  uint32_t i;
  for (i = 0; i < 5; i++)
    RangeEnc_ShiftLow(p);
}


#define MASK(sym) ((signed char *)charMask)[sym]

void Ppmd7_EncodeSymbol(CPpmd7 *p, CPpmd7z_RangeEnc *rc, int32_t symbol)
{
  size_t charMask[256 / sizeof(size_t)];
  if (p->MinContext->NumStats != 1)
  {
    CPpmd_State *s = Ppmd7_GetStats(p, p->MinContext);
    uint32_t sum;
    uint32_t i;
    if (s->Symbol == symbol)
    {
      RangeEnc_Encode(rc, 0, s->Freq, p->MinContext->SummFreq);
      p->FoundState = s;
      Ppmd7_Update1_0(p);
      return;
    }
    p->PrevSuccess = 0;
    sum = s->Freq;
    i = p->MinContext->NumStats - 1;
    do
    {
      if ((++s)->Symbol == symbol)
      {
        RangeEnc_Encode(rc, sum, s->Freq, p->MinContext->SummFreq);
        p->FoundState = s;
        Ppmd7_Update1(p);
        return;
      }
      sum += s->Freq;
    }
    while (--i);
    
    p->HiBitsFlag = p->HB2Flag[p->FoundState->Symbol];
    PPMD_SetAllBitsIn256Bytes(charMask);
    MASK(s->Symbol) = 0;
    i = p->MinContext->NumStats - 1;
    do { MASK((--s)->Symbol) = 0; } while (--i);
    RangeEnc_Encode(rc, sum, p->MinContext->SummFreq - sum, p->MinContext->SummFreq);
  }
  else
  {
    uint16_t *prob = Ppmd7_GetBinSumm(p);
    CPpmd_State *s = Ppmd7Context_OneState(p->MinContext);
    if (s->Symbol == symbol)
    {
      RangeEnc_EncodeBit_0(rc, *prob);
      *prob = (uint16_t)PPMD_UPDATE_PROB_0(*prob);
      p->FoundState = s;
      Ppmd7_UpdateBin(p);
      return;
    }
    else
    {
      RangeEnc_EncodeBit_1(rc, *prob);
      *prob = (uint16_t)PPMD_UPDATE_PROB_1(*prob);
      p->InitEsc = PPMD7_kExpEscape[*prob >> 10];
      PPMD_SetAllBitsIn256Bytes(charMask);
      MASK(s->Symbol) = 0;
      p->PrevSuccess = 0;
    }
  }
  for (;;)
  {
    uint32_t escFreq;
    CPpmd_See *see;
    CPpmd_State *s;
    uint32_t sum;
    uint32_t i, numMasked = p->MinContext->NumStats;
    do
    {
      p->OrderFall++;
      if (!p->MinContext->Suffix)
        return; /* EndMarker (symbol = -1) */
      p->MinContext = Ppmd7_GetContext(p, p->MinContext->Suffix);
    }
    while (p->MinContext->NumStats == numMasked);
    
    see = Ppmd7_MakeEscFreq(p, numMasked, &escFreq);
    s = Ppmd7_GetStats(p, p->MinContext);
    sum = 0;
    i = p->MinContext->NumStats;
    do
    {
      int32_t cur = s->Symbol;
      if (cur == symbol)
      {
        uint32_t low = sum;
        CPpmd_State *s1 = s;
        do
        {
          sum += (s->Freq & (int32_t)(MASK(s->Symbol)));
          s++;
        }
        while (--i);
        RangeEnc_Encode(rc, low, s1->Freq, sum + escFreq);
        Ppmd_See_Update(see);
        p->FoundState = s1;
        Ppmd7_Update2(p);
        return;
      }
      sum += (s->Freq & (int32_t)(MASK(cur)));
      MASK(cur) = 0;
      s++;
    }
    while (--i);
    
    RangeEnc_Encode(rc, sum, escFreq, sum + escFreq);
    see->Summ = (uint16_t)(see->Summ + sum + escFreq);
  }
}
