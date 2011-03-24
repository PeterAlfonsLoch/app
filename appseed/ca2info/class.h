#pragma once

namespace ca2info
{

   class application;

   class CLASS_DECL_CA2_STATUS ca2info_class :
      public ::user::form_callback,
      public ::user::create_view,
      public ip_enum
   {
   public:
      ca2info_class(::ca::application * papp);
      virtual ~ca2info_class();


      virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address);

      void perform();

      stringa m_straStatus;
      string m_strViewPath;

      void update_view();


      void on_create_view(view_data * pviewdata);

      string                           m_strServer;
      int                              m_iView;
      ::userbase::single_document_template *     m_ptemplatePane;
      ::userex::pane_tab_view *           m_ptabview;
      form_document *                  m_pdocServer;
      form_view *                      m_pviewServer;
      stringa                        m_straIp;

      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnBeforeNavigate2(const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
   };


} // namespace ca2info
