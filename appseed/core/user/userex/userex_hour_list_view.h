#pragma once


namespace userex
{


   class CLASS_DECL_CORE hour_list_view :
      virtual public ::simple_list_view
   {
   public:


      hour_list_view(sp(base_application) papp);   
      virtual ~hour_list_view();


      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      virtual void _001InsertColumns();

      virtual void _001OnSelectionChange();


      int32_t get_hour();
      int32_t set_hour(int32_t iHour);


      DECL_GEN_SIGNAL(_001OnCreate);


      
   
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };


} // namespace userex

