#include "StdAfx.h"

namespace devedge
{

   file::file(::ca::application * papp) : 
      ca(papp)
   {   
      m_pdocument = NULL;
   }

   void file::initialize(folder * pfolder, const char * pszPath)
   {
      m_pfolder = pfolder;
      m_strPath = pszPath;
      m_strName = System.file().name_(m_strPath);
   }

   void file::open(::user::interaction * puieParent)
   {
      devedge::application & app = Application;
      m_pdocument = dynamic_cast < document * > 
         (app.devedge::application_interface::m_ptemplate_devedge->open_document_file(m_strPath, true, puieParent));
   }

   void file::close()
   {
      if(m_pdocument != NULL)
      {
         m_pdocument->on_close_document();
      }
   }

} // namespace devedge