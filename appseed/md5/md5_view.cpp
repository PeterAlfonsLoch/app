#include "StdAfx.h"


namespace md5
{

   
//   BEGIN_MESSAGE_MAP(view, BaseView)
	//{{AFX_MSG_MAP(view)
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
	ON_COMMAND(ID_FILE_PRINT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, BaseView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, BaseView::OnFilePrintPreview)
   */
//   END_MESSAGE_MAP()


   view::view(::ca::application * papp) :
      ca(papp)
   {
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(user::win::message::dispatch * pinterface)
   {
      userbase::view::_001InstallMessageHandling(pinterface);
   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void view::dump(dump_context& dc) const
   {
	   ::userbase::view::dump(dc);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   BOOL view::PreCreateWindow(CREATESTRUCT& cs)
   {
/*      cs.lpszClass = AfxRegisterWndClass(
		   CS_DBLCLKS |
		   CS_OWNDC,
		   0, 0, 0);
      cs.style &= ~WS_EX_CLIENTEDGE;*/
	   return ::userbase::view::PreCreateWindow(cs);
   }

   /////////////////////////////////////////////////////////////////////////////
   // OLE Server support

   // The following command handler provides the standard keyboard
   //  user interface to cancel an in-place editing session.  Here,
   //  the server (not the container) causes the deactivation.
   //void view::OnCancelEditSrvr()
   //{
   //	GetscreencaptureViewData()->OnDeactivateUI(FALSE);
   //}

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers
   void view::on_update(::view * pSender, LPARAM lHint, base_object* phint) 
   {
   }

   void view:: _001OnDraw(::ca::graphics * pdc)
   {

      pdc->TextOutA(10, 10, get_document()->m_strCheckMd5);
      pdc->TextOutA(10, 50, get_document()->m_thread.m_strFile);


      if(get_document()->m_thread.m_bReady)
      {
         pdc->TextOutA(10, 100, get_document()->m_thread.m_strMd5);
      }
      else
      {
         class rect rect;

         rect.left   = 10;
         rect.top    = 100;
         rect.right  = rect.left + 400;
         rect.bottom = rect.top + 25;

         pdc->Draw3dRect(rect, RGB(0, 128, 0), RGB(0, 128, 0));
         rect.deflate(1, 1);
         pdc->Draw3dRect(rect, RGB(255, 255, 255), RGB(255, 255, 255));
         rect.deflate(1, 1);
         rect.right = rect.left + rect.width() * get_document()->m_thread.m_dProgress;
         pdc->FillSolidRect(rect, RGB(0, 128, 0));
      }

//      GetDocument()->m_document._001OnDraw(pdc);

      //FIBITMAP * pdib = CImaging::LoadImageFile("C:\\screenshot.jpeg");

      //CBitmap bmp2;

      //bmp2.Attach(CImaging::FItoHBITMAP(pdib, true));
      //::ca::graphics dc2;
      //dc2.CreateCompatibleDC(pdc);
      //dc2.SelectObject(&bmp2);

      //::SendMessage(::GetDesktopWindow(), WM_PRINT, (WPARAM)(HDC)dc, PRF_CHILDREN | PRF_NONCLIENT | PRF_CLIENT);

      //pdc->BitBlt(0, 0, 1280, 1024, &dc2, 0, 0, SRCCOPY);
   //   pdc->TextOut(20, 20, "Curitiba, 24 de fevereiro de 2008.");
     // pdc->TextOut(20, 80, "Carlos Gustavo Cecyn Lundgren é minha Vida Eterna, meu Coração Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!");
      //pdc->TextOut(20, 110, "Assinado Camilo Sasuke Tsumanuma.");
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (m_pDocument);
   }

} // namespace md5