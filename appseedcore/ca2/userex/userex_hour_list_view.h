//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#pragma once


namespace userex
{


   class CLASS_DECL_ca hour_list_view :
      virtual public ::simple_list_view
   {
   public:


      hour_list_view(::ca::application * papp);   
      virtual ~hour_list_view();


      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
      virtual count _001GetItemCount();
      virtual void _001InsertColumns();

      virtual void _001OnSelectionChange();


      int get_hour();
      int set_hour(int iHour);


      DECL_GEN_SIGNAL(_001OnCreate)


      
   
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };


} // namespace userex

