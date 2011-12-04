#include "StdAfx.h"

namespace user
{

   tool_tip_tool::tool_tip_tool()
   {
      m_uiBaseToolTipText  = 0xffffffff;
      m_pbasetooltiphdl    = NULL;
   }

   tool_tip_tool::~tool_tip_tool()
   {
      m_pbasetooltiphdl    = NULL;
   }

   void tool_tip_tool::BaseToolTipRelayEvent(gen::signal_object * pobj)
   {

      if(m_pbasetooltiphdl != NULL)
         m_pbasetooltiphdl->relay_event(this, pobj);

   }

   void tool_tip_tool::BaseToolTipSetHandler(tool_tip_window *phandler)
   {
      m_pbasetooltiphdl = phandler;
   }

   ::user::interaction * tool_tip_tool::BaseToolTipGetWnd()
   {
      return dynamic_cast < ::ca::window * > (this);
   }

   void tool_tip_tool::BaseToolTipGetRect(LPRECT lprect)
   {
      UNREFERENCED_PARAMETER(lprect);
   }

   int tool_tip_tool::BaseToolTipGetIndex()
   {
      return -1;
   }

   bool tool_tip_tool::BaseToolTipGetText(string & str)
   {
      UNREFERENCED_PARAMETER(str);
      return false;
   }

} // namespace user