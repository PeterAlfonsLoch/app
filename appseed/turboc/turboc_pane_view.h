#pragma once


namespace tc4
{


   class CLASS_DECL_APP_CORE_TC4 pane_view : 
      public ::userex::pane_tab_view
   {
   public:


      ::tc4::view *                     m_pflagview;


      pane_view(::aura::application * papp);
	   virtual ~pane_view();

      
      void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_handling(::message::dispatch * pinterface);

	   virtual void assert_valid() const;

      virtual void dump(dump_context & dumpcontext) const;

	   DECL_GEN_SIGNAL(_001OnCreate);

   };


} // namespace tc4













