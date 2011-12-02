#pragma once


class FileManagerCallbackInterface;
class ::filemanager::document;
class FileManagerFileListCallback;
class ::userbase::multiple_document_template;
class SimpleDialogBar;


class CLASS_DECL_ca FileManagerTemplate :
   virtual public ::radix::object
{
public:


   int         m_iTemplate;
   int         m_iNextDocument;

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

   ::userbase::multiple_document_template * m_pdoctemplateMain;
   ::userbase::multiple_document_template * m_pdoctemplate;
   ::userbase::multiple_document_template * m_pdoctemplateChild;
   ::userbase::multiple_document_template * m_pdoctemplateChildList;

   SimpleDialogBar *    m_pdialogbar;


   ::filemanager::document * open(FileManagerCallbackInterface * pinterface, ::ax::create_context * pwndParent = NULL, ::fs::data * pdata = NULL);
   ::filemanager::document * OpenChild(FileManagerCallbackInterface * pinterface, bool bMakeVisible = true, bool bTransparentBackground = false, ::user::interaction * pwndParent = NULL);
   ::filemanager::document * OpenChildList(FileManagerCallbackInterface * pinterface, bool bMakeVisible = true, bool bTransparentBackground = false, ::user::interaction * pwndParent = NULL);

   ::filemanager::document * create_new_document(FileManagerCallbackInterface * pinterface);


   FileManagerTemplate(::ax::application * papp);
   virtual ~FileManagerTemplate();


   virtual void Initialize(::ax::application * papp, int iTemplate, const char * pszMatter);


};


