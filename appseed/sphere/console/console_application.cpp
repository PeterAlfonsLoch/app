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

      IGUI_WIN_MSG_LINK(WM_APP + 3243,m_pthreadimpl,this,&application::_001OnImpact);

      System.factory().creatable_small < console::prompt_document >();
      System.factory().creatable_small < console::prompt_frame >();
      System.factory().creatable_small < console::prompt_impact >();

      if(!::asphere::application::initialize_instance())
         return false;


      m_spprompt = canew(prompt(this));

      console_prompt().impact(false);



      return true;

   }


   void application::pre_translate_message(::signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase != NULL)
      {
         if(pbase->m_uiMessage == WM_KEYDOWN)
         {

            SCAST_PTR(::message::key,pkey,pobj);

            if(pkey->m_ekey == ::user::key_semicolon2 && Session.is_key_pressed(::user::key_shift))
            {

               console_prompt().impact().keyboard_set_focus();

            }
         }
          
      }

      return ::userstack::application::pre_translate_message(pobj);

   }

   
   void application::_001OnImpact(::signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);


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

      pbase->m_bRet = true;

   }


} // namespace userstack






















