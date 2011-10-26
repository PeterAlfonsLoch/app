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
      ::ca::get_type_info < filemanager_document > (),
      ::ca::get_type_info < filemanager_frame > (),       // main SDI frame ::ca::window
      ::ca::get_type_info < FileManagerTabView > ());

   m_pdoctemplate = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      ::ca::get_type_info < filemanager_document > (),
      ::ca::get_type_info < filemanager_frame > (),
      ::ca::get_type_info < FileManagerAView > ());

   m_pdoctemplateChild = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      ::ca::get_type_info < filemanager_document > (),
      ::ca::get_type_info < filemanager_frame > (),
      ::ca::get_type_info < FileManagerAView > ());

   m_pdoctemplateChildList = new ::userbase::multiple_document_template(
      papp,
      pszMatter,
      ::ca::get_type_info < filemanager_document > (),
      ::ca::get_type_info < filemanager_frame > (),
      ::ca::get_type_info < filemanager::SimpleFileListView > ());
}


}//  namespace syllomatter