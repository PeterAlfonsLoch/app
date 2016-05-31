//#include "framework.h"


istring::istring(::ace::application * papp)
{

   m_paceapp = papp;

}
      
istring::~istring()
{
}


void istring::update_string()
{

   m_str = m_paceapp->lstr(m_strTemplate, m_strTemplate);

}


istring & istring::operator = (const char * psz)
{
   
   m_strTemplate = psz;

   update_string();

   return *this;

}


