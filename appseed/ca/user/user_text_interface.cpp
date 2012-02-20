#include "StdAfx.h"

void text_interface::_001GetText(string & str) const
{
   UNREFERENCED_PARAMETER(str);
}

void text_interface::_001GetSelText(string & str) const
{
   UNREFERENCED_PARAMETER(str);
}

void text_interface::_001SetText(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
}

strsize text_interface::get_length() const
{
   string str;
   _001GetText(str);
   return str.get_length();
}

void text_interface::get_string(char * psz) const
{
   string str;
   _001GetText(str);
   gen::str::copy(psz, str);
}

void text_interface::set_string(const char * psz)
{
   _001SetText(psz);
}
