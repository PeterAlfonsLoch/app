#include "StdAfx.h"
#include "HtmlEditView.h"
#include "HtmlEditDoc.h"
#include "document.h"

//   // BEGIN_MESSAGE_MAP(devedgeHtmlEditView, html_view)
   //{{AFX_MSG_MAP(devedgeHtmlEditView)
/*
   ON_WM_DESTROY()
   ON_WM_SIZE()
   ON_WM_PAINT()
   ON_WM_CREATE()
   ON_WM_CONTEXTMENU()
   ON_WM_SETCURSOR()
   ON_WM_ERASEBKGND()
   //}}AFX_MSG_MAP
   // Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
   ON_MESSAGE(WM_APP + 119, OnWavePlayerEvent)
   ON_COMMAND(ID_FILE_PRINT, html_view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)
   */
// // END_MESSAGE_MAP()


devedgeHtmlEditView::devedgeHtmlEditView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp), 
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::user::form(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_view(papp)
{
   m_pkeyboardfocus = NULL;
   m_pelementMouseDown = NULL;
}

devedgeHtmlEditView::~devedgeHtmlEditView()
{
}

void devedgeHtmlEditView::install_message_handling(::user::win::message::dispatch * pinterface)
{
   html_view::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &devedgeHtmlEditView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &devedgeHtmlEditView::_001OnSize);
   //IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &devedgeHtmlEditView::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &devedgeHtmlEditView::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &devedgeHtmlEditView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &devedgeHtmlEditView::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &devedgeHtmlEditView::_001OnTimer);
   IGUI_WIN_MSG_LINK(WM_USER + 101     , this, this, &devedgeHtmlEditView::_001OnPost);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &devedgeHtmlEditView::_001OnTabClick);
   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &devedgeHtmlEditView::_001OnWavePlayerEvent);
   IGUI_WIN_MSG_LINK(WM_USER, pinterface, this, &devedgeHtmlEditView::_001OnUser);
 //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &devedgeHtmlEditView::_001OnChar);
   //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &devedgeHtmlEditView::_001OnSysChar);
   //connect_command(ID_FILE_PRINT, html_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, html_view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, html_view::OnFilePrintPreview)

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
      this,
      this,
      &devedgeHtmlEditView::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
      this,
      this,
      &devedgeHtmlEditView::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, 
      this,
      this,
      &devedgeHtmlEditView::_001OnMouseMove);

}

#ifdef _DEBUG
void devedgeHtmlEditView::assert_valid() const
{
   html_view::assert_valid();
}

void devedgeHtmlEditView::dump(dump_context & dumpcontext) const
{
   html_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeHtmlEditView message handlers

// vmpLightView.cpp : implementation of the devedgeHtmlEditView class
//


/////////////////////////////////////////////////////////////////////////////
// devedgeHtmlEditView


BOOL devedgeHtmlEditView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
   cs.style &= ~WS_BORDER;
   return html_view::PreCreateWindow(cs);
}
void devedgeHtmlEditView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   html_view::_001OnInitialUpdate(pobj);


   
}

::user::interaction* devedgeHtmlEditView::get_guie()
{
   return this;
}

void devedgeHtmlEditView::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 1001)
   {
      _001RedrawWindow();
   }
/*xxx   if(phint != NULL)
   {
      if(base < PaneViewUpdateHint >::bases(phint))
      {
         PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) phint;
         if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowKaraoke))
         {
            (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
         }
         else if(puh->is_type_of(PaneViewUpdateHint::TypeOnBeforeShowView))
         {
            devedge::application_interface * papp = dynamic_cast < devedge::application_interface * > (get_app());
            POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
            document * pdoc = (document *) papp->m_ptemplate_devedge->get_document(posDoc);
            if(m_str == pdoc->get_path_name())
            {
//               transform_back();
            }
            else
            {
               m_str = pdoc->get_path_name();
            }
         }
         else if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowView))
         {
            transform();
            Navigate(System.dir().time("html.html"));
         }
      }
   }
*/

   
}

database::user::interaction* devedgeHtmlEditView::BackViewGetWnd()
{
   return this;
}

void devedgeHtmlEditView::_001OnDestroy(gen::signal_object * pobj) 
{
   html_view::_001OnDestroy(pobj);

}



void devedgeHtmlEditView::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
  // SCAST_PTR(::user::win::message::size, psize, pobj)
//   document * pdoc = get_document();
}

void devedgeHtmlEditView::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //CPaintDC spgraphics(this); // device context for painting
   

   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void devedgeHtmlEditView:: _001OnDraw(::ca::graphics * pdc)
{
   html_view::_001OnDraw(pdc);
}

void devedgeHtmlEditView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

   SetTimer(100, 100, NULL);
   
   PostMessage(WM_USER + 101, 100, 1);



   /*document * pdoc = get_document();
   for(int i = 0; i < pdoc->m_elementptraVisible.get_size(); i++)
   {
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
         this,
         pdoc->m_elementptraVisible[i],
         &devedge::Element2D::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
         this,
         pdoc->m_elementptraVisible[i],
         &devedge::Element2D::_001OnLButtonUp);
   }*/

}
void devedgeHtmlEditView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}



void devedgeHtmlEditView::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
}

void devedgeHtmlEditView::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
  // SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
}

void devedgeHtmlEditView::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::command, pcommand, pobj)
}

void devedgeHtmlEditView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}

void devedgeHtmlEditView::_001OnLButtonDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void devedgeHtmlEditView::_001OnLButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void devedgeHtmlEditView::_001OnMouseMove(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

document * devedgeHtmlEditView::get_document() const
{
   return (document *) ::userbase::view::get_document();
}

devedge::Element2D * devedgeHtmlEditView::hit_test(int x, int y)
{
   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
//   document * pdoc = get_document();
   return NULL;
}

void devedgeHtmlEditView::_001OnTimer(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::timer, ptimer, pobj)
   if(ptimer->m_nIDEvent >= 100 
      && ptimer->m_nIDEvent <= 200)
   {
   }
   else if(ptimer->m_nIDEvent == 500 || ptimer->m_nIDEvent == 501 )
   {
      if(ptimer->m_nIDEvent == 500)
      {
         KillTimer(500);
         SetTimer(501, 300, NULL);
      }
      key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   }

}

void devedgeHtmlEditView::_001OnKeyDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)
   m_dwLastKeyWparam = pkey->m_wparam;
   m_dwLastKeyLparam = pkey->m_lparam;
   key_to_char(m_dwLastKeyWparam, m_dwLastKeyLparam);
   SetTimer(500, 500, NULL);
}

void devedgeHtmlEditView::_001OnKeyUp(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
   KillTimer(500);
   KillTimer(501);
}


void devedgeHtmlEditView::_001OnChar(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::key, pkey, pobj)
   if(pkey->m_nChar == 's')
   {
      if(::GetKeyState(VK_CONTROL) & 0x80000000)
      {
         return;
      }
   }
}


void devedgeHtmlEditView::_001OnSysChar(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
}

void devedgeHtmlEditView::pre_translate_message(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_KEYUP)
   {
      PostMessage(WM_USER, MessageUserCheckChange);
      return;
   }
   return html_view::pre_translate_message(pobj);
}

void devedgeHtmlEditView::key_to_char(WPARAM wparam, LPARAM lparam)
{
   UNREFERENCED_PARAMETER(lparam);
   ::user::win::message::key key(get_app());

   if(wparam == VK_LSHIFT || wparam == VK_RSHIFT
      || wparam == VK_LCONTROL || wparam == VK_RCONTROL
      || wparam == VK_LMENU || wparam == VK_RMENU)
   {
      return;
   }

   key.m_nChar = wparam;
   bool bShift = (::GetKeyState(VK_SHIFT) & 0x80000000) != 0;
   if(bShift && isalpha(key.m_nChar))
   {
      key.m_nChar = toupper(key.m_nChar);  
   }
   else
   {
      key.m_nChar = tolower(key.m_nChar);  
   }
   _001OnChar(&key);
}

void devedgeHtmlEditView::_001OnPost(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj)
   if(pbase->m_wparam == 100)
   {
      PostMessage(WM_APP + 80, 101);
   }
   else if (pbase->m_wparam == 101)
   {
   }
}

void devedgeHtmlEditView::transform()
{
   /* xxx
   devedgeApp * papp = dynamic_cast < devedgeApp * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->m_papp);
   POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
   document * pdoc = (document *) papp->m_ptemplate_devedge->get_document(posDoc);

   string strSourcePath = pdoc->get_path_name();
   string strDestPath = System.dir().time("html.html");
   string strSource = Application.file().as_string(strSourcePath);

   string strImgNns = Application.dir().matter("html_edit_nns.png");
   

   string strDest;
   int iStart = 0;
   int iPos = 0;
   int iLastEnd = 0;
   if(strSource.Mid(0, 4) == "<?ss")
   {
      iLastEnd = strSource.find("?>", iPos);
      if(iLastEnd > 0)
      {
         iLastEnd += 2;
         strDest += strSource.Mid(iPos + 4, iLastEnd - iPos - 6);
         iStart = iLastEnd;
      }
   }
   while((iPos = strSource.find("<?ds", iStart)) >= 0)
   {
      if(iPos > iLastEnd)
      {
         strDest += strSource.Mid(iLastEnd, iPos - iLastEnd);
      }
      iLastEnd = strSource.find("?>", iPos);
      if(iLastEnd < 0)
         break;
      iLastEnd += 2;
      m_straScript.add(strSource.Mid(iPos + 4, iLastEnd - iPos - 6));
      string strFormat;
      strFormat.Format("<visual id=\"netnodescript.%d src=\"%s\" />", m_straScript.get_upper_bound(), strImgNns);
      strDest += strFormat;
      iStart = iLastEnd;
   }
   strDest += strSource.Mid(iStart);

   Application.file().put_contents(strDestPath, strDest);
   */
   
}

void devedgeHtmlEditView::_001OnUser(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj)
   if(pbase->m_wparam == MessageUserCheckChange)
   {
   }
}


void devedgeHtmlEditView::transform_back()
{
   
//   string strSourcePath = System.dir().time("html.html");
//   SaveAs(strSourcePath);
 
   string strImgNns = Application.dir().matter("html_edit_nns.png");

   /* xxx
   devedgeApp * papp = dynamic_cast < devedgeApp * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->m_papp);
   POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
   document * pdoc = (document *) papp->m_ptemplate_devedge->get_document(posDoc);
   string strDestPath = pdoc->get_path_name();

   string str;
   GetDocumentHTML(str);

   for(int i = 0; i < m_straScript.get_size(); i++)
   {
      string strFormat;
      strFormat.Format("<visual id=\"netnodescript.%d src=\"%s\" />", m_straScript.get_upper_bound(), strImgNns);
      str.replace(
         strFormat,
         m_straScript[i]);
   }

   Application.file().put_contents(strDestPath, str);

   */
}


