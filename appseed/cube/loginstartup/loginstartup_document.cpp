#include "StdAfx.h"
#include "loginstartup_document.h"

loginstartup_document::loginstartup_document(::ca::application * papp) :
   ::ca::ca(papp)
{
}

BOOL loginstartup_document::OnNewDocument()
{
	if (!BaseDocument::OnNewDocument())
		return FALSE;

   UpdateAllViews(NULL, 0);

   string str;
   str = "<loginstartup>\n";
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
   str += "</loginstartup>\n";

	return TRUE;
}

loginstartup_document::~loginstartup_document()
{
}



#ifdef _DEBUG
void loginstartup_document::AssertValid() const
{
	BaseDocument::AssertValid();
}

void loginstartup_document::Dump(CDumpContext & dumpcontext) const
{
	BaseDocument::Dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// loginstartup_document serialization

/*
void loginstartup_document::Serialize(CArchive& ar)
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

void loginstartup_document::data_on_after_change(gen::signal_object * pobj)
{
}

BOOL loginstartup_document::on_open_document(const char * lpszPathName)
{
   string str = Application.file().as_string(lpszPathName);
   if(str.is_empty())
   {
      Application.sync_load_url(str, lpszPathName, Application.user().get_user());
   }
//  m_document.load(str);
   UpdateAllViews(NULL, 123);
   return TRUE;
}



