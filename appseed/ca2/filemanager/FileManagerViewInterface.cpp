#include "framework.h"

FileManagerViewInterface::FileManagerViewInterface()
{
   m_pfilemanagerinterface = NULL;
}

FileManagerViewInterface::~FileManagerViewInterface()
{
}

::fs::item & FileManagerViewInterface::GetFileManagerItem()
{
   return GetFileManager()->get_item();
}

FileManagerInterface * FileManagerViewInterface::GetFileManager()
{ 
   return m_pfilemanagerinterface;
}

::filemanager::document * FileManagerViewInterface::GetFileManagerDoc()
{ 
   return dynamic_cast < ::filemanager::document * > (m_pfilemanagerinterface);
}

void FileManagerViewInterface::on_update(::view * psender, LPARAM lhint, ::radix::object * phint)
{ 
   UNREFERENCED_PARAMETER(psender);
   UNREFERENCED_PARAMETER(lhint);
   if(phint != NULL)
   {
      if(base < FileManagerViewUpdateHint > :: bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews)
         || puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
         {
            if(m_pfilemanagerinterface == NULL
               && (puh->m_pview == NULL ||
                   puh->m_pview == dynamic_cast < ::userbase::view * > (this)))
            {
               m_pfilemanagerinterface = puh->m_pmanager;
            }
         }
      }
   }
}



