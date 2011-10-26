#pragma once

namespace status
{

   class application;

   class CLASS_DECL_CA2_TESSERACT status_class :
      virtual public ::user::form_callback,
      virtual public ::user::view_creator,
      virtual public ip_enum
   {
   public:
      status_class(::ca::application * papp);
      virtual ~status_class();


      virtual BOOL EnumCallbackFunction(int nAdapter, const in_addr& address);

      void perform();

      stringa m_straStatus;
      string m_strViewPath;

      void update_view();


      string get_status(var user);


      void on_create_view(::user::view_creator_data * pcreatordata);

      string                           m_strServer;
      int                              m_iView;
      ::userbase::single_document_template *     m_ptemplatePane;
      ::userex::pane_tab_view *           m_ptabview;
      form_document *                  m_pdocServer;
      form_view *                      m_pviewServer;
      stringa                        m_straIp;

      virtual bool BaseOnControlEvent(::user::form * pview, ::user::control_event * pevent);
      virtual void OnBeforeNavigate2(html::data * pdata, var & varFile, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel);
   };


} // namespace status
