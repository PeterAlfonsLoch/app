#include "framework.h"

FileManagerViewInterface::FileManagerViewInterface()
{
   m_pfilemanagerinterface = ::null();
}

FileManagerViewInterface::~FileManagerViewInterface()
{
}

::fs::item & FileManagerViewInterface::GetFileManagerItem()
{
   return GetFileManager()->get_item();
}

sp(FileManagerInterface) FileManagerViewInterface::GetFileManager()
{ 
   return m_pfilemanagerinterface;
}

sp(::filemanager::document) FileManagerViewInterface::GetFileManagerDoc()
{ 
   return  (m_pfilemanagerinterface);
}

void FileManagerViewInterface::on_update(sp(::view) psender, LPARAM lhint, ::ca::object * phint)
{ 
   UNREFERENCED_PARAMETER(psender);
   UNREFERENCED_PARAMETER(lhint);
   if(phint != ::null())
   {
      if(base < FileManagerViewUpdateHint > :: bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->is_type_of(FileManagerViewUpdateHint::TypeCreateViews)
         || puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
         {
            if(m_pfilemanagerinterface == ::null()
               && (puh->m_pview == ::null() ||
                   puh->m_pview == (this)))
            {
               m_pfilemanagerinterface = puh->m_pmanager;
            }
         }
      }
   }
}



