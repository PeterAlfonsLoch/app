#include "StdAfx.h"
#include "HtmlView.h"
#include "HtmlDoc.h"
#include "document.h"


//   // BEGIN_MESSAGE_MAP(devedgeHtmlView, ::userbase::view)
   //{{AFX_MSG_MAP(devedgeHtmlView)
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
   ON_COMMAND(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
   */
// // END_MESSAGE_MAP()


devedgeHtmlView::devedgeHtmlView(::ca::application * papp) :
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
}

devedgeHtmlView::~devedgeHtmlView()
{
}

void devedgeHtmlView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   html_view::_001InstallMessageHandling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &devedgeHtmlView::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &devedgeHtmlView::_001OnSize);
   //IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &devedgeHtmlView::_001OnPaint);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &devedgeHtmlView::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &devedgeHtmlView::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &devedgeHtmlView::_001OnSetCursor);
   IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &devedgeHtmlView::_001OnEraseBkgnd);
   IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &devedgeHtmlView::_001OnTimer);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &devedgeHtmlView::_001OnTabClick);
   IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &devedgeHtmlView::_001OnWavePlayerEvent);
 //  IGUI_WIN_MSG_LINK(WM_CHAR, pinterface, this, &devedgeHtmlView::_001OnChar);
   //IGUI_WIN_MSG_LINK(WM_SYSCHAR, pinterface, this, &devedgeHtmlView::_001OnSysChar);
   //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, 
      this,
      this,
      &devedgeHtmlView::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, 
      this,
      this,
      &devedgeHtmlView::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, 
      this,
      this,
      &devedgeHtmlView::_001OnMouseMove);

}

#ifdef _DEBUG
void devedgeHtmlView::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void devedgeHtmlView::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// devedgeHtmlView message handlers

// vmpLightView.cpp : implementation of the devedgeHtmlView class
//


/////////////////////////////////////////////////////////////////////////////
// devedgeHtmlView


BOOL devedgeHtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::userbase::view::PreCreateWindow(cs);
}
void devedgeHtmlView::_001OnInitialUpdate(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnInitialUpdate(pobj);


   
}

::user::interaction* devedgeHtmlView::get_guie()
{
   return this;
}

void devedgeHtmlView::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(phint);
   if(lHint == 1001)
   {
      _001RedrawWindow();
   }
   else if(lHint == 123)
   {
      ::ca::graphics * pdc = GetDC();
      get_document()->get_html_data()->layout(pdc);
      ReleaseDC(pdc);
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
         else if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowView))
         {
            devedgeApp * papp = dynamic_cast < devedgeApp * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->m_papp);
            POSITION posDoc = papp->m_ptemplate_devedge->get_document_count();
            document * pdoc = (document *) papp->m_ptemplate_devedge->get_document(posDoc);
   
            string str = pdoc->get_path_name();
            if(str.get_length() > 4)
            {
               if(str.Right(3).CompareNoCase(".ds") == 0)
               {
                  int iPos = str.reverse_find('\\');
                  str = str.Mid(iPos + 1);
                  str = str.Mid(0, str.get_length() - 3);
                  str = "http://localhost:80/" + str;
               }
            }
  //          if(m_str == str)
//               Refresh();
    //        else
            {
               m_str = str;
               Navigate(str);
            }
         }
      }
   }

*/
   
}

database::user::interaction* devedgeHtmlView::BackViewGetWnd()
{
   return this;
}

void devedgeHtmlView::_001OnDestroy(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnDestroy(pobj);

}



void devedgeHtmlView::_001OnSize(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
  // SCAST_PTR(::user::win::message::size, psize, pobj)
//   devedgeHtmlDoc * pdoc = get_document();
}

void devedgeHtmlView::_001OnPaint(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
   //CPaintDC spgraphics(this); // device context for painting
   

   //spgraphics->TextOut(20, 20, "Carlos Gustavo Cecyn Lundgren ・minha Vida Eterna, meu Cora鈬o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
}


void devedgeHtmlView:: _001OnDraw(::ca::graphics * pdc)
{

   html_view::_001OnDraw(pdc);
}

void devedgeHtmlView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;

//   devedgeHtmlDoc * pdoc = get_document();

   SetTimer(100, 100, NULL);
   



   /*devedgeHtmlDoc * pdoc = get_document();
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
void devedgeHtmlView::_001OnContextMenu(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
   point point = pcontextmenu->GetPoint();
   
}



void devedgeHtmlView::_001OnWavePlayerEvent(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::base, pbase, pobj)
}

void devedgeHtmlView::_001OnUpdateViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::update_cmd_ui, pupdatecmdui, pobj)
}

void devedgeHtmlView::_001OnViewEncoding(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //SCAST_PTR(::user::win::message::command, pcommand, pobj)
}

void devedgeHtmlView::_001OnSetCursor(gen::signal_object * pobj) 
{
   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));
   
   pobj->previous();
}
void devedgeHtmlView::_001OnEraseBkgnd(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::erase_bkgnd, perasebkgnd, pobj)
   perasebkgnd->m_bRet = true;
   perasebkgnd->set_result(TRUE);
}

void devedgeHtmlView::_001OnLButtonDown(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void devedgeHtmlView::_001OnLButtonUp(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

void devedgeHtmlView::_001OnMouseMove(gen::signal_object * pobj) 
{
   SCAST_PTR(::user::win::message::mouse, pmouse, pobj)
   point pt = pmouse->m_pt;
}

devedgeHtmlDoc * devedgeHtmlView::get_document() const
{
   return dynamic_cast < devedgeHtmlDoc * > (::userbase::view::get_document());
}

devedge::Element2D * devedgeHtmlView::hit_test(int x, int y)
{
   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
   //devedgeHtmlDoc * pdoc = get_document();
   return NULL;
}

void devedgeHtmlView::_001OnTimer(gen::signal_object * pobj) 
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
   }

}

void devedgeHtmlView::_001OnKeyDown(gen::signal_object * pobj) 
{
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
   UNREFERENCED_PARAMETER(pobj);
   SetTimer(500, 500, NULL);
}

void devedgeHtmlView::_001OnKeyUp(gen::signal_object * pobj) 
{
  // SCAST_PTR(::user::win::message::key, pkey, pobj)
   UNREFERENCED_PARAMETER(pobj);
   KillTimer(500);
   KillTimer(501);
}


void devedgeHtmlView::_001OnChar(gen::signal_object * pobj) 
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


void devedgeHtmlView::_001OnSysChar(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
//   SCAST_PTR(::user::win::message::key, pkey, pobj)
}

void devedgeHtmlView::pre_translate_message(gen::signal_object * pobj)
{
   ::userbase::view::pre_translate_message(pobj);
}

void devedgeHtmlView::key_to_char(WPARAM wparam, LPARAM lparam)
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
