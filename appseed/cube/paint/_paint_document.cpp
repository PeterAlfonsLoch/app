#include "StdAfx.h"
#include "paint_document.h"

paint_document::paint_document(::ca::application * papp) :
   ca(papp),
   ::ca::data_container(papp),
   ::document(papp),
   ::userbase::document(papp),
   m_document(papp)
{
}

BOOL paint_document::on_new_document()
{
   if (!::userbase::document::on_new_document())
      return FALSE;

   update_all_views(NULL, 0);

   string str;
   str = "<paint>\n";
   str += "<head>\n";
   str += "</head>\n";
   str += "<body>\n";
   // tag fixer tabjs!!
   str += "<span>Curitiba, 10 de abril de 2008</span>\n";
   str += "<h1>Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!</h1>";
   str += "<h2>Assinado Camilo Sasuke Tsumanuma.</h2>\n";
   str += "<span>htmlapp dedicado ao Carlos Gustavo Cecyn Lundgren!!</span>";
   str += "<br />";
   str += "<span>Voc・conhece o ca2?</span>";
   str += "<br />";
   str += "<span>Se positivo, entre com seu nome abaixo e clique em enviar!</span>";
   str += "<br />";
   str += "<input type=\"text\" />";
   str += "</body>\n";
   str += "</paint>\n";
   m_document.load(str);

   return TRUE;
}

paint_document::~paint_document()
{
}


#ifdef _DEBUG
void paint_document::assert_valid() const
{
   ::userbase::document::assert_valid();
}

void paint_document::dump(dump_context & dumpcontext) const
{
   ::userbase::document::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// paint_document serialization
/*
void paint_document::Serialize(CArchive& ar)
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
void paint_document::data_on_after_change(gen::signal_object * pobj)
{
}

bool paint_document::on_open_document(var varFile)
{
   string str = Application.file().as_string(varFile);
   update_all_views(NULL, 123);
   return TRUE;
}



::paint::document * paint_document::get_document()
{
   return &m_document;
}