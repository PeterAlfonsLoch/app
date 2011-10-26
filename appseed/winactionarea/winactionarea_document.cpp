#include "StdAfx.h"

namespace winactionarea
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp)
   {
   }

   BOOL document::on_new_document()
   {
	   if (!::userbase::document::on_new_document())
		   return FALSE;


      update_all_views(NULL, 0);

      string str;
      str = "<winactionarea>\n";
      str += "<head>\n";
      str += "</head>\n";
      str += "<body>\n";
      // tag fixer tabjs!!
      str += "<span>Curitiba, 10 de abril de 2008</span>\n";
      str += "<h1>Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>";
      str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
      str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
      str += "<br />";
      str += "<span>Você conhece o ca2?</span>";
      str += "<br />";
      str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
      str += "<br />";
      str += "<input type=\"text\" />";
      str += "</body>\n";
      str += "</winactionarea>\n";

	   return TRUE;
   }

   document::~document()
   {
   }


    // BEGIN_MESSAGE_MAP(document, ::userbase::document)
	   //{{AFX_MSG_MAP(document)
		   // NOTE - the ClassWizard will add and remove mapping macros here.
	   //}}AFX_MSG_MAP
    // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // document diagnostics

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

   /*
   void document::Serialize(CArchive& ar)
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

   bool document::on_open_document(var varFile)
   {
      string str = Application.file().as_string(varFile);
   //  m_document.load(str);
      update_all_views(NULL, 123);
      return TRUE;
   }

} // namespace winactionarea