//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#pragma once


namespace userex
{


   class CLASS_DECL_ca minute_list_view :
      virtual public ::simple_list_view
   {
   public:


      minute_list_view(::ax::application * papp);   
      virtual ~minute_list_view();


      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      virtual void _001GetItemText(::user::list_item * pitem);
      virtual count _001GetItemCount();
      virtual void _001InsertColumns();

      virtual void _001OnSelectionChange();

      int get_minute();
      int set_minute(int iMinute);

      DECL_GEN_SIGNAL(_001OnCreate)


      
   
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };


} // namespace userex

