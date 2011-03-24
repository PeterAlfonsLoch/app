#include "StdAfx.h"


winservice_1_document::winservice_1_document()
{
}

BOOL winservice_1_document::OnNewDocument()
{
	if (!BaseDocument::OnNewDocument())
		return FALSE;

   UpdateAllViews(NULL, 0);

   string str;
   str = "<command>\n";
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
   str += "</command>\n";

	return TRUE;
}

winservice_1_document::~winservice_1_document()
{
}



#ifdef _DEBUG
void winservice_1_document::AssertValid() const
{
	BaseDocument::AssertValid();
}

void winservice_1_document::Dump(CDumpContext& dc) const
{
	BaseDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// winservice_1_document serialization

/*
void winservice_1_document::Serialize(CArchive& ar)
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

void winservice_1_document::data_on_after_change(gen::signal_object * pobj)
{
}

BOOL winservice_1_document::OnOpenDocument(LPCTSTR lpszPathName)
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



