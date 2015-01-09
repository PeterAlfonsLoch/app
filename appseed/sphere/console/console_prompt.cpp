#include "framework.h"


namespace console
{


   prompt::prompt(::aura::application * papp) :
      element(papp)
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

      m_pdoctemplate->open_document_file(NULL,false);

   }


   prompt_impact & prompt::impact(bool bShow)
   {

      prompt_impact & i = *m_pdoctemplate->get_document()->get_type_view < prompt_impact >();

      if(bShow)
      {
         
         i->GetTopLevel()->WfiRestore();

      }
         
      return i;

   }


} // namespace console



















