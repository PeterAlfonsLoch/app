#pragma once


namespace netnodecfg
{

   class application;

   class configuration :
      public ::user::form_callback,
      public ::user::view_creator,
      public ip_enum
   {
   public:
      
	   
      string											         m_strServer;
      netnodecfg::application *							   m_papp;
      int												         m_iView;
      ::userbase::single_document_template *			   m_ptemplatePane;
      ::userex::pane_tab_view *							   m_ptabview;
      ::collection::string_map < form_document * >		m_mapdoc;
      ::collection::string_map < form_view * >			m_mapview;
      stringa											         m_straIp;


      configuration(netnodecfg::application * papp);
      virtual ~configuration();


      virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address);

      void set_configuration();

      void on_create_view(::user::view_creator_data * pcreatordata);


      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);


   };


} // namespace netnodecfg


