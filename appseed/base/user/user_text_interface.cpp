#include "framework.h"

void text_interface::_001GetText(string & str)
{
   UNREFERENCED_PARAMETER(str);
}

void text_interface::_001GetSelText(string & str)
{
   UNREFERENCED_PARAMETER(str);
}

void text_interface::_001SetText(const char * psz, bool bUser)
{
   UNREFERENCED_PARAMETER(psz);
   UNREFERENCED_PARAMETER(bUser);
}

strsize text_interface::get_length()
{
   string str;
   _001GetText(str);
   return str.get_length();
}

void text_interface::get_string(char * psz, ::primitive::memory_size len)
{

   string str;

   _001GetText(str);

   strncpy(psz, str, len);

}

void text_interface::set_string(const char * psz, bool bUser)
{
   _001SetText(psz, bUser);
}
