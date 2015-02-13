//#include "framework.h"



CTestCmdUI::CTestCmdUI(::aura::application * papp):
object(papp),
cmd_ui(papp)
{

   m_bEnabled        = TRUE;  // assume it is enabled
   m_echeck          = ::check::undefined;
   m_bRadio          = false;
   m_bRadioChanged   = false;

}


void CTestCmdUI::Enable(bool bOn,::action::context)
{

   m_bEnabled        = bOn;
   m_bEnableChanged  = true;

}


void CTestCmdUI::_001SetCheck(bool bCheck,::action::context context)
{

   ::cmd_ui::_001SetCheck(bCheck,context);

}


void CTestCmdUI::_001SetCheck(check::e_check echeck,::action::context)
{

   m_echeck = echeck;

}

void CTestCmdUI::SetRadio(bool bOn,::action::context)
{

   m_bRadio = bOn;
   m_bRadioChanged = true;


}

void CTestCmdUI::SetText(const char * lpszText,::action::context)
{

   m_strText = lpszText;

}



