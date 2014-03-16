#include "framework.h"


simple_combo_box::simple_combo_box(sp(base_application) papp) :
      element(papp),
      ::user::scroll_view(papp),
      data::data_listener(papp),
      colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp),
      ::user::combo_box(papp)
{
         m_edatamode = data_mode_opaque;
}


simple_combo_box::~simple_combo_box()
{
}


void simple_combo_box::_001OnDraw(::draw2d::graphics *pdc)
{

   ::user::combo_box::_001OnDraw(pdc);

}



void simple_combo_box::_001GetListText(index iSel, string & str) const
{

   if(iSel < 0)
      throw invalid_argument_exception(get_app());

   if(iSel >= m_straList.get_count())
      throw invalid_argument_exception(get_app());

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


::count simple_combo_box::_001GetListCount() const
{

   return m_straList.get_count();

}





index simple_combo_box::AddString(const char * lpszString, uint_ptr dwItemData)
{

   ASSERT(m_edatamode == data_mode_opaque);

   if (m_edatamode != data_mode_opaque)
      return -1;

   m_straList.add(lpszString);

   m_uiptra.add(dwItemData);

   return m_straList.get_upper_bound();

}


index simple_combo_box::AddString(const char * lpszString, const string & strValue)
{

   ASSERT(m_edatamode == data_mode_string);

   if (m_edatamode != data_mode_string)
      return -1;

   m_straList.add(lpszString);

   m_uiptra.add((uint_ptr) id(strValue).m_pstr);

   return m_straList.get_upper_bound();

}

void simple_combo_box::_001SetCurSelByStringValue(const string & strValue, ::action::context actioncontext)
{

   _001SetCurSelByData((uint_ptr) id(strValue).m_pstr, actioncontext);

}


void simple_combo_box::_001SetCurSelByData(uint_ptr ui, ::action::context actioncontext)
{

   index iSel = m_uiptra.find_first(ui);

   if (iSel < 0)
      return;

   _001SetCurSel(iSel, actioncontext);

}


string simple_combo_box::_001GetCurSelStringValue()
{

   index iSel = _001GetCurSel();

   if (iSel < 0)
      return "";

   uint_ptr ui = m_uiptra[iSel];

   if (ui == 0)
      return "";

   return *((string *)ui);
 
}