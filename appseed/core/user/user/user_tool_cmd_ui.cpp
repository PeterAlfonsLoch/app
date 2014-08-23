#include "framework.h"


/////////////////////////////////////////////////////////////////////////////
   // toolbar idle update through tool_cmd_ui class



namespace user
{

   tool_cmd_ui::tool_cmd_ui(sp(::aura::application) papp) :
      element(papp),
      cmd_ui(papp)
   {
   }
      
   tool_cmd_ui::~tool_cmd_ui()
   {
   }



   void tool_cmd_ui::Enable(bool bOn)
   {
      m_bEnableChanged = TRUE;
      toolbar* pToolBar = dynamic_cast < toolbar * > (m_pOther.m_p);
      ASSERT(pToolBar != NULL);
      ASSERT_KINDOF(toolbar, pToolBar);
      ASSERT(m_iIndex < m_iCount);

#ifdef WINDOWSEX
      UINT nNewStyle = pToolBar->GetButtonStyle((int32_t) m_iIndex) & ~TBBS_DISABLED;
      if (!bOn)
      {
         nNewStyle |= TBBS_DISABLED;
         // WINBUG: If a button is currently pressed and then is disabled
         // COMCTL32.DLL does not unpress the button, even after the mouse
         // button goes up!  We work around this bug by forcing TBBS_PRESSED
         // off when a button is disabled.
         nNewStyle &= ~TBBS_PRESSED;
      }
      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
      pToolBar->SetButtonStyle((int32_t) m_iIndex, nNewStyle);
#else
      throw todo(get_app());
#endif
   }

   void tool_cmd_ui::SetCheck(int32_t nCheck)
   {
      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
      toolbar* pToolBar = dynamic_cast < toolbar * > (m_pOther.m_p);
      ASSERT(pToolBar != NULL);
      ASSERT_KINDOF(toolbar, pToolBar);
      ASSERT(m_iIndex < m_iCount);

#ifdef WINDOWSEX
      UINT nNewStyle = pToolBar->GetButtonStyle((int32_t) m_iIndex) & ~(TBBS_CHECKED | TBBS_INDETERMINATE);
      if (nCheck == 1)
         nNewStyle |= TBBS_CHECKED;
      else if (nCheck == 2)
         nNewStyle |= TBBS_INDETERMINATE;
      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
      pToolBar->SetButtonStyle((int32_t) m_iIndex, nNewStyle | TBBS_CHECKBOX);
#else
      throw todo(get_app());
#endif
   }

   void tool_cmd_ui::SetText(const char *)
   {
      // ignore it
   }



} // namespace user

