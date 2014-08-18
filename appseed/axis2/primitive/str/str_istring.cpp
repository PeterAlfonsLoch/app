#include "framework.h"


istring::istring(sp(::axis::application) papp)
{

   m_pbaseapp = papp;

}
      
istring::~istring()
{
}


void istring::update_string()
{

   m_pbaseapp->load_string(m_str, m_strTemplate);

}


istring & istring::operator = (const char * psz)
{
   
   m_strTemplate = psz;

   update_string();

   return *this;

}


