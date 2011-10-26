#pragma once

namespace userbase
{
   
   
   class document;


   class FrameInitialUpdate
   {
   public:
      bool        m_bMakeVisible;
      ::userbase::document *  m_pdoc;
   };


   class CLASS_DECL_ca frame_window_interface :
      virtual public ::user::frame_window_interface,
      virtual public window_frame::WorkSetClientInterface,
      virtual public window_frame::WorkSetListener,
      virtual public database::user::interaction
   {
   public:

      static bool             g_bFullScreenAlt;

      bool                    m_bCustomFrame;
      bool                    m_bLayered;
      ::database::id          m_datakeyFrame;
      int                     m_iFrameData;


      void data_on_after_change(gen::signal_object * pobj);

      enum EColumn
      {
         ColumnWindowRect,
      };

      virtual void _000OnDraw(::ca::graphics * pdc);
      virtual void _001OnDraw(::ca::graphics * pdc);
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);
      DECL_GEN_VSIGNAL(_guserbaseOnInitialUpdate);
      frame_window_interface(::ca::application * papp);
      virtual ~frame_window_interface();

      virtual bool WfiOnMove(bool bTracking);
      virtual bool WfiOnSize(bool bTracking);

      virtual void WfiOnClose();
      virtual void WfiOnMaximize();
      virtual void WfiOnMinimize();
      virtual void WfiOnRestore();
      virtual void on_set_parent(::user::interaction* pguieParent);

      virtual bool DeferFullScreen(bool bFullScreen, bool bRestore);


      virtual void defer_synch_layered();
      virtual bool calc_layered();

      virtual bool IsFullScreen();
      virtual bool ShowWindowFullScreen(bool bFullScreen = true);

      virtual void assert_valid() const;
      virtual void dump(dump_context & dc) const;

      virtual void on_delete(::ca::ca * pca);
   };

} // namespace userbase

