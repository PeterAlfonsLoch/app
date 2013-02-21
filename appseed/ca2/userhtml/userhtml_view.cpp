#include "framework.h"

//   // BEGIN_MESSAGE_MAP(html_view, ::userbase::view)
   //{{__MSG_MAP(html_view)
/*
   ON_WM_DESTROY()
   ON_WM_SIZE()
   ON_WM_PAINT()
   ON_WM_CREATE()
   ON_WM_CONTEXTMENU()
   ON_WM_SETCURSOR()
   ON_WM_ERASEBKGND()
   //}}__MSG_MAP
   // Standard printing commands
   ON_MESSAGE(WM_USER + 177, OnTabClick)
   ON_MESSAGE(WM_APP + 119, OnWavePlayerEvent)
   ON_COMMAND(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
   */
// // END_MESSAGE_MAP()


html_view::html_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::form(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp)
{
}

html_view::~html_view()
{
}

void html_view::install_message_handling(::gen::message::dispatch * pinterface)
{
   ::userbase::view::install_message_handling(pinterface);

   IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &html_view::_001OnDestroy);
   IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &html_view::_001OnSize);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &html_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &html_view::_001OnContextMenu);
   IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &html_view::_001OnSetCursor);

//   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &html_view::_001OnTabClick);
   //connect_command(ID_FILE_PRINT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_DIRECT, ::userbase::view::OnFilePrint)
   //connect_command(ID_FILE_PRINT_PREVIEW, ::userbase::view::OnFilePrintPreview)
//   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
//   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
   IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);

   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &html_view::_001OnLButtonDown);
   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &html_view::_001OnMouseMove);
   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &html_view::_001OnLButtonUp);
   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &html_view::_001OnKeyDown);

}

/////////////////////////////////////////////////////////////////////////////
// html_view diagnostics

#ifdef DEBUG
void html_view::assert_valid() const
{
   ::userbase::view::assert_valid();
}

void html_view::dump(dump_context & dumpcontext) const
{
   ::userbase::view::dump(dumpcontext);
}
#endif //DEBUG


bool html_view::pre_create_window(CREATESTRUCT& cs)
{
#ifdef WINDOWSEX
   cs.lpszClass = System.RegisterWndClass(
      CS_DBLCLKS |
      CS_OWNDC,
      0, 0, 0);
#else
   throw todo(get_app());
#endif
   cs.style &= ~WS_EX_CLIENTEDGE;
   return ::userbase::view::pre_create_window(cs);
}
void html_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{

   ::userbase::view::_001OnInitialUpdate(pobj);

}

void html_view::on_update(::view * pSender, LPARAM lHint, ::gen::object* phint) 
{
   UNREFERENCED_PARAMETER(pSender);
   UNREFERENCED_PARAMETER(lHint);
   if(phint != NULL)
   {
      html_view_update_hint * puh = dynamic_cast < html_view_update_hint * >
         (phint);
      if(puh != NULL)
      {
         if(puh->m_etype == html_view_update_hint::type_document_complete)
         {
            
            layout();

            _001RedrawWindow();

            on_document_complete(puh->m_strUrl);

         }
      }
   }
   
   
}

void html_view::_001OnDestroy(gen::signal_object * pobj) 
{
   ::userbase::view::_001OnDestroy(pobj);

}





void html_view::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;
   
   get_html_data()->m_pguie = this;
   /*get_html_data()->m_papp = get_app();*/
   get_html_data()->m_strPathName = get_document()->get_path_name();


}
void html_view::_001OnContextMenu(gen::signal_object * pobj) 
{
//   SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
//   point point = pcontextmenu->GetPoint();
   
}



void html_view::_001OnSetCursor(gen::signal_object * pobj) 
{

#ifdef WINDOWSEX

   ::SetCursor(::LoadCursor(NULL, IDC_ARROW));

#else

   throw todo(get_app());

#endif
   
   pobj->previous();
}

html_document * html_view::get_document()
{
   return dynamic_cast < html_document * > (::userbase::view::get_document());
}

string html_view::GetLocationURL()
{
   return m_strLocationURL;
}

bool html_view::Refresh2(int32_t i)
{
   UNREFERENCED_PARAMETER(i);
   get_document()->on_open_document(GetLocationURL());
   return true;
}

bool html_view::Navigate(const char * pszUrl)
{
   if(!get_document()->on_open_document(pszUrl))
      return false;
   m_strLocationURL = pszUrl;
   return true;
}

void html_view::on_document_complete(const char * pszUrl)
{
   UNREFERENCED_PARAMETER(pszUrl);
}




