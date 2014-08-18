#include "framework.h"


bool (* g_pfn__assert_failed_line) (const char * lpszFileName,int32_t iLineNumber) = NULL;


CLASS_DECL_AXIS void set_assert_failed_line(bool(* pfn__assert_failed_line) (const char * lpszFileName,int32_t iLineNumber))
{

   g_pfn__assert_failed_line = pfn__assert_failed_line;
    
}

bool __axis_assert_failed_line(const char * lpszFileName,int32_t iLineNumber)
{

#ifdef DEBUG

   char szTitle[1024];
   char szMessage[1024 * 4];

   strcpy(szTitle,"Assert failed");

   sprintf(szMessage,"Assert failed!\n\nFile: %s\nLine: %d\n\nYou can choose to:\n\n\t - \"Cancel\": cancel debugging.\n\t - \"Try\": try debug break where assertion occurred.\n\t - \"Continue\": continue running",lpszFileName,iLineNumber);

   int iResult = simple_message_box(NULL,szMessage,szTitle,MB_CANCELTRYCONTINUE | MB_ICONERROR);

   if(iResult == IDCANCEL)
   {

      exit(0);

      return false;

   }
   else if(iResult == IDTRYAGAIN)
   {

      return false;

   }
   else
   {

      return true;

   }

#endif

   return false;


}

bool __assert_failed_line(const char * lpszFileName,int32_t iLineNumber)
{

   if(g_pfn__assert_failed_line != NULL)
   {
      return g_pfn__assert_failed_line(lpszFileName,iLineNumber);

   }

   return __axis_assert_failed_line(lpszFileName,iLineNumber);

}



