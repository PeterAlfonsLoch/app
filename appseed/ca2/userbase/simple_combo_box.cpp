#include "framework.h"


simple_combo_box::simple_combo_box()
{

   

}


simple_combo_box::~simple_combo_box()
{
}


void simple_combo_box::_001OnDraw(::ca::graphics *pdc)
{

   ::userbase::combo_box::_001OnDraw(pdc);

}



void simple_combo_box::_001GetListText(index iSel, string & str) const
{

   if(iSel < 0)
      throw invalid_argument_exception();

   if(iSel >= m_straList.get_count())
      throw invalid_argument_exception();

   str = m_straList[iSel];

}


index simple_combo_box::_001FindListText(const string & str) const
{

   if(m_bCaseSensitiveMatch)
   {
      return m_straList.find_first(str);
   }
   else
   {
      return m_straList.find_first_ci(str);
   }

}


count simple_combo_box::_001GetListCount() const
{

   return m_straList.get_count();

}




