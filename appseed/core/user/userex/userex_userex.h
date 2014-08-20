#pragma once


class form_document;
class form_view;


namespace userex
{


   class keyboard;
   class front_end_schema;
   class document_manager;
   class impact_system;
   class document;


   class CLASS_DECL_CORE userex :
      virtual public ::user::core,
      virtual public ::user::server,
      virtual public BaseMenuCentralContainer,
      virtual public ::database::client
   {
   public:



      sp(::user::multiple_document_template)    m_ptemplateForm;
      sp(::user::multiple_document_template)    m_ptemplateChildForm;
      sp(::user::multiple_document_template)    m_ptemplatePlaceHolder;


      filemanager::_shell::ImageSet *           m_pshellimageset;


      ::user::front_end_schema *                m_pufeschema;
      ::user::front_end *                       m_pufe;
      stringa                       m_straEscape;






      userex(sp(::axis::application) papp);
      virtual ~userex();


      filemanager::_shell::ImageSet & shellimageset();

      virtual bool initialize1();
      virtual bool initialize2();
      virtual bool initialize();



      string message_box(const char * pszMatter, property_set & propertyset);
      virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, ::duration durationTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);

      virtual void data_on_after_change(signal_details * pobj);

      class keyboard & keyboard();


      virtual sp(type) controltype_to_typeinfo(::user::control::e_type type);


      virtual int32_t GetVisibleTopLevelFrameCountExcept(sp(::user::interaction) pwndExcept);


      virtual void SendMessageToWindows(UINT message, WPARAM wParam, LPARAM lParam);

      virtual void AddToRecentFileList(const char * lpszPathName);

      ::user::front_end_schema * GetUfeSchema();
      ::user::front_end * GetUfe();

      virtual bool finalize();

      virtual void _001CloseAllDocuments(bool bEndSession);
      void add_document_template(sp(::user::impact_system) ptemplate);
      virtual sp(::user::document) _vmsguserbaseOpenDocumentFile(const char * lpszFileName);

      virtual bool _001OnCmdMsg(::axis::cmd_msg * pcmdmsg);


      virtual void _001OnFileNew();


      void defer_add_document_template(sp(::user::impact_system) ptemplate);







      int32_t GetVisibleFrameCount();
      int32_t GetVisibleFrameCountExcept(sp(::user::interaction) pwndExcept);

      DECL_GEN_SIGNAL(VmsGuiiOnAppLanguage);


         virtual int32_t exit_instance();

      void LoadStdProfileSettings(UINT nMaxMRU = ___MRU_COUNT);

      ::count get_template_count() const;
      sp(impact_system) get_template(index index) const;



      sp(::form_document)   create_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_form(sp(form_view) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_child_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::form_document)   create_child_form(sp(form_view) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var = ::var(::var::type_empty_argument));
      sp(::user::document) hold(sp(::user::interaction) pui);

   };


   CLASS_DECL_CORE::user::front_end_schema * GetUfeSchema(sp(::axis::application) papp);
   CLASS_DECL_CORE::user::front_end * GetUfe(sp(::axis::application) papp);


} // namespace core


