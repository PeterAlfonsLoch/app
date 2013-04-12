#pragma once


namespace userbase
{
   
   
   class document;


   class FrameInitialUpdate
   {
   public:


      bool                       m_bMakeVisible;
      sp(::userbase::document)     m_pdoc;


   };


   class CLASS_DECL_ca2 frame_window_interface :
      virtual public ::user::frame_window_interface,
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


      frame_window_interface();
      virtual ~frame_window_interface();


      virtual void _000OnDraw(::ca::graphics * pdc);
      virtual void _001OnDraw(::ca::graphics * pdc);
      virtual void install_message_handling(::ca::message::dispatch * pinterface);
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

      void data_on_after_change(::ca::signal_object * pobj);


   };


} // namespace userbase



