#include "framework.h"


namespace filemanager
{


   preview::preview(sp(::aura::application) papp) :
      element(papp)
   {

   }

   preview::~preview()
   {
   }

   void preview::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::impact::install_message_handling(pdispatch);
   }


   void preview::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {
      ::filemanager::impact::on_update(pSender, lHint, phint);
      if (phint != NULL)
      {
         if (base_class < update_hint > ::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (puh->is_type_of(update_hint::TypeInitialize))
            {

               /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                           AddClient(this);
                           SetDataInterface(&m_datainterface);
                           AddClient(&m_datainterface);
                           string str;
                           str.Format("file_list(%d,%d)", get_filemanager_data()->m_iTemplate, get_filemanager_data()->m_iDocument);
                           if(get_filemanager_data()->m_bTransparentBackground)
                           {
                           ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
                           }
                           DISetSection(str);
                           _001UpdateColumns();*/
            }
            else if (puh->is_type_of(update_hint::TypeFilter))
            {
               /*if(puh->m_wstrFilter.is_empty())
               {
               FilterClose();
               }
               else
               {
               FilterBegin();
               Filter1(puh->m_wstrFilter);
               FilterApply();
               }*/
            }
         }
         else if (base_class < form_update_hint > ::bases(phint))
         {
         }

      }
   }



   void preview::_001OnDraw(::draw2d::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->FillSolidRect(rectClient, RGB(200, 200, 190));


      if (m_iCurFile < 0)
      {
      }
      else if (m_iCurFile == 0 && get_filemanager_manager()->m_straPath.get_size() == 0)
      {
         pdc->TextOut(10, 10, "No files in this directory");
      }
      else if(m_iCurFile < get_filemanager_manager()->m_straPath.get_size())
      {
         pdc->TextOut(10,10,get_filemanager_manager()->m_straTitle[m_iCurFile]);
      }

   }



} // namespace filemanager




