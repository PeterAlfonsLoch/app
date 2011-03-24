#pragma once

namespace user
{

   class tool_tip_tool;

   class tool_tip_window : public ::ca::window
   {
   public:
      enum e_message
      {
         MessageBaseToolTipText = WM_USER + 110
      };

      enum e_position
      {
         PositionCenter,
         PositionRandomTopRight
      };


      enum ETimer
      {
         TimerHideWindow = 1,
         TimerShowDelayed = 2,
      };

      enum EAlign
      {
         AlignNone = 0,
         AlignLeft = 1,
         AlignRight = 2,
         AlignTop = 4,
         AlignBottom = 8
      };

      typedef base_enum < EAlign, AlignNone > CEnumAlign;

      class CText
      {
      public:
         string m_str;
      };

      class CToolMap :
         public ::collection::map < int, int, tool_tip_tool *, tool_tip_tool * >
      {
      public:
          void AddTool(tool_tip_tool * ptool);
      };



   // Attributes
   protected:
      CEnumAlign              m_ealign;         // current alignment of the tool tip
      CEnumAlign              m_ealignDefault;  // default alignment of the tool tip
      ::ca::window *                  m_pwnd;           // ::ca::window associate with this tool tip wnd
      string                 m_strTip;         // tip string
      int                     m_iEventTool;     // item selected
      int                     m_iTool;          // item where the tip will be showed
      ::ca::font_sp                   m_font;           // tip string font
      point                  m_ptOffset;       // tip point offset
      size                   m_sizeArrow;      // arrow size
      bool                    m_bTipEnable;     // set if the tip is enabled

      point                  m_pt;             // coordinates fo the cursor position used to track changes in cursor position
      CToolMap                m_toolmap;        // ::collection::map of tool index to tool pointers

   public:
      void RemoveAllTools();
      tool_tip_tool * GetTool(int iTool);
      bool GetToolText(int iTool, string &str);
      void AddTool(tool_tip_tool * ptool);
      bool GetToolRect(int iTool, LPRECT lprect);
      tool_tip_window(::ca::application * papp);
      virtual ~tool_tip_window();
      void UpdateDrawingObjects();
      bool ShowTip();
      bool IsTipEnabled();
      void EnableTip(bool bEnable = true);
      bool HideTip();
      bool create(::ca::window * pwnd);
      bool CalcRect(::ca::graphics * pdc, LPRECT lprect, LPCRECT lprectToolScreen, const char * lpcsz);
      void ShowTip(int iTool, bool bForce = false);
      void SetPositionHint(::ca::window * pwnd, e_position eposition);
      void relay_event(tool_tip_tool * pwnd, gen::signal_object * pobj);

      afx_msg void OnPaint();
      afx_msg void OnTimer(UINT nIDEvent);
      afx_msg void OnSize(UINT nType, int cx, int cy);
      afx_msg void OnDestroy();
   };


} // namespace user