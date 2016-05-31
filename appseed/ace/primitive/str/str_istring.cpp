//#include "framework.h"


istring::istring(::ace::application * papp)
{

   m_pauraapp = papp;

}
      
istring::~istring()
{
}


void istring::update_string()
{

   m_str = m_pauraapp->lstr(m_strTemplate, m_strTemplate);

}


istring & istring::operator = (const char * psz)
{
   
   m_strTemplate = psz;

   update_string();

   return *this;

}


