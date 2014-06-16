#include "framework.h"


namespace exception
{


   exception::exception()
   {
      printf("log:exception");
   }


   exception::~exception()
   {
      printf("\n");

   }

   void exception::Delete()
   {

      delete this;

   }

   void rethrow(exception * pe)
   {

      throw pe;

   }

   const char * exception::what() const throw()
   {

      return m_strMessage;

   }


} // namespace exception


#ifdef APPLE_IOS



#else

#ifdef WINDOWS
__declspec(thread) string * t_pstrNote = NULL;
__declspec(thread) BYTE t_pdataNote[sizeof(string)];
#else
__thread string * t_pstrNote = NULL;
__thread BYTE t_pdataNote[sizeof(string)];
#endif

string __get_thread_note()
{
   if(t_pstrNote == NULL)
      return "";
   return *t_pstrNote;
}
void __set_thread_note(const char * pszNote)
{
   if(t_pstrNote == NULL)
   {
#undef new
      t_pstrNote = ::new(t_pdataNote) string;
#define new BASE_NEW
   }
   *t_pstrNote = pszNote;
}

#endif

