#include "framework.h"


istring::istring(sp(::ca::application) papp)
{

   m_papp = papp;

}
      
istring::~istring()
{
}


void istring::update_string()
{

   m_str = App(m_papp).load_string(m_strTemplate);

}


istring & istring::operator = (const char * psz)
{
   
   m_strTemplate = psz;

   update_string();

   return *this;

}


