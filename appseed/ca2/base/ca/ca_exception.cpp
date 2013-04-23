#include "framework.h"

namespace ca
{

   exception::~exception()
   {
   }

   void exception::Delete()
   {
      delete this;
   }

   void CLASS_DECL_ca2 rethrow(exception * pe)
   {
      throw pe;
   }


} // namespace ca

#ifdef WINDOWS
__declspec(thread) vsstring * t_pstrNote = NULL;
__declspec(thread) BYTE t_pdataNote[sizeof(vsstring)];
#else
__thread vsstring * t_pstrNote = NULL;
__thread BYTE t_pdataNote[sizeof(vsstring)];
#endif

CLASS_DECL_ca2 vsstring __get_thread_note()
{
   if(t_pstrNote == NULL)
      return "";
   return *t_pstrNote;
}
CLASS_DECL_ca2 void __set_thread_note(const char * pszNote)
{
   if(t_pstrNote == NULL)
   {
#undef new
      t_pstrNote = ::new(t_pdataNote) vsstring;
#define new DEBUG_NEW
   }
   *t_pstrNote = pszNote;
}
