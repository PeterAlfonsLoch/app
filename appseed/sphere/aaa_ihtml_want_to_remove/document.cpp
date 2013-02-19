// AlbumDoc.cpp : implementation file
//

#include "stdafx.h"
#include "document.h"






#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace ihtml
{

/////////////////////////////////////////////////////////////////////////////
// document

IMPLEMENT_DYNCREATE(document, Document)



document::document()
{
}

BOOL document::OnNewDocument()
{
   VmsDataClientInterface::Initialize();

	if (!Document::OnNewDocument())
		return FALSE;

   string str;
   VmsDataGet(VMSDATAKEY(LastOpenedFile), 0, 0, str);

   if(str.GetLength() > 0)
   {
      return OnOpenDocument(str);
   }



   UpdateAllViews(NULL, 0);

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
   //m_document.load(str);

	return TRUE;
}

document::~document()
{
}


BEGIN_MESSAGE_MAP(document, Document)
	//{{AFX_MSG_MAP(document)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// document diagnostics

#ifdef _DEBUG
void document::AssertValid() const
{
	Document::AssertValid();
}

void document::Dump(CDumpContext& dc) const
{
	Document::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// document serialization

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

void document::VmsDataOnAfterChange(const VmsDataKeyInterface & key, int iLine, int iColumn, VmsDataUpdateHint * puh)
{
}

BOOL document::OnOpenDocument(LPCTSTR lpszPathName)
{
   string strPathName(lpszPathName);
   if(strPathName.Mid(3) == "wb:")
      return FALSE;
   string str = ca2::app(get_app()).file().as_string(lpszPathName);
   if(str.is_empty())
   {
      //ca36::app(get_app()).sync_load_url(str, lpszPathName, ca2::app(get_app()).user().get_user(), m_pcookies);
   }
/*   SetPathName(lpszPathName);
   m_document.m_strPathName = lpszPathName;
   m_document.load(str);
   m_document.m_papp = get_app();
   html_view_update_hint uh;
   uh.m_etype = html_view_update_hint::type_document_complete;
   uh.m_strUrl = lpszPathName;
   UpdateAllViews(NULL, 0, &uh);
   VmsDataSet(VMSDATAKEY(LastOpenedFile), 0, 0, lpszPathName);*/
   return TRUE;
}



document * document::get_document()
{
   return this;
}

bool document::_001OnUpdateCmdUi(CCmdUI * pcmdui)
{
   CommandIdSpace idspace;
   gen::app * papp = gen::get_app(get_app());
   if(papp->GetResourceId(idspace, "viewindefaultbrowser"))
   {
      pcmdui->Enable();
      return true;
   }
   return false;
}
 
bool document::_001OnCommand(UINT uiId)
{
   CommandIdSpace idspace;
   gen::app * papp = gen::get_app(get_app());
   if(papp->GetResourceId(idspace, "viewindefaultbrowser") == uiId)
   {
      string_to_string_map strmap;
      ca36::app(get_app()).message_box("html_reader\\going_to_open_in_default_browser.xml", strmap);
      ::ShellExecute(NULL, "open", GetPathName(), NULL, ca2::app(get_app()).dir().name(GetPathName()), SW_SHOWNORMAL);
      return true;
   }
   return false;
}


bool document::open_document(const char * pszPath)
{
   return OnOpenDocument(pszPath);
}

bergedge_application * document::get_app()
{
   return Document::get_app();
}

} // namespace ihtml