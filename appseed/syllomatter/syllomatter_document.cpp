// AlbumDoc.cpp : implementation file
//

#include "stdafx.h"
#include "syllomatter_document.h"






#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// syllomatter_document

IMPLEMENT_DYNCREATE(syllomatter_document, Document)

syllomatter_document::syllomatter_document()
{
}

BOOL syllomatter_document::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);



   UpdateAllViews(NULL, 0);

   string str;
   str = "<syllomatter>\n";
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
   str += "</syllomatter>\n";

	return TRUE;
}

syllomatter_document::~syllomatter_document()
{
}


BEGIN_MESSAGE_MAP(syllomatter_document, Document)
	//{{AFX_MSG_MAP(syllomatter_document)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// syllomatter_document diagnostics

#ifdef _DEBUG
void syllomatter_document::AssertValid() const
{
	Document::AssertValid();
}

void syllomatter_document::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// syllomatter_document serialization

void syllomatter_document::Serialize(CArchive& ar)
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

void syllomatter_document::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
}

BOOL syllomatter_document::OnOpenDocument(LPCTSTR lpszPathName)
{
   string str = ca2::app(get_app()).file().as_string(lpszPathName);
   if(str.is_empty())
   {
      ca36::app(get_app()).sync_load_url(str, lpszPathName);
   }
   UpdateAllViews(NULL, 123);
   return TRUE;
}



