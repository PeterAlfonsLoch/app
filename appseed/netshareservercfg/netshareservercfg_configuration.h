#pragma once


namespace netshareservercfg
{


   class CLASS_DECL_CA2_NETSHARESERVERCFG configuration :
      public ::user::form_callback,
      public ::user::view_creator,
      public ip_enum
   {
   public:
      
      
      
      string                                    m_strServer;
      int                                       m_iView;
      ::userbase::single_document_template *    m_ptemplatePane;
      ::userex::pane_tab_view *                 m_ptabview;
      form_document *                           m_pdocServer;
      form_view *                               m_pviewServer;
      stringa                                   m_straIp;


      configuration(::ca::application * papp);
      virtual ~configuration();


      virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address);

      void set_configuration();

      void on_create_view(::user::view_creator_data * pcreatordata);


      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnBeforeNavigate2(html::data * pdata, var & varUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);


   };


} // namespace netshareservercfg



