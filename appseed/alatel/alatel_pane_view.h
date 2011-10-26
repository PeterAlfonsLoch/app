#pragma once


namespace alatel
{


   class frame;


   class CLASS_DECL_CA2_ALARM pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:


      frame *        m_pframePopup;

	   
      pane_view(::ca::application * papp);
      virtual ~pane_view();


      virtual void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void install_message_handling(user::win::message::dispatch * pinterface);
      virtual void on_show_view();

   #ifdef _DEBUG
	   virtual void assert_valid() const;
	   virtual void dump(dump_context& dc) const;
   #endif

	   DECL_GEN_SIGNAL(_001OnCreate)


   };


} // namespace alatel


