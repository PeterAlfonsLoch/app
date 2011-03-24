// AlbumDoc.cpp : implementation file
//

#include "stdafx.h"
#include "definitionland_document.h"






#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// definitionland_document

IMPLEMENT_DYNCREATE(definitionland_document, Document)

definitionland_document::definitionland_document()
{
}

BOOL definitionland_document::OnNewDocument()
{
	if (!Document::OnNewDocument())
		return FALSE;

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);



   UpdateAllViews(NULL, 0);

   string str;
   str = "<definitionland>\n";
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
   str += "</definitionland>\n";

	return TRUE;
}

definitionland_document::~definitionland_document()
{
}


BEGIN_MESSAGE_MAP(definitionland_document, Document)
	//{{AFX_MSG_MAP(definitionland_document)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// definitionland_document diagnostics

#ifdef _DEBUG
void definitionland_document::AssertValid() const
{
	Document::AssertValid();
}

void definitionland_document::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// definitionland_document serialization

void definitionland_document::Serialize(CArchive& ar)
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

void definitionland_document::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
}

BOOL definitionland_document::OnOpenDocument(LPCTSTR lpszPathName)
{
   string str = ca2::app(get_app()).file().as_string(lpszPathName);
   if(str.is_empty())
   {
      ca36::app(get_app()).sync_load_url(str, lpszPathName, ca2::app(get_app()).user().get_user());
   }
//  m_document.load(str);
   UpdateAllViews(NULL, 123);
   return TRUE;
}



