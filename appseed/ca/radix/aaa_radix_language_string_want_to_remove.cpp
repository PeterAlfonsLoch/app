#include "StdAfx.h"

language_string::language_string()
{
}

language_string::~language_string()
{
   if(m_papp != NULL)
   {
      System.m_langstrptra.remove(this);
   }
}

string language_string::get(::ca::application * papp)
{
   if(m_id.is_empty())
      return m_str;
   else if(m_str.is_empty())
   {
      m_papp = papp->m_pappThis;
      System.m_langstrptra.add(this);
      m_str = System.load_string(m_id);
   }
   if(m_str.is_empty())
      return m_id;
   else
      return m_str;
}


void language_string::set_text(const char * psz)
{
   m_id.Empty();
   m_str = psz;
}


void language_string::set_text_id(const char * psz)
{
   m_str.Empty();
   m_id = psz;
}
