#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE manager_template :
      virtual public ::object
   {
   public:


      int32_t                    m_iTemplate;
      int32_t                    m_iNextDocument;

      string                     m_strMenuBar;
      string                     m_strToolBar;
      string                     m_strToolBarSave;
      string                     m_strDialogBar;
      string                     m_strPopup;
      string                     m_strFilePopup;
      string                     m_strFilePopupSubstId;

      string                     m_strFolderPopup;
      string                     m_strDISection;

      id                         m_idExpandBox;
      id                         m_idCollapseBox;

      ::database::id             m_dataidStatic;


      file_list_callback *       m_pfilelistcallback;

      string                     m_strLevelUp;


      sp(::user::multiple_document_template) m_pdoctemplateMain;
      sp(::user::multiple_document_template) m_pdoctemplate;
      sp(::user::multiple_document_template) m_pdoctemplateChild;
      sp(::user::multiple_document_template) m_pdoctemplateChildList;


      manager_template(sp(::base::application) papp);
      virtual ~manager_template();


      sp(manager) open(sp(::create_context) pcreatecontext = NULL, ::fs::data * pdata = NULL, data * pfilemanagerdata = NULL);
      sp(manager) open_child(bool bMakeVisible = true,bool bTransparentBackground = false,sp(::user::interaction) pwndParent = NULL,data * pfilemanagerdata = NULL);
      sp(manager) open_child_list(bool bMakeVisible = true,bool bTransparentBackground = false,sp(::user::interaction) pwndParent = NULL,data * pfilemanagerdata = NULL);

      sp(manager) create_new_document(callback * pinterface,sp(::create_context) pcreatecontext);




      virtual void Initialize(int32_t iTemplate, const char * pszMatter);


   };




} // namespace filemanager




