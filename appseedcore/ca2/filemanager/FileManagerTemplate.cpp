#include "StdAfx.h"
#include "FileManagerFrame.h"
#include "FileManagerViewUpdateHint.h"
#include "SimpleFileListView.h"


FileManagerTemplate::FileManagerTemplate(::ca::application * papp) :
   ca(papp)
{
   m_iTemplate = -1;

   m_pdialogbar = NULL;
   m_pfilelistcallback = NULL;

   //m_uiLevelUp       = 0xffffffff;
//   m_uiMenuBar       = 0xffffffff;
   m_iNextDocument   = 0;

   m_pdoctemplate = NULL;
   m_pdoctemplateChild = NULL;
   m_pdoctemplateChildList = NULL;
}

FileManagerTemplate::~FileManagerTemplate()
{
   if(m_pdoctemplate != NULL)
   {
      delete m_pdoctemplate;
   }
}

::filemanager::document * FileManagerTemplate::open(
   FileManagerCallbackInterface * pcallback,
   bool bMakeVisible,
   bool bTransparentBackground,
   ::user::interaction * pwndParent)
{
   UNREFERENCED_PARAMETER(pcallback);
   UNREFERENCED_PARAMETER(bTransparentBackground);
   ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pdoctemplateMain->open_document_file(NULL, FALSE, pwndParent));
   if(pdoc != NULL)
   {
      pdoc->get_filemanager_data()->m_pcallback = &System;
      pdoc->get_filemanager_data()->m_pmanager  = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain  = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate = this;
      pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;
      pdoc->get_filemanager_data()->m_bTransparentBackground = bTransparentBackground;
      string strId;
      strId.Format("filemanager(%d)", pdoc->get_filemanager_data()->m_iDocument);
      pdoc->get_filemanager_data()->m_strDISection = m_strDISection + "." + strId;
      pdoc->get_filemanager_data()->m_bFileSize = true;
      pdoc->Initialize(bMakeVisible);
      return pdoc;
   }
   return NULL;
}

::filemanager::document * FileManagerTemplate::create_new_document(
   FileManagerCallbackInterface * pcallback)
{
   ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pdoctemplate->create_new_document());
   if(pdoc != NULL)
   {

      pdoc->get_filemanager_data()->m_pcallback       = pcallback;
      pdoc->get_filemanager_data()->m_pfilemanager    = pcallback;
      pdoc->get_filemanager_data()->m_pmanager        = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain    = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate       = this;
      pdoc->get_filemanager_data()->m_iTemplate       = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument       = m_iNextDocument++;
      
      return pdoc;
   }
   return NULL;
}


::filemanager::document * FileManagerTemplate::OpenChild(
   FileManagerCallbackInterface * pcallback,
   bool bMakeVisible,
   bool bTransparentBackground,
   ::user::interaction * pwndParent,
   ::fs::data * pdata)
{
   ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pdoctemplateChild->open_document_file(NULL, FALSE, pwndParent));
   if(pdoc != NULL)
   {
      if(pdata == NULL)
      {
         pdoc->m_pfsdata = System.fs();
      }
      else
      {
         pdoc->m_pfsdata = pdata;
      }
      pdoc->get_filemanager_data()->m_pcallback                = pcallback;
      pdoc->get_filemanager_data()->m_pfilemanager             = pcallback;
      pdoc->get_filemanager_data()->m_pmanager                 = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain             = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate                = this;
      pdoc->get_filemanager_data()->m_iTemplate                = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument                = m_iNextDocument++;
      pdoc->get_filemanager_data()->m_bTransparentBackground   = bTransparentBackground;
      string strId;
      strId.Format("filemanager(%d)", pdoc->get_filemanager_data()->m_iDocument);
      pdoc->get_filemanager_data()->m_strDISection             = m_strDISection + "." + strId;
      pdoc->Initialize(bMakeVisible);
      return pdoc;
   }
   return NULL;
}


::filemanager::document * FileManagerTemplate::OpenChildList(
   FileManagerCallbackInterface * pcallback,
   bool bMakeVisible,
   bool bTransparentBackground,
   ::user::interaction * pwndParent)
{
   UNREFERENCED_PARAMETER(bMakeVisible);
   ::filemanager::document * pdoc = dynamic_cast < ::filemanager::document * > (m_pdoctemplateChildList->open_document_file(NULL, FALSE, pwndParent));
   if(pdoc != NULL)
   {
//      pdoc->get_filemanager_data()->m_uiMenuBar = m_uiMenuBar;
//      pdoc->get_filemanager_data()->m_uiToolBar = m_uiToolBar;

      pdoc->get_filemanager_data()->m_pcallback = pcallback;
      pdoc->get_filemanager_data()->m_pfilemanager = pcallback;
      pdoc->get_filemanager_data()->m_pmanager  = pdoc;
      pdoc->get_filemanager_data()->m_pmanagerMain  = pdoc;
      pdoc->get_filemanager_data()->m_ptemplate = this;
      pdoc->get_filemanager_data()->m_iTemplate = m_iTemplate;
      pdoc->get_filemanager_data()->m_iDocument = m_iNextDocument++;
      pdoc->get_filemanager_data()->m_bTransparentBackground = bTransparentBackground;

      //pdoc->CreateViews();

      return pdoc;
   }
   return NULL;
}

void FileManagerTemplate::Initialize(::ca::application * papp, int iTemplate, const char * pszMatter)
{
   m_iTemplate       = iTemplate;
   m_pdoctemplateMain = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(::filemanager::document),
      &typeid(FileManagerMainFrame),       // main SDI frame ::ca::window
      &typeid(FileManagerTabView));

   m_pdoctemplate = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(::filemanager::document),
      &typeid(FileManagerFrame),
      &typeid(FileManagerAView));

   m_pdoctemplateChild = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(::filemanager::document),
      &typeid(FileManagerChildFrame),
      &typeid(FileManagerAView));

   m_pdoctemplateChildList = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(::filemanager::document),
      &typeid(FileManagerChildFrame),
      &typeid(filemanager::SimpleFileListView));
}