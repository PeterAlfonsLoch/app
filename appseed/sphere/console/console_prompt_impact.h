#pragma once



namespace console
{


   class CLASS_DECL_sphere prompt_impact :
      virtual public ::aura::impact
   {
   public:


      uint32_t             m_dwLastCaret;

      uint32_t             m_dwCaretPeriod;

      int                  m_iCursor;

      size                 m_sizeChar;

      string               m_strCommand;

      event                m_evNewChar;

      int                  m_iNewChar;

      DWORD                m_dwLastError;

      bool                 m_bOk;


      prompt_impact(::aura::application * papp);
      virtual ~prompt_impact();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual int getch();
      virtual int ungetch(int c);

      void simple_ui_draw_focus_rect(::draw2d::graphics * pgraphics);
      virtual bool keyboard_focus_is_focusable();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


      virtual void interpret_command();

   };


} // namespace console








































