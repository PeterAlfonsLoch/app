#include "framework.h"


namespace filemanager
{


   data_interface::data_interface(sp(base_application) papp) :
      element(papp)
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


   void data_interface::on_update(sp(::user::impact) psender, LPARAM lhint, object * phint)
   {
      UNREFERENCED_PARAMETER(psender);
      UNREFERENCED_PARAMETER(lhint);
      if (phint != NULL)
      {
         if (base < ::user::view_update_hint > ::bases(phint))
         {
            sp(::user::view_update_hint) puh = phint;
            if (puh->is_type_of(::user::view_update_hint::hint_create_views))
            {
               if (m_pfilemanagerinterface == NULL
                  && (puh->oprop("data").cast < data_interface > () == NULL ||
                  puh->oprop("data").cast < data_interface >() == (this)))
               {
                  m_pfilemanagerinterface = puh->oprop("manager").cast < manager >();
               }
            }
         }
         else if (base < update_hint > ::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (puh->is_type_of(update_hint::TypeInitialize))
            {
               if (m_pfilemanagerinterface == NULL
                  && (puh->m_pview == NULL ||
                  puh->m_pview == (this)))
               {
                  m_pfilemanagerinterface = puh->m_pmanager;


                  sp(::user::interaction) pui = this;

                  if (pui.is_set())
                  {

                     if (GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
                     {
                        pui->m_etranslucency = ::user::interaction::TranslucencyPresent;
                     }
                     else
                     {
                        pui->m_etranslucency = ::user::interaction::TranslucencyNone;
                     }

                     pui->set_default_background_color(ARGB(255, 255, 255, 255));

                  }


               }
            }
         }
      }
   }




} // namespace filemanager




