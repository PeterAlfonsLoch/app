#pragma once



namespace filemanager
{

   class callback;


   class document;
   class filemanager;




   class file_list_callback;


   class SimpleDialogBar;


   class CLASS_DECL_CORE schema :
      virtual public object
   {
   public:


      filemanager *              m_pfilemanager;

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

      SimpleDialogBar *    m_pdialogbar;


      sp(document) open(sp(::create_context) pcreatecontext = NULL, ::fs::data * pdata = NULL, list_data * pfilemanagerdata = NULL);
      sp(document) open_child(bool bMakeVisible = true, bool bTransparentBackground = false, sp(::user::interaction) pwndParent = NULL, list_data * pfilemanagerdata = NULL);
      sp(document) open_child_list(bool bMakeVisible = true, bool bTransparentBackground = false, sp(::user::interaction) pwndParent = NULL, list_data * pfilemanagerdata = NULL);

      sp(document) create_new_document(callback * pinterface);


      schema(filemanager * pfilemanager);
      virtual ~schema();


      virtual void Initialize(int32_t iTemplate, const char * pszMatter);


   };




} // namespace filemanager




