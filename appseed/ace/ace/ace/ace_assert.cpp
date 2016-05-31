//#include "framework.h"

CLASS_DECL_ACE int __cpp_assert_failed_line(const char * lpszFileName, int iLineNumber);

BEGIN_EXTERN_C

CLASS_DECL_ACE int __assert_failed_line(const char * lpszFileName, int iLineNumber)
{

   return __cpp_assert_failed_line(lpszFileName, iLineNumber);

}

END_EXTERN_C


CLASS_DECL_ACE int __cpp_assert_failed_line(const char * lpszFileName, int iLineNumber)
{

   thread * pthread = get_thread();

   if(pthread != NULL)
   {

      pthread->m_paceapp->m_pacesystem->assert_failed_line(lpszFileName,iLineNumber);

   }

#ifdef DEBUG

   char szTitle[1024];
   char szMessage[1024*4];

   strcpy(szTitle, "Assert failed");

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



