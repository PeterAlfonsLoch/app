#include "framework.h"
#include "freeimage/source/freeimage.h"

#ifdef WINDOWS
#include <cderr.h>      // Commdlg Error definitions
#include <winspool.h>
#endif


// CLASS_DECL_CORE string g_strNote;


namespace core
{


   void format_strings(string & rString, const char * lpszFormat, const char * const* rglpsz, int32_t nString)
   {
      ENSURE_ARG(lpszFormat != NULL);
      ENSURE_ARG(rglpsz != NULL);
      // determine length of destination string, not including NULL terminator
      strsize nTotalLen = 0;
      const char * pchSrc = lpszFormat;
      //      strsize count;
      while (*pchSrc != '\0')
      {
         if (pchSrc[0] == '%' &&
            ( (pchSrc[1] >= '1' && pchSrc[1] <= '9') ||
            (pchSrc[1] >= 'A' && pchSrc[1] <= 'Z')) )
         {
            // %A comes after %9 -- we'll need it someday
            int32_t i;
            if (pchSrc[1] > '9')
               i = 9 + (pchSrc[1] - 'A');
            else
               i = pchSrc[1] - '1';
            pchSrc += 2;
            if (i >= nString)
               ++nTotalLen;
            else if (rglpsz[i] != NULL)
               nTotalLen += strlen(rglpsz[i]);
         }
         else
         {
            pchSrc = ::str::utf8_inc_slide(&nTotalLen, pchSrc);
         }
      }

      pchSrc = lpszFormat;
      char * pchDest = rString.GetBuffer(nTotalLen);
      while (*pchSrc != '\0')
      {
         if (pchSrc[0] == '%' &&
            ( (pchSrc[1] >= '1' && pchSrc[1] <= '9') ||
            (pchSrc[1] >= 'A' && pchSrc[1] <= 'Z')) )
         {
            // %A comes after %9 -- we'll need it someday
            int32_t i;
            if (pchSrc[1] > '9')
               i = 9 + (pchSrc[1] - 'A');
            else
               i = pchSrc[1] - '1';
            pchSrc += 2;
            if (i >= nString)
            {
               //               TRACE(::aura::trace::category_AppMsg, 0, "Error: illegal string index requested %d.\n", i);
               *pchDest++ = '?';
               nTotalLen--;
            }
            else if (rglpsz[i] != NULL)
            {
               size_t nLen = strlen(rglpsz[i]);
               ::aura::strcpy_s(pchDest, nTotalLen + 1, rglpsz[i]);
               nTotalLen -= nLen;
               pchDest += nLen;
            }
         }
         else
         {

            ::str::utf8_inc_copy_slide_back(&nTotalLen, pchDest, pchSrc);

         }

      }
      rString.ReleaseBuffer((int32_t)((const char *)pchDest - (const char *)rString));
      // ReleaseBuffer will assert if we went too far
   }

   bool extract_sub_string(string & rString, const char * lpszFullString, int32_t iSubString, char chSep)
   {
      if (lpszFullString == NULL)
         return FALSE;

      while (iSubString--)
      {
         lpszFullString = strchr(lpszFullString, chSep);
         if (lpszFullString == NULL)
         {
            rString.Empty();        // return is_empty string as well
            return FALSE;
         }
         lpszFullString++;       // point past the separator
      }

      const char * lpchEnd = strchr(lpszFullString, chSep);

      strsize nLen = (lpchEnd == NULL) ? strlen(lpszFullString) : (int32_t)(lpchEnd - lpszFullString);

      ASSERT(nLen >= 0);

      ::axis::memcpy_s(rString.GetBufferSetLength(nLen), nLen*sizeof(char), lpszFullString, nLen*sizeof(char));

      rString.ReleaseBuffer();   // Need to call ReleaseBuffer after calling GetBufferSetLength

      return TRUE;
   }


   CLASS_DECL_CORE bool init_core()
   {

      if(!defer_base_init())
         return false;

      try
      {

         FreeImage_Initialise(FALSE);

      }
      catch(...)
      {

         ::simple_message_box(NULL,"Failure to initialize FreeImage (::core::init_core)","FreeImage_Initialise failure",MB_ICONEXCLAMATION);

         return false;

      }

      return true;

   }


   CLASS_DECL_CORE bool term_core()
   {

      FreeImage_DeInitialise();

      defer_base_term();

      return true;

   }


} // namespace core






#ifdef WINDOWS

extern "C" const GUID LIBID_Lib =                 {0x44EC0535,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3}};
extern "C" const CLSID CLSID_Registrar =              {0x44EC053A,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3}};
extern "C" const IID IID_IRegistrar =              {0x44EC053B,0x400F,0x11D0,{0x9D,0xCD,0x00,0xA0,0xC9,0x03,0x91,0xD3}};
extern "C" const IID IID_IAxWinHostWindow =           {0xb6ea2050,0x048a,0x11d1,{0x82,0xb9,0x00,0xc0,0x4f,0xb9,0x94,0x2e}};
extern "C" const IID IID_IAxWinAmbientDispatch =        {0xb6ea2051,0x048a,0x11d1,{0x82,0xb9,0x00,0xc0,0x4f,0xb9,0x94,0x2e}};
extern "C" const IID IID_IInternalConnection =        {0x72AD0770,0x6A9F,0x11d1,{0xBC,0xEC,0x00,0x60,0x08,0x8F,0x44,0x4E}};
extern "C" const IID IID_IDocHostUIHandlerDispatch =     {0x425B5AF0,0x65F1,0x11d1,{0x96,0x11,0x00,0x00,0xF8,0x1E,0x0D,0x0D}};
extern "C" const IID IID_IAxWinHostWindowLic =        {0x3935BDA8,0x4ED9,0x495c,{0x86,0x50,0xE0,0x1F,0xC1,0xE3,0x8A,0x4B}};
extern "C" const IID IID_IAxWinAmbientDispatchEx =     {0xB2D0778B,0xAC99,0x4c58,{0xA5,0xC8,0xE7,0x72,0x4E,0x53,0x16,0xB5}};


#endif


void gen_CrtErrorCheck(int32_t i);


void gen_CrtErrorCheck(int32_t i)
{
   UNREFERENCED_PARAMETER(i);
}





int g_iCoreRefCount = 0;


CLASS_DECL_CORE bool defer_core_init()
{

   g_iCoreRefCount++;

   if(g_iCoreRefCount > 1)
      return true;

   if(!::core::init_core())
      return false;

   return true;

}


CLASS_DECL_CORE bool defer_core_term()
{

   g_iCoreRefCount--;

   if(g_iCoreRefCount >= 1)
      return true;

   ::core::term_core();

   return true;

}




