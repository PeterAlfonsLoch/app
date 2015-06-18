//#include "framework.h"


namespace console
{


   prompt::prompt(::aura::application * papp) :
      ::object(papp)
   {


      ::user::single_document_template* pdoctemplate;

      pdoctemplate = new ::user::single_document_template(
         get_app(),
         "system/form",
         System.type_info < prompt_document >(),
         System.type_info < prompt_frame >(),
         System.type_info < prompt_impact >());
      
      Application.add_document_template(pdoctemplate);

      m_pdoctemplate = pdoctemplate;

      

   }


   prompt_impact & prompt::impact(bool bShow, bool bCreateMini)
   {

      if(m_pdoctemplate->get_document() == NULL)
      {

         Application.send_thread_message(WM_APP + 3243,(bShow ? 1 : 0) | (bCreateMini ? 2 : 0));

      }

      if(bShow && !m_pdoctemplate->get_document()->get_typed_view < prompt_impact >()->IsWindowVisible())
      {
         if(bCreateMini)
         {

            m_pdoctemplate->get_document()->get_typed_view < prompt_impact >()->GetTypedParent < prompt_frame > ()->show_mini();
         }
         else
         {
            m_pdoctemplate->get_document()->get_typed_view < prompt_impact >()->WfiRestore();

         }

      }

      return *m_pdoctemplate->get_document()->get_typed_view < prompt_impact >();

   }


   int prompt::getch()
   {

      return impact().getch();

   }

   void prompt::ungetch(int c)
   {

      impact().ungetch(c);

   }

} // namespace console



















