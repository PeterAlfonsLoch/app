#pragma once

namespace netshareclient
{

   class application;

   class bergedge :
      virtual public ::user::form_callback,
      virtual public ::user::view_creator
   {
   public:

      string                                       m_strServer;
      netshareclient::application *                m_papp;
      int                                          m_iView;
      ::userbase::single_document_template *       m_ptemplatePane;
      ::userex::pane_tab_view *                      m_ptabview;
      form_document *                              m_pdocServer;
      form_view *                                  m_pviewServer;


      bergedge(netshareclient::application * papp);
      virtual ~bergedge();


      string get_server();


      void on_create_view(::user::view_creator_data * pcreatordata);


      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnBeforeNavigate2(html::data * pdata, var & varUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
   };


} // namespace netshareclient
