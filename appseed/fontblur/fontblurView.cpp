// fontblurView.cpp : implementation of the CFontblurView class
//

#include "stdafx.h"
#include "fontblur.h"

#include "fontblurDoc.h"
#include "fontblurView.h"

#include "Imaging.h"
#include "Picture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFontblurView

IMPLEMENT_DYNCREATE(CFontblurView, CView)

BEGIN_MESSAGE_MAP(CFontblurView, CView)
	//{{AFX_MSG_MAP(CFontblurView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontblurView construction/destruction

CFontblurView::CFontblurView()
{
	m_font1.CreatePointFont(360, "Times New Roman");

}

CFontblurView::~CFontblurView()
{
}

BOOL CFontblurView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFontblurView drawing

void CFontblurView::OnDraw(CDC* pdc)
{

   CDC dc;

   dc.CreateCompatibleDC(pdc);

   CBitmap bmp;

   CRect rectClient;

   GetClientRect(rectClient);

   int w = rectClient.Width();
   int h = rectClient.Height();

   bmp.CreateCompatibleBitmap(pdc, rectClient.Width(), rectClient.Height());

   dc.SetBkMode(TRANSPARENT);


   CBitmap * pbmpOld = dc.SelectObject(&bmp);
   CFont * pfontOld = dc.SelectObject(&m_font1);
   m_dc2.SelectObject(&m_font1);
   
   int iVersion = GetDocument()->m_iVersion;
   if(iVersion == 0)
   {
      dc.FillSolidRect(rectClient, RGB(241, 250, 255));
      dc.TextOut(0,0,"blur font");
   }
   else if(iVersion == 1)
   {
      dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
         &m_dc1, 0, 0, SRCCOPY);
      dc.TextOut(0,0,"blur font");
   }
   else if(iVersion == 2)
   {
      m_dc2.FillSolidRect(rectClient, RGB(0, 0, 0));
      m_dc2.SetTextColor(RGB(255, 255, 255));
      m_dc2.TextOut(0,0,"blur font");

      dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
         &m_dc1, 0, 0, SRCCOPY);

      CImaging::GetImaging()->Blur(&m_dc2,0, 0, 300, 200,
         &m_dc2, 0, 0, 3);

/*      CImaging::GetImaging()->Blur(&m_dc2,0, 0, 300, 200,
         &m_dc2, 0, 0);
      CImaging::GetImaging()->Blur(&m_dc2,0, 0, 300, 200,
         &m_dc2, 0, 0);
      CImaging::GetImaging()->Blur(&m_dc2,0, 0, 300, 200,
         &m_dc2, 0, 0);*/

      CImaging::GetImaging()->ColorBlend(&dc, 0, 0, 300, 200, 
         RGB(255, 255, 255), &m_dc2, 0, 0);

/*      dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
         &m_dc2, 0, 0, SRCCOPY);*/

      dc.TextOut(0,0,"blur font");
   }
   switch(iVersion)
   {
      case 3:
      {
         int w1 = 100;
         int h1 = 100;
         dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         m_dc2.FillSolidRect(rectClient, RGB(0, 0, 0));
         m_dc2.SetTextColor(RGB(255, 0, 0));
         m_dc2.SelectObject(&m_font1);
         m_dc2.TextOut(0, 0, "blur font");
         CImaging::GetImaging()->ChannelGrayBlur(&m_dc2, 0, 0, w1, h1,
            &m_dc2, 0, 0, 2, 3);
         //dc.BitBlt(0, 0, w, h, &m_dc1, 0, 0, SRCCOPY);
         CImaging::GetImaging()->ColorBlend(&dc, 0, 0, w1, h1,
            RGB(255, 255, 127), &m_dc2, 0, 0);
         dc.SetTextColor(RGB(127, 255, 255));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         dc.TextOut(0, 0, "blur font");
      }
      break;

   case 4:
      {
         //dc.FillSolidRect(rectClient, RGB(, 0, 0));
         dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
            &m_dc1, 0, 0, SRCCOPY);

         m_dc2.FillSolidRect(rectClient, RGB(0, 0, 0));
         m_dc2.SetTextColor(RGB(255, 0, 0));
         m_dc2.SelectObject(&m_font1);
         m_dc2.TextOut(0, 0, "blur font");
         CImaging::GetImaging()->ChannelGrayBlur(&m_dc2, 0, 0, 200, 200,
            &m_dc2, 0, 0, 2, 5);
         CRgn rgnL;
         rgnL.CreateRectRgn(0, 0, 100, h);
         dc.SelectClipRgn(&rgnL);
         //dc.BitBlt(0, 0, w, h, &m_dc1, 0, 0, SRCCOPY);
         CImaging::GetImaging()->ClipColorBlend(&dc, 0, 0, 100, 100,
            RGB(0, 255, 0), &m_dc2, 0, 0);
         dc.SetTextColor(RGB(0, 0, 255));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         dc.TextOut(0, 0, "blur font");

         CRgn rgnR;
         rgnR.CreateRectRgn(100, 0, 200, h);
         dc.SelectClipRgn(&rgnR);
         CImaging::GetImaging()->ClipColorBlend(&dc, 100, 0, 100, h,
            RGB(0, 0, 255), &m_dc2, 100, 0);
         dc.SetTextColor(RGB(255, 0, 0));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         dc.TextOut(0, 0, "blur font");
      }
      break;
   case 5:
      {
         dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         //dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
           
         //&m_dc1, 0, 0, SRCCOPY);

         m_dc2.SelectClipRgn(NULL);
         m_dc2.FillSolidRect(rectClient, RGB(255, 127, 0));
//         m_dc2.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
  //          &m_dc1, 0, 0, SRCCOPY);
         m_dc2.SetTextColor(RGB(255, 255, 255));
         m_dc2.SelectObject(&m_font1);
         m_dc2.TextOut(0, 0, "blur font");
//         CImaging::GetImaging()->ChannelGrayBlur(&m_dc2, 0, 0, 300, 200,
  //          &m_dc2, 0, 0, 2, 5);
         CRgn rgnL;
/*         rgnL.CreateRectRgn(0, 0, 100, h);
         dc.SelectClipRgn(&rgnL);
         //dc.BitBlt(0, 0, w, h, &m_dc1, 0, 0, SRCCOPY);
         CImaging::GetImaging()->ClipColorBlend(&dc, 0, 0, 100, 100,
            RGB(0, 255, 0), &m_dc2, 0, 0);
         dc.SetTextColor(RGB(0, 0, 255));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         dc.TextOut(0, 0, "blur font");*/

         CRgn rgnR;
         rgnR.CreateRectRgn(100, 0, 200, h);
        //dc.SelectClipRgn(&rgnR)
//         CImaging::GetImaging()->ClipColorBlend(&dc,0, 0, w, h, 
  //          RGB(0, 0, 255), &m_dc2, 0, 0);

         dc.BitBlt(0, 0, w, h, &m_dc2, 0, 0, SRCCOPY);

         dc.SetTextColor(RGB(255, 0, 0));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         //dc.TextOut(50, 50, "blur font");
      }
      break;
   case 7:
      {
         dc.FillSolidRect(rectClient, RGB(0, 0, 0));
         //dc.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
           
         //&m_dc1, 0, 0, SRCCOPY);

         m_dc2.SelectClipRgn(NULL);
         m_dc2.FillSolidRect(rectClient, RGB(0, 0, 0));
//         m_dc2.BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
  //          &m_dc1, 0, 0, SRCCOPY);
         m_dc2.SetTextColor(RGB(255, 255, 255));
         m_dc2.SelectObject(&m_font1);
         m_dc2.SetBkMode(TRANSPARENT);
         m_dc2.TextOut(0, 0, "texto compridinho para testar os limites horizontais");
         
         BYTE b[7][7] =
         {
            {4, 4, 4, 4, 4, 4, 4},
            {4, 2, 2, 2, 2, 2, 4},
            {4, 2, 1, 1, 1, 2, 4},
            {4, 2, 1, 0, 1, 2, 4},
            {4, 2, 1, 1, 1, 2, 4},
            {4, 2, 2, 2, 2, 2, 4},
            {4, 4, 4, 4, 4, 4, 4}
         };
//         CImaging::GetImaging()->ChannelGrayBlur(&m_dc2, 0, 0, 300, 200,
  //         &m_dc2, 0, 0, 2, 7, 7, (LPBYTE) b);
         CImaging::GetImaging()->AlphaSpreadR2(&m_dc2, 0, 0, 300, 200,
           &m_dc2, 0, 0, 1);
         CImaging::GetImaging()->ChannelGrayBlur(&m_dc2, 0, 0, 300, 200,
           &m_dc2, 0, 0, 2, 7, 7, (LPBYTE) b);
         CRgn rgnL;
/*         rgnL.CreateRectRgn(0, 0, 100, h);
         dc.SelectClipRgn(&rgnL);
         //dc.BitBlt(0, 0, w, h, &m_dc1, 0, 0, SRCCOPY);
         CImaging::GetImaging()->ClipColorBlend(&dc, 0, 0, 100, 100,
            RGB(0, 255, 0), &m_dc2, 0, 0);
         dc.SetTextColor(RGB(0, 0, 255));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         dc.TextOut(0, 0, "blur font");*/

         CRgn rgnR;
         //rgnR.CreateRectRgn(400, 300, 600, h);
         dc.SelectClipRgn(&rgnR);
         //CImaging::GetImaging()->ClipColorBlend(&dc, 200, 300, 800, 100, 
           // RGB(255, 255, 255), &m_dc2, 0, 0);

         dc.BitBlt(200, 300, w, h, &m_dc2, 0, 0, SRCCOPY);

         dc.SetTextColor(RGB(0, 127, 0));
         //dc.FillSolidRect(rectClient, RGB(255, 255, 255));
         dc.TextOut(200, 300, "texto compridinho para testar os limites horizontais");
      }
      break;
   }

   

	
   pdc->BitBlt(0, 0, rectClient.Width(), rectClient.Height(),
      &dc, 0, 0, SRCCOPY);
   dc.SelectObject(pbmpOld);
   dc.SelectObject(pfontOld);

}

/////////////////////////////////////////////////////////////////////////////
// CFontblurView printing

BOOL CFontblurView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFontblurView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFontblurView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFontblurView diagnostics

#ifdef _DEBUG
void CFontblurView::AssertValid() const
{
	CView::AssertValid();
}

void CFontblurView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFontblurDoc* CFontblurView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFontblurDoc)));
	return (CFontblurDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFontblurView message handlers

int CFontblurView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

   CDC * pdc = GetDC();

   CPicture picture;

   picture.Load("F:\\windows\\web\\wallpaper\\Vento.jpg");


   m_dc1.CreateCompatibleDC(pdc);
   m_dc2.CreateCompatibleDC(pdc);
   CSize size = picture.GetImageSize();
   
   m_bitmap1.CreateCompatibleBitmap(pdc, size.cx, size.cy);
   m_bitmap2.CreateCompatibleBitmap(pdc, size.cx, size.cy);

   CBitmap * pbmpOld = m_dc1.SelectObject(&m_bitmap1);
   m_dc2.SelectObject(&m_bitmap2);

   picture.Render(&m_dc1);
	

	
	return 0;
}

void CFontblurView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   if(lHint == 0 && pHint == NULL)
   {
      RedrawWindow();
   }
	
	
}


BOOL CFontblurView::OnEraseBkgnd(CDC* pDC) 
{
   return TRUE;
	return CView::OnEraseBkgnd(pDC);
}
