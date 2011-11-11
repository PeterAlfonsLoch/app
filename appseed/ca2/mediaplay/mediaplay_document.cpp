#include "StdAfx.h"

namespace mediaplay
{

   document::document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
      m_pdata     = NULL;
      m_pview     = NULL;
      m_bWriting  = false;
   }

   document::~document()
   {

   }

   data * document::get_data()
   {
      return m_pdata;
   }

   view * document::GetMediaView()
   {
      return m_pview;
   }

   bool document::on_open_document(var varFile) 
   {
      keeper < bool > keepWriting(&m_bWriting, true, false, true);

      System.wait_twf();

      delete_contents();
      
      keepWriting.Keep();

      mediaplay::data * pdata =  new mediaplay::data(this);
      pdata->m_pdocument = this;

      keepWriting.Keep();

      ::mediaplay::view_update_hint uh;
      m_pdata = pdata;
      uh.set_type(::mediaplay::view_update_hint::TypeBeforeOpenDocument);
      update_all_views(NULL, 0, &uh);

      keepWriting.Keep();

      if(!pdata->on_open_document(varFile))
      {
         return FALSE;
      }

      keepWriting.Keep();

      uh.set_type(::mediaplay::view_update_hint::TypeAfterOpenDocument);
      update_all_views(NULL, 0, &uh);

      return TRUE;

   }

   void document::delete_contents()
   {
    
      ::mediaplay::view_update_hint uh;
      uh.set_type(::mediaplay::view_update_hint::TypeDeleteContents);
      update_all_views(NULL, 0, &uh);

      ::mediaplay::data * pdataOld = m_pdata;
      if(pdataOld != NULL)
      {
         m_pdata = NULL;
         try
         {
            pdataOld->delete_contents();
         }
         catch(...)
         {
         }
         delete pdataOld;
         pdataOld = NULL;
      }

   }

} // namespace mediaplay

