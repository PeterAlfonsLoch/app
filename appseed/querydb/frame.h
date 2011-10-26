#pragma once

namespace querydb
{
   class pane_view;

   class CLASS_DECL_CA2_QUERYDB frame :
      public simple_frame_window,
      public ::ca::message_window_simple_callback
   {
   public:

      pane_view *       m_ppaneview;


      frame(::ca::application * papp);
      virtual ~frame();


      virtual void install_message_handling(::user::win::message::dispatch * pinterface);


      virtual bool calc_layered();
      window_frame::FrameSchema * create_frame_schema();
	   
      virtual bool _001OnCommand(id id);
      virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

      virtual void _000OnDraw(::ca::graphics * pdc);

      virtual void message_window_message_handler(gen::signal_object * pobj);

	   DECL_GEN_SIGNAL(_001OnCreate)
	   DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnClose)

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context & dumpcontext) const;
   #endif

   };

} // namespace querydb