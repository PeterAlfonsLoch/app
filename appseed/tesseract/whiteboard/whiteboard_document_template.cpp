#include "StdAfx.h"

namespace whiteboard
{

   document_template::document_template(::ca::application * papp) :
      ca(papp),
      ::MultiFrameViewSingleDocTemplate(
         papp,
         "whiteboard/frame",
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < whiteboard::main_frame > (),       // default main SDI frame ::ca::window
         ::ca::get_type_info < view > () // default ::view
         ), 
      ::document_template(papp, "whiteboard/frame", 
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < whiteboard::main_frame > (),       // default main SDI frame ::ca::window
         ::ca::get_type_info < view > ()), // default ::view
      ::userbase::document_template(papp, "whiteboard/frame",
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < whiteboard::main_frame > (),       // default main SDI frame ::ca::window
         ::ca::get_type_info < view > ()), // default ::view
      ::userbase::single_document_template(papp, "whiteboard/frame",
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < whiteboard::main_frame > (),       // default main SDI frame ::ca::window
         ::ca::get_type_info < view > ()), // default ::view
      ::single_document_template(papp, "whiteboard/frame",
         ::ca::get_type_info < document > (),
         ::ca::get_type_info < whiteboard::main_frame > (),       // default main SDI frame ::ca::window
         ::ca::get_type_info < view > ()) // default ::view
   {
   }

   document_template::~document_template()
   {

   }

   html_view * document_template::CreateHtmlWnd(bool bMakeVisible)
   {
      html_frame * pframe = 
         (html_frame *) 
            CreateFrameViewPair(
               "html/frame",
               ::ca::get_type_info < html_frame > (),
               ::ca::get_type_info < html_view > (),
               bMakeVisible);

      html_view * phtml = 
         dynamic_cast < html_view * > (
            pframe->GetActiveView());

      return phtml;
   }

} // namespace whiteboard
