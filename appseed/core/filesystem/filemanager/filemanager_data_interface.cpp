#include "framework.h"


namespace filemanager
{


   data_interface::data_interface()
   {
      m_pfilemanagerinterface = NULL;
   }

   data_interface::~data_interface()
   {
   }

   ::fs::item & data_interface::GetFileManagerItem()
   {
      return GetFileManager()->get_item();
   }

   sp(manager) data_interface::GetFileManager()
   {
      return m_pfilemanagerinterface;
   }

   sp(document) data_interface::GetFileManagerDoc()
   {
      return  (m_pfilemanagerinterface);
   }

   void data_interface::on_update(sp(::user::view) psender, LPARAM lhint, object * phint)
   {
      UNREFERENCED_PARAMETER(psender);
      UNREFERENCED_PARAMETER(lhint);
      if (phint != NULL)
      {
         if (base < update_hint > ::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (puh->is_type_of(update_hint::TypeCreateViews)
               || puh->is_type_of(update_hint::TypeInitialize))
            {
               if (m_pfilemanagerinterface == NULL
                  && (puh->m_pview == NULL ||
                  puh->m_pview == (this)))
               {
                  m_pfilemanagerinterface = puh->m_pmanager;
               }
            }
         }
      }
   }




} // namespace filemanager




