#pragma once


class OleFrameHook;


namespace user
{

   class document;


   class FrameInitialUpdate
   {
   public:


      bool                       m_bMakeVisible;
      sp(::user::document)     m_pdoc;


   };

   class CLASS_DECL_ca2 frame_window_interface :
      virtual public database::user::interaction,
      virtual public ::uinteraction::frame::WorkSetClientInterface,
      virtual public ::uinteraction::frame::WorkSetListener
   {
   public:

      static bool             g_bFullScreenAlt;
      bool                    m_bAutoWindowFrame;
      bool                    m_bWindowFrame;
      bool                    m_bLayered;
      ::database::id          m_datakeyFrame;
      int32_t                     m_iFrameData;


      enum EColumn
      {
         ColumnWindowRect,
      };

      sp(document_template)           m_pdocumenttemplate;


      frame_window_interface();
      virtual ~frame_window_interface();


      virtual void SetBorderRect(LPCRECT lpcrect);
      virtual void GetBorderRect(LPRECT lprect);
      virtual bool _001IsFrameWnd();


      //virtual ::user::OleFrameHook * GetNotifyHook();
      virtual void NotifyFloatingWindows(uint32_t dwFlags);

      virtual string get_window_default_matter();
      virtual ::user::interaction::e_type get_window_type();

      
      virtual bool on_simple_command(e_simple_command ecommand, LPARAM lparam, LRESULT & lresult);
      virtual void _000OnDraw(::ca2::graphics * pdc);
      virtual void _001OnDraw(::ca2::graphics * pdc);
      virtual void install_message_handling(::ca2::message::dispatch * pinterface);
      DECL_GEN_VSIGNAL(_guserbaseOnInitialUpdate);

      virtual bool WfiOnMove(bool bTracking);
      virtual bool WfiOnSize(bool bTracking);

      virtual void WfiOnClose();
      virtual void WfiOnMaximize();
      virtual void WfiOnMinimize();
      virtual void WfiOnRestore();
      virtual void on_set_parent(sp(::user::interaction) pguieParent);

      virtual bool DeferFullScreen(bool bFullScreen, bool bRestore);


      virtual void defer_synch_layered();
      virtual bool calc_layered();

      virtual bool IsFullScreen();
      virtual bool ShowWindowFullScreen(bool bFullScreen = true, bool bRestore = true);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dc) const;

      //

      void data_on_after_change(::ca2::signal_object * pobj);


   };


} // namespace user



#pragma once

