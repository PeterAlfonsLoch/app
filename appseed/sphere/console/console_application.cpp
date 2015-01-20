#include "framework.h"


namespace console
{


   application::application()
   {
   }

   application::~application()
   {
   }


   bool application::initialize_instance()
   {

      System.factory().creatable_small < console::prompt_document >();
      System.factory().creatable_small < console::prompt_frame >();
      System.factory().creatable_small < console::prompt_impact >();

      if(!::asphere::application::initialize_instance())
         return false;


      m_spprompt = canew(prompt(this));

      return true;

   }

   void application::pre_translate_message(::signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase->m_uiMessage == WM_APP + 3243)
      {
         event & e = *(event *)(LPARAM) pobj->m_lparam;
         bool bShow = pobj->m_wparam & 1;
         bool bCreateMini = pobj->m_wparam & 2;

         bool bCreate = false;
         if(m_spprompt->m_pdoctemplate->get_document() == NULL)
         {

            bCreate = true;
            m_spprompt->m_pdoctemplate->open_document_file(NULL,false);

         }
         prompt_impact & i = *m_spprompt->m_pdoctemplate->get_document()->get_typed_view < prompt_impact >();

         if(bShow)
         {

            if(bCreate && bCreateMini)
            {

               i.GetTypedParent < prompt_frame >()->show_mini();
            }
            else
            {
               i.GetTopLevel()->WfiRestore();

            }

         }

         e.SetEvent();
         pbase->m_bRet = true;
         return;

      }

      return ::userstack::application::pre_translate_message(pobj);

   }
   


} // namespace userstack



