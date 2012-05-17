#include "framework.h"


void ultoa_dup(char * sz, uint64_t ui, int iBase)
{
   if(ui == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return;
   }
   int iIndex = 0;
   while(ui > 0)
   {
      int iDigit = (ui % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      ui = ui / iBase;
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);
}



void ltoa_dup(char * sz, int64_t i, int iBase)
{
   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   int iIndex = 0;
   while(i > 0)
   {
      int iDigit = (i % iBase);
      char ch;
      if(iDigit <= 9)
      {
         ch = iDigit + '0';
      }
      else
      {
         ch = iDigit - 10 + 'a';
      }
      sz[iIndex] =  ch;
      i = i / iBase;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = '-';
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);
}



























void ultow_dup(wchar_t * sz, uint64_t ui, int iBase)
{
   if(ui == 0)
   {
      sz[0] = L'0';
      sz[1] = L'\0';
      return;
   }
   int iIndex = 0;
   while(ui > 0)
   {
      int iDigit = (ui % iBase);
      wchar_t wch;
      if(iDigit <= 9)
      {
         wch = iDigit + L'0';
      }
      else
      {
         wch = iDigit - 10 + L'a';
      }
      sz[iIndex] =  wch;
      ui = ui / iBase;
      iIndex++;
   }
   sz[iIndex] = L'\0';
   wcs_reverse(sz);
}



void ltow_dup(wchar_t * sz, int64_t i, int iBase)
{
   if(i == 0)
   {
      sz[0] = L'0';
      sz[1] = L'\0';
      return;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   int iIndex = 0;
   while(i > 0)
   {
      int iDigit = (i % iBase);
      wchar_t wch;
      if(iDigit <= 9)
      {
         wch = iDigit + L'0';
      }
      else
      {
         wch = iDigit - 10 + L'a';
      }
      sz[iIndex] =  wch;
      i = i / iBase;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = L'-';
      iIndex++;
   }
   sz[iIndex] = L'\0';
   wcs_reverse(sz);
}


























