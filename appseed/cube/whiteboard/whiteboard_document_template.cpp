#include "StdAfx.h"

namespace whiteboard
{

   document_template::document_template(::ca::application * papp) :
      ca(papp),
      ::MultiFrameViewSingleDocTemplate(
         papp,
         "whiteboard/frame",
         &typeid(document),
         &typeid(whiteboard::main_frame),       // default main SDI frame ::ca::window
         &typeid(view) // default ::view
         ), 
      ::document_template(papp, "whiteboard/frame", &typeid(document),
         &typeid(whiteboard::main_frame),       // default main SDI frame ::ca::window
         &typeid(view)),
      ::userbase::document_template(papp, "whiteboard/frame", &typeid(document),
         &typeid(whiteboard::main_frame),       // default main SDI frame ::ca::window
         &typeid(view)),
      ::userbase::single_document_template(papp, "whiteboard/frame", &typeid(document),
         &typeid(whiteboard::main_frame),       // default main SDI frame ::ca::window
         &typeid(view)),
      ::single_document_template(papp, "whiteboard/frame", &typeid(document),
         &typeid(whiteboard::main_frame),       // default main SDI frame ::ca::window
         &typeid(view))
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
               &typeid(html_frame),
               &typeid(html_view),
               bMakeVisible);

      html_view * phtml = 
         dynamic_cast < html_view * > (
            pframe->GetActiveView());

      return phtml;
   }

} // namespace whiteboard
