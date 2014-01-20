#pragma once


namespace user
{


   class tool_tip_window;


   class tool_tip_tool :
      virtual public ::object
   {
   public:
      tool_tip_tool();
      virtual ~tool_tip_tool();

      // Attributes
      void BaseToolTipSetHandler(tool_tip_window * phandler);

      // Message handling
      void BaseToolTipRelayEvent(signal_details * pobj);

      // Overridables
      virtual void BaseToolTipGetRect(LPRECT lprect);
      virtual bool BaseToolTipGetText(string & str);
      virtual int32_t BaseToolTipGetIndex();
      virtual sp(::user::interaction) BaseToolTipGetWnd();

      tool_tip_window *  m_pbasetooltiphdl;      // Base tooltip handler
      UINT              m_uiBaseToolTipText;    // Base tooltip text id

   };


} // namespace user



