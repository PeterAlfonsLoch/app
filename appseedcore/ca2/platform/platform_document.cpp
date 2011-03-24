#include "StdAfx.h"
#include "document.h"

namespace platform
{

   document::document(::ca::application * papp) :
      ca(papp),
      data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      html_document(papp),
      form_document(papp)
   {
      
      m_pbergedgedocument = NULL;

   }

   BOOL document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

      update_all_views(NULL, 0);

      string str;
      str = "<platform>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 10 de abril de 2008</span>\n";
      str += unitext("<h1>Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>");
      str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
      str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
      str += "<br />";
      str += unitext("<span>Você conhece o ca2?</span>");
      str += "<br />";
      str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
      str += "<br />";
      str += "<input type=\"text\" />";
      str += "</body>\n";
      str += "</platform>\n";

      return TRUE;
   }

   document::~document()
   {
   }



   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*void document::Serialize(CArchive& ar)
   {
      if (ar.IsStoring())
      {
         // TODO: add storing code here
      }
      else
      {
         // TODO: add loading code here
      }
   }
   */

   void document::data_on_after_change(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   view * document::get_platform_view()
   {
      return get_typed_view < view > ();
   }


   frame * document::get_platform_frame()
   {
      ::view * pview = get_platform_view();
      if(pview == NULL)
         return NULL;
      frame * pplatformframe = pview->GetTypedParent < frame >();
      return pplatformframe;
   }


   ::bergedge::bergedge * document::get_bergedge()
   {
      return m_pbergedgedocument->get_bergedge();
   }


} // namespace platform