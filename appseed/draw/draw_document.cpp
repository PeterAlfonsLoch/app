// AlbumDoc.cpp : implementation file
//

#include "stdafx.h"
#include "html_document.h"






#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// html_document

IMPLEMENT_DYNCREATE(html_document, Document)

html_document::html_document()
{
}

BOOL html_document::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);



   UpdateAllViews(NULL, 0);

   string str;
   str = "<html>\n";
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
   str += "</html>\n";
   m_document.load(str);

	return TRUE;
}

html_document::~html_document()
{
}


BEGIN_MESSAGE_MAP(html_document, Document)
	//{{AFX_MSG_MAP(html_document)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// html_document diagnostics

#ifdef _DEBUG
void html_document::AssertValid() const
{
	Document::AssertValid();
}

void html_document::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// html_document serialization

void html_document::Serialize(CArchive& ar)
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

void html_document::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
}

BOOL html_document::OnOpenDocument(LPCTSTR lpszPathName)
{
   string str = ca2::app(get_app()).file().as_string(lpszPathName);
   if(str.is_empty())
   {
      ca36::app(get_app()).sync_load_url(str, lpszPathName);
   }
   m_document.load(str);
   UpdateAllViews(NULL, 123);
   return TRUE;
}



::html::document * html_document::get_document()
{
   return &m_document;
}