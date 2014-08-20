#pragma once

namespace platform
{

   class CLASS_DECL_CORE pane_view : 
      virtual public ::userex::pane_tab_view
   {
   public:
      pane_view(sp(::axis::application) papp); 

      virtual void on_create_view(::user::view_creator_data * pcreatordata);

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual ~pane_view();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      DECL_GEN_SIGNAL(_001OnCreate);
   };

} // namespace platform