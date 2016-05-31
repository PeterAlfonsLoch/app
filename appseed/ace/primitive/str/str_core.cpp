//#include "framework.h"



CLASS_DECL_ACE int64_t strtoi(const char * psz)
{
   return ::str::to_int64(psz);
}

CLASS_DECL_ACE int64_t strtoi(const unichar * psz)
{
   return wtoi64_dup(psz);
}



// string support for template collections



CLASS_DECL_ACE string_manager * s_pstringmanager = NULL;


string_manager * __get_string_manager()
{


   return s_pstringmanager;


}


//strsize const_empty_string::get_length() const
//{
//   return 0;
//}
//
//void const_empty_string::get_string(char * psz) const
//{
//   psz[0] = '\0';
//}
//
//void const_empty_string::set_string(const string & str, ::action::context actioncontext)
//{
//   UNREFERENCED_PARAMETER(str);
//   UNREFERENCED_PARAMETER(actioncontext);
//   throw "cannot set const string";
//}
//
//namespace str
//{
//   CLASS_DECL_ACE const_empty_string g_strEmpty;
//
//   CLASS_DECL_ACE string_interface & empty_string()
//   {
//      return g_strEmpty;
//   }
//
//}



