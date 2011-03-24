//
// Alá Telmo Friesen Son God
//
/////////////////////////////////////////////////////


#pragma once


namespace alatel
{

   class document;

   class CLASS_DECL_CA2_ALARM week_view :
      virtual public ::userbase::split_view,
      virtual public ::user::form_callback
   {
   public:
      week_view(::ca::application * papp);
      virtual ~week_view();


      alarm_list_view *             m_palarmlistview;
      form_document *               m_pdocWeekday;
      form_view *                   m_pviewWeekday;
      userex::hour_list_view *      m_phourlistview;
      userex::minute_list_view *    m_pminutelistview;
      userex::second_list_view *    m_psecondlistview;


      virtual int get_current_alarm();


      virtual bool create_views();
      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnAddAlarm)
      DECL_GEN_SIGNAL(_001OnUpdateAddAlarm)

      document * get_document();


      void FileManagerBrowse(const char * lpcwstr);

      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      virtual void on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint);
   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif
   };


} // namespace alatel
