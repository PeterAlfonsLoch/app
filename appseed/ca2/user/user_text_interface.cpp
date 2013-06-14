#include "framework.h"

void text_interface::_001GetText(string & str)
{
   UNREFERENCED_PARAMETER(str);
}

void text_interface::_001GetSelText(string & str)
{
   UNREFERENCED_PARAMETER(str);
}

void text_interface::_001SetText(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
}

strsize text_interface::get_length()
{
   string str;
   _001GetText(str);
   return str.get_length();
}

void text_interface::get_string(char * psz)
{
   string str;
   _001GetText(str);
   ::ca2::str::copy(psz, str);
}

void text_interface::set_string(const char * psz)
{
   _001SetText(psz);
}
