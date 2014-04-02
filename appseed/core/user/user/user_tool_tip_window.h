#pragma once

namespace user
{

   class tool_tip_tool;

   class tool_tip_window : public window
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
         public map < int32_t, int32_t, tool_tip_tool *, tool_tip_tool * >
      {
      public:
          void AddTool(tool_tip_tool * ptool);
      };


      CEnumAlign                 m_ealign;         // current alignment of the tool tip
      CEnumAlign                 m_ealignDefault;  // default alignment of the tool tip
      sp(::user::interaction)      m_pwnd;           // window associate with this tool tip wnd
      string                     m_strTip;         // tip string
      int32_t                        m_iEventTool;     // item selected
      int32_t                        m_iTool;          // item where the tip will be showed
      ::draw2d::font_sp              m_font;           // tip string font
      point                      m_ptOffset;       // tip point offset
      size                       m_sizeArrow;      // arrow size
      bool                       m_bTipEnable;     // set if the tip is enabled

      point                      m_pt;             // coordinates fo the cursor position used to track changes in cursor position
      CToolMap                   m_toolmap;        // map of tool index to tool pointers

      void RemoveAllTools();
      tool_tip_tool * GetTool(int32_t iTool);
      bool GetToolText(int32_t iTool, string &str);
      void AddTool(tool_tip_tool * ptool);
      bool GetToolRect(int32_t iTool, LPRECT lprect);
      tool_tip_window(sp(base_application) papp);
      virtual ~tool_tip_window();
      void update_drawing_objects();
      bool ShowTip();
      bool IsTipEnabled();
      void EnableTip(bool bEnable = true);
      bool HideTip();
      virtual bool create(sp(::user::interaction) pwnd, id id);
      bool CalcRect(::draw2d::graphics * pdc, LPRECT lprect, LPCRECT lprectToolScreen, const char * lpcsz);
      void ShowTip(int32_t iTool, bool bForce = false);
      void SetPositionHint(::window_sp pwnd, e_position eposition);
      void relay_event(tool_tip_tool * pwnd, signal_details * pobj);

      void OnPaint();
      void OnTimer(UINT nIDEvent);
      void OnSize(UINT nType, int32_t cx, int32_t cy);
      void OnDestroy();


   };


} // namespace user



