#pragma once


namespace filehandler
{


   class CLASS_DECL_sphere pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:
      pane_view(sp(base_application) papp);
      
      void rotate();

      void on_create_view(::user::view_creator_data * pcreatordata);
      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* pHint);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      DECL_GEN_SIGNAL(_001OnMenuMessage);
      virtual ~pane_view();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
      DECL_GEN_SIGNAL(_001OnCreate);
   };


} // namespace filehandler


