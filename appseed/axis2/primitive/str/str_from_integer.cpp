#include "framework.h"


 string i64toa_dup(int64_t i, int32_t iAxis)
{

   char sz[128 + 64];

   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return sz;
   }
   bool bNegative = false;
   if(i < 0)
   {
      i = -i;
      bNegative = true;
   }
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iAxis);
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
      i = i / iAxis;
      iIndex++;
   }
   if(bNegative)
   {
      sz[iIndex] = '-';
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);

   return sz;

}


 string i64toa_dup(int64_t i)
{

   return i64toa_dup(i, 10);

}



 string ui64toa_dup(int64_t i, int32_t iAxis)
{

   char sz[128 + 64];

   if(i == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return sz;
   }
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iAxis);
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
      i = i / iAxis;
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);

   return sz;

}


 string ui64toa_dup(int64_t i)
{

   return ui64toa_dup(i, 10);

}





 void ultoa_dup(char * sz, uint64_t ui, int32_t iAxis)
{
   if(ui == 0)
   {
      sz[0] = '0';
      sz[1] = '\0';
      return;
   }
   int32_t iIndex = 0;
   while(ui > 0)
   {
      int32_t iDigit = (ui % iAxis);
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
      ui = ui / iAxis;
      iIndex++;
   }
   sz[iIndex] = '\0';
   str_reverse(sz);
}



void ltoa_dup(char * sz, int64_t i, int32_t iAxis)
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
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iAxis);
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
      i = i / iAxis;
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



























void ultow_dup(wchar_t * sz, uint64_t ui, int32_t iAxis)
{
   if(ui == 0)
   {
      sz[0] = L'0';
      sz[1] = L'\0';
      return;
   }
   int32_t iIndex = 0;
   while(ui > 0)
   {
      int32_t iDigit = (ui % iAxis);
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
      ui = ui / iAxis;
      iIndex++;
   }
   sz[iIndex] = L'\0';
   wcs_reverse(sz);
}



void ltow_dup(wchar_t * sz, int64_t i, int32_t iAxis)
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
   int32_t iIndex = 0;
   while(i > 0)
   {
      int32_t iDigit = (i % iAxis);
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
      i = i / iAxis;
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








