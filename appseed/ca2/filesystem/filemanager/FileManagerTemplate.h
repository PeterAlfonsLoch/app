#pragma once


class FileManagerCallbackInterface;


namespace filemanager
{


   class document;
   class filemanager;


} // namespace filemanager


class FileManagerFileListCallback;


namespace user
{


   class multiple_document_template;


} // namespace user


class SimpleDialogBar;


class CLASS_DECL_ca2 FileManagerTemplate :
   virtual public ::ca::object
{
public:


   ::filemanager::filemanager * m_pfilemanager;

   int32_t         m_iTemplate;
   int32_t         m_iNextDocument;

   string      m_strMenuBar;
   string      m_strToolBar;
   string      m_strToolBarSave;
   string      m_strDialogBar;
   string      m_strPopup;
   string      m_strFilePopup;
   string      m_strFilePopupSubstId;

   string      m_strFolderPopup;
   string      m_strDISection;

   id          m_idExpandBox;
   id          m_idCollapseBox;

   ::database::id m_dataidStatic;


   FileManagerFileListCallback * m_pfilelistcallback;


   string  m_strLevelUp;

   sp(::user::multiple_document_template) m_pdoctemplateMain;
   sp(::user::multiple_document_template) m_pdoctemplate;
   sp(::user::multiple_document_template) m_pdoctemplateChild;
   sp(::user::multiple_document_template) m_pdoctemplateChildList;

   SimpleDialogBar *    m_pdialogbar;


   sp(::filemanager::document) open(sp(::ca::create_context) pcreatecontext = NULL, ::fs::data * pdata = NULL, ::filemanager::data * pfilemanagerdata = NULL);
   sp(::filemanager::document) OpenChild(bool bMakeVisible = true, bool bTransparentBackground = false, sp(::user::interaction) pwndParent = NULL, ::filemanager::data * pfilemanagerdata = NULL);
   sp(::filemanager::document) open_child_list(bool bMakeVisible = true, bool bTransparentBackground = false, sp(::user::interaction) pwndParent = NULL, ::filemanager::data * pfilemanagerdata = NULL);

   sp(::filemanager::document) create_new_document(FileManagerCallbackInterface * pinterface);


   FileManagerTemplate(::filemanager::filemanager * pfilemanager);
   virtual ~FileManagerTemplate();


   virtual void Initialize( int32_t iTemplate, const char * pszMatter);


};


