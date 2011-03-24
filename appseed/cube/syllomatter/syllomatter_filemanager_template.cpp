#include "StdAfx.h"

#include "filemanager/FileManagerTabView.h"
#include "filemanager/FileManagerView.h"
#include "filemanager/SimpleFileListView.h"


namespace syllomatter
{

   filemanager_template::filemanager_template(::ca::application * papp) :
      ca(papp),
      FileManagerTemplate(papp)
   {
   }

   filemanager_template::~filemanager_template()
   {
   }


void filemanager_template::Initialize(::ca::application * papp, int iTemplate, const char * pszMatter)
{
   m_iTemplate       = iTemplate;
   m_pdoctemplateMain = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(filemanager_document),
      &typeid(filemanager_frame),       // main SDI frame ::ca::window
      &typeid(FileManagerTabView));

   m_pdoctemplate = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(filemanager_document),
      &typeid(filemanager_frame),
      &typeid(FileManagerAView));

   m_pdoctemplateChild = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(filemanager_document),
      &typeid(filemanager_frame),
      &typeid(FileManagerAView));

   m_pdoctemplateChildList = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      &typeid(filemanager_document),
      &typeid(filemanager_frame),
      &typeid(filemanager::SimpleFileListView));
}


}//  namespace syllomatter