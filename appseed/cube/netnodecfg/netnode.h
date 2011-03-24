#pragma once

namespace netnodecfg
{

   class application;

   class netnode :
      public ::user::form_callback,
      public ::user::create_view,
      public ip_enum
   {
   public:
      netnode(netnodecfg::application * papp);
      virtual ~netnode();


      virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address);

      void set_configuration();

      void on_create_view(view_data * pviewdata);

      string                           m_strServer;
      netnodecfg::application *    m_papp;
      int                              m_iView;
      ::userbase::single_document_template *     m_ptemplatePane;
      ::userex::pane_tab_view *           m_ptabview;
      form_document *                  m_pdocServer;
      form_view *                      m_pviewServer;
      stringa                        m_straIp;

      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
   };


} // namespace netnodecfg
