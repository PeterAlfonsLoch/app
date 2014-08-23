#include "framework.h"


istring::istring(sp(::aura::application) papp)
{

   m_pauraapp = papp;

}
      
istring::~istring()
{
}


void istring::update_string()
{

   m_pauraapp->load_string(m_str, m_strTemplate);

}


istring & istring::operator = (const char * psz)
{
   
   m_strTemplate = psz;

   update_string();

   return *this;

}


