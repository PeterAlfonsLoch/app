//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#pragma once


namespace alatel
{


   class document;


   class CLASS_DECL_CA2_ALARM alarm_list_view :
      virtual public ::simple_list_view
   {
   public:

      string m_strProfile;


      alarm_list_view(::ca::application * papp);   
      virtual ~alarm_list_view();

      document * get_document();


      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual bool _001GetItemText(string &str, index iItem, index iSubItem, index iListItem);
      virtual count _001GetItemCount();
      virtual void _001InsertColumns();


      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnDeleteAlarm)
      DECL_GEN_SIGNAL(_001OnUpdateDeleteAlarm)


      virtual bool _001OnRemoveItem(index iItem);


      void _001OnSelectionChange();

      int set_cur_alarm(int iAlarm);
      int get_cur_alarm();
      
   
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   };


} // namespace alatel

