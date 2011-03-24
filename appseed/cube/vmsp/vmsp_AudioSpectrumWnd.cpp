#include "StdAfx.h"
#include "AudioSpectrumWnd.h"


AudioSpectrumWnd::AudioSpectrumWnd()
{
   m_pWaveBuffer = NULL;
//   m_pBmpTemplate = new ::ca::bitmap;
//   m_pBmpBuffer = new ::ca::bitmap;
//   m_pBmpMask = new ::ca::bitmap;
   m_pFont = new visual::font(get_app());
   m_pFont->SetFont(new ::ca::font());
   m_pFont->GetFont()->CreatePointFont(140, "Arial");
   m_pen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
   m_lpwaveformatex = NULL;
   m_bEnabled = false;

   OSVERSIONINFO versionInformation;
   versionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
   GetVersionEx(&versionInformation);
   m_bUsePlgBlt = versionInformation.dwPlatformId ==
      VER_PLATFORM_WIN32_NT;
    m_pdc = NULL;
    m_pdcBack = NULL;
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(0, 0, 255)));
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(0, 255, 128)));
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(0, 255, 0)));
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(127, 255, 0)));
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(255, 255, 0)));
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(255, 127, 0)));
//   m_pens.add(new ::ca::pen(PS_SOLID, 1, RGB(255, 0, 0)));
}

AudioSpectrumWnd::~AudioSpectrumWnd()
{
//   delete m_pBmpTemplate;
//   delete m_pBmpBuffer;
//   delete m_pBmpMask;
//   delete m_pFont->GetFont();
   delete m_pFont;
}

 // BEGIN_MESSAGE_MAP(AudioSpectrumWnd, ::ca::window)
   //{{AFX_MSG_MAP(AudioSpectrumWnd)
/* xxx   ON_WM_CREATE()
   ON_WM_SIZE()
   ON_WM_DESTROY() */
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()

void AudioSpectrumWnd::to(
   ::ca::graphics * pdc)
{
   BOOL bresult;
    if(!m_bVisible)
        return;

   rect rectClient;
   GetClientRect(rectClient);

   LPWAVEFORMATEX pWaveFormatEx = m_lpwaveformatex;
   double dDeltaScore = m_dDeltaScore;
   double dScoreAddUp = m_dScoreAddUp;

   if(pWaveFormatEx == NULL)
      return;

    EraseBackground(pdc);

      ::ca::graphics * pgraphics = pdc;
    //::ca::graphics * pDCBack = m_pdcBack;

    ASSERT(m_pWaveBuffer != NULL);
   int x, i, j, k, d, idx;
   double dy, dj, dk, pdata, ddy, ddl;
   double * pfData = m_pWaveBuffer->FFTGetResult();
   int iWidth = rectClient.width();
   int iHeight = rectClient.height();
   pdata = m_pWaveBuffer->m_uiInterestSize / (double) iWidth;
   ddy = iHeight / (double) m_pWaveBuffer->GetMaxLevel();
   ddl = iHeight / (double) m_pens.get_size();
   dk = 0;
//   ::ca::graphics_sp graphicsMem;
//   graphicsMem->CreateCompatibleDC(pgraphics);
//   ::ca::bitmap *pOldBitmap = graphicsMem->SelectObject(m_pBmpMono);
   //graphicsMem->SelectObject(m_pBmpMono);
   string str;
   double dMaxAmplitude;
   double dFrequency = m_pWaveBuffer->PeakValueFrequency(pWaveFormatEx->nSamplesPerSec / 2.0, &dMaxAmplitude);
   if(dMaxAmplitude > m_pWaveBuffer->GetMaxLevel() / 3.0)
   {
      
      str.Format("%0.0fHz", dFrequency );
//      rect rect;
//      GetPlacement(&rect);
      ::ca::font *pOldFont = pgraphics->SelectObject(m_pFont->GetFont());
      pgraphics->SetTextColor(RGB(255, 255, 255));
      pgraphics->SetTextAlign(TA_LEFT | TA_TOP);
      pgraphics->SelectObject(m_pen);
      rect rectTextOut;
      GetClientRect(rectTextOut);
      m_pFont->EmbossedTextOut(pgraphics, rectTextOut, 1.0, rectTextOut.height(), str);
      pgraphics->SelectObject(pOldFont);
   }

//   pgraphics->FillSolidRect(
//      m_iLeft,
//      m_iTop,
//      width(),
//      height(),
//      GetSysColor(COLOR_WINDOW ));
//   pgraphics->Draw3dRect(
//      m_iLeft,
//      m_iTop,
//      width(),
//      height(),
//      GetSysColor(COLOR_3DDKSHADOW),
//      GetSysColor(COLOR_3DHIGHLIGHT));
//   pgraphics->Draw3dRect(
//      m_iLeft + 1,
//      m_iTop + 1,
//      width() - 2,
//      height() - 2,
//      GetSysColor(COLOR_3DDKSHADOW),
//      GetSysColor(COLOR_3DHIGHLIGHT));

//   for(x = m_iLeft, i = 0; x < m_iRight;  x++, i++)
//   graphicsMem->FillSolidRect(0, 0, iWidth, iHeight, RGB(0,  0, 0));
   ::ca::bitmap *pOldBackBitmap;
   ::ca::bitmap *pOldBitmap;
   if(m_bUsePlgBlt)
   {
      pOldBackBitmap = m_dcBack->SelectObject(m_bmpMask);
   }
   else
   {
      pOldBackBitmap = m_dcBack->SelectObject(m_bmpTemplate);
      pOldBitmap = pgraphics->SelectObject(m_bmpBuffer);
      pgraphics->BitBlt(
         0, 0,
         iWidth, iHeight,
         m_dcBack,
         0, 0,
         SRCCOPY);
      m_dcBack->SelectObject(m_bmpMask);
   }
   
   ::ca::pen_sp pen(get_app());
   if(m_bUsePlgBlt)
   {
      m_dcBack->FillSolidRect(0, 0, iWidth, iHeight, 0);
      pen->CreatePen(PS_SOLID, 1, 1);
   }
   else
   {
      m_dcBack->FillSolidRect(0, 0, iWidth, iHeight, RGB(0,  0, 0));
      pen->CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
   }
   //::ca::pen * pPenOld = graphicsMem->SelectObject(pen);
   ::ca::pen * pPenOld = m_dcBack->SelectObject(pen);
   for(x = 0, i = 0; x < iWidth;  x++, i++)
   {
/*      dj = dk;
      dk += pdata;
      j = (int) dj;
      k = int (dk);
      d = k - j;
      if(d > 0)
      {
         dy = 0;
         for(idx = j; idx < k; idx++)
         {
            dy += pfData[idx] / (double) d;
         }
         dy *= ddy;
      }*/
      dy = pfData[idx];
      m_dcBack->MoveTo(x, iHeight);
      m_dcBack->LineTo(x, (int) (iHeight - iHeight * dy));
//      pgraphics->MoveTo(x, m_iBottom);
//      for(j = 0; j < m_pens.get_size(); j++)
//      {
//         pgraphics->SelectObject(m_pens[j]);
//         if(dy < (j + 1) * ddl)
//         {
//            pgraphics->LineTo(x, (int) (m_iBottom - dy));
//            break;
//         }
//         else
//         {
//            pgraphics->LineTo(x, (int) (m_iBottom - (j + 1) * ddl));
//         }
//      }
      
   }
   if(m_bUsePlgBlt)
   {
      point points[3];
      points[0].x = rectClient.left;
      points[0].y = rectClient.top;
      points[1].x = rectClient.right;
      points[1].y = rectClient.top;
      points[2].x = rectClient.left;
      points[2].y = rectClient.bottom;

      m_dcBack->SelectObject(m_bmpTemplate);
      bresult = pgraphics->PlgBlt(
         points,
         m_dcBack,
         0, 0,
         iWidth, iHeight,
         m_bmpMask,
         0, 0);
   }
   else
   {
      pgraphics->BitBlt(
         0, 0,
         iWidth, iHeight,
         m_dcBack,
         0, 0,
         SRCAND);
      pgraphics->SelectObject(pOldBitmap);
      m_dcBack->BitBlt(
         0, 0,
         iWidth, iHeight,
         pgraphics,
         0, 0,
         DSTINVERT);
      pgraphics->BitBlt(
         rectClient.left, rectClient.top,
         rectClient.width(), rectClient.height(),
         m_dcBack,
         0, 0,
         SRCAND);
      m_dcBack->SelectObject(m_bmpBuffer);
      pgraphics->BitBlt(
         rectClient.left, rectClient.top,
         rectClient.width(), rectClient.height(),
         m_dcBack,
         0, 0,
         SRCPAINT);
   }
   m_dcBack->SelectObject(pOldBackBitmap);
//   pDCBack->SelectObject(m_pBmpColor);
//   void * lpData = new BYTE[(((iWidth * 3) + 3) & ~3) * iHeight];
//   BITMAPINFO bmInfo;
//
//   bmInfo.bmiHeader.biSize =  sizeof(BITMAPINFOHEADER);
//   bmInfo.bmiHeader.biBitCount = 0;
//
//   i = GetDIBits(
//      graphicsMem->get_os_data(),
//      *m_pBmpMono,
//      0,
//      iHeight,
//      NULL,
//      &bmInfo,
//      DIB_RGB_COLORS);

//   bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//   bmInfo.bmiHeader.biWidth = width();
//   bmInfo.bmiHeader.biHeight = height();
//   bmInfo.bmiHeader.biPlanes = 1;
//   bmInfo.bmiHeader.biBitCount = 1;
//   bmInfo.bmiHeader.biCompression = BI_RGB;
//   bmInfo.bmiHeader.biSizeImage = 0;
//   bmInfo.bmiHeader.biXPelsPerMeter = 1;
//   bmInfo.bmiHeader.biYPelsPerMeter = 1;
//   bmInfo.bmiHeader.biClrUsed = 0;
//   bmInfo.bmiHeader.biClrImportant = 0;
//   i = GetDIBits(
//      pgraphics->get_os_data(),
//      *m_pBmpMono,
//      0,
//      iHeight,
//      lpData,
//      &bmInfo,
//      DIB_RGB_COLORS);
//   delete lpData;


//   point points[3];
//   points[0].x = m_iLeft;
//   points[0].y = m_iTop;
//   points[1].x = m_iRight;
//   points[1].y = m_iTop;
//   points[2].x = m_iLeft;
///   points[2].y = m_iBottom;
//   (m_iLeft, m_iTop);
//   i = pgraphics->GetDeviceCaps(RASTERCAPS) & RC_BITBLT;
//   i = pgraphics->MaskBlt(
//      m_iLeft, m_iTop,
//      iWidth, iHeight,
//      pDCBack,
//      0, 0,
//      *m_pBmpMono,
//      0, 0,
//      MAKEROP4(SRCCOPY, 0) & 0xFFFF0000);
//   i = pgraphics->PlgBlt(
//      points,
//      pDCBack,
//      0, 0,
//      iWidth, iHeight,
//      *m_pBmpMono,
//      0, 0);
   rect rect;
   GetClientRect(&rect);
   m_dcBack->SelectObject(pPenOld);
   pen->delete_object();

   rect.bottom = rect.top + 10;
   rect.left = rect.right - 10;
   ::ca::pen_sp penSignal(get_app());
   ::ca::brush_sp brushSignal(get_app());
   
   static DWORD dwLastTime0 = 0;
   static int ie = 0;
//   TRACE("dDeltaScore = %f ie = %d dwLastTime0 = %d\n", dDeltaScore, ie, dwLastTime0);
//   TRACE("dScoreAddUP = %f\n", dScoreAddUp);
   if((dDeltaScore > -dScoreAddUp  && 
      dDeltaScore <= 0.0) ||
      dDeltaScore == 0.0)
   {
      if(dwLastTime0 + 1000<timeGetTime())
      {
         dwLastTime0 = timeGetTime();
         ie = 0;
      }
   }
   else if(dDeltaScore > 0.0)
   {
      ie = 1;
   }
   else 
   {
      ie = -1;
   }
   if(ie == 0)
   {
      penSignal->CreatePen(PS_SOLID, 0, RGB(127, 127, 0));   
      brushSignal->CreateSolidBrush(RGB(255,255,0));
   }
   else if (ie > 0)
   {
      penSignal->CreatePen(PS_SOLID, 0, RGB(0, 127, 0));   
      brushSignal->CreateSolidBrush(RGB(0,255,0));
   }
   else
   {
      penSignal->CreatePen(PS_SOLID, 0, RGB(127, 0, 0));   
      brushSignal->CreateSolidBrush(RGB(255,0,0));
   }
   pPenOld = pgraphics->SelectObject(penSignal);
   ::ca::brush *pBrushOld = pgraphics->SelectObject(brushSignal);
   pgraphics->Ellipse(rect);
   

   pgraphics->SelectObject(pPenOld);
   pgraphics->SelectObject(pBrushOld);
   penSignal->delete_object();
   brushSignal->delete_object();
//   pDCBack->SelectObject(pOldBitmap);
//   graphicsMem->DeleteDC();
}

//int AudioSpectrumWnd::width()
//{
//   return m_iRight - m_iLeft;
//}

//int AudioSpectrumWnd::height()
//{
//   return m_iBottom - m_iTop;
//}

void AudioSpectrumWnd::SetPlacement(
   ::ca::graphics * pgraphics,
   int iLeft,
   int iTop,
   int iRight,
   int iBottom)
{
//   int iWidth = width();
//   int iHeight = height();
//   if(m_iLeft == iLeft &&
//      m_iTop == iTop &&
//      m_iRight == iRight &&
//      m_iBottom == iBottom)
//      return;
//   m_iLeft      = iLeft;
//   m_iTop      = iTop;
//   m_iRight   = iRight;
//   m_iBottom   = iBottom;
//   if(width() <= 0 ||
//      height() <= 0 ||
//      (iWidth == width() &&
//       iHeight == height()))
//      return;

   rect rectClient;
   GetClientRect(rectClient);
   int iw = rectClient.width();
   int ih = rectClient.height();

   m_bmpTemplate->delete_object();
   m_bmpTemplate->CreateCompatibleBitmap(
      pgraphics,
      iw, ih);

   m_dcBack->DeleteDC();

//   m_pBmpTemplate->CreateBitmap(
//      width(), height(),
//      1,
//      24,
//      NULL);
   if(m_bUsePlgBlt)
   {
      m_bmpBack->delete_object();
      m_bmpBack->CreateCompatibleBitmap(
         pgraphics,
         iw, ih);

      m_bmpMask->delete_object();
      m_bmpMask->CreateBitmap(
         iw, ih,
         1,
         1,
         NULL);


   }
   else
   {
      m_bmpBack->delete_object();
      m_bmpBack->CreateCompatibleBitmap(
         pgraphics,
         iw, ih);

      m_bmpBuffer->delete_object();
      m_bmpBuffer->CreateCompatibleBitmap(
         pgraphics,
         iw, ih);

   //   m_pBmpBuffer->CreateBitmap(
   ///      width(), height(),
   //      1,
   //      24,
   //      NULL);
      
      m_bmpMask->delete_object();
   //   m_pBmpMask->CreateBitmap(
   //      width(), height(),
   //      1,
   //      24,
   //      NULL);
      m_bmpMask->CreateCompatibleBitmap(
         pgraphics,
         iw, ih);
   }

   m_dcBack->CreateCompatibleDC(pgraphics);
   m_dcBack->SelectObject(m_bmpBack);

//   m_pBmpColor->CreateCompatibleBitmap(pgraphics, width(), height());
//   m_pBmpColor->CreateBitmap(
//      width(), height(),
//      1,
//      24,
//      NULL);
   int iWidthAligned = (iw * 3 + 3) & ~3;
   int iHeight = ih;
   LPBYTE lpBitmap = new BYTE[iWidthAligned * iHeight];
   int iWidth = iw * 3;
   LPBYTE lpByte;
   int x, y;
   color color;
   double dHue;
   double dLightness = 700.0;
   double dSaturation = 800.0;
   for(y = 0; y < iHeight; y++)
   {
      dHue = (iHeight - y) *  2.0 / (iHeight * 3.0);
      color.set_hls(dHue, dLightness, dSaturation);
      lpByte = lpBitmap + y * iWidthAligned;
      for(x = 0; x < iWidth; x += 3)
      {
         *lpByte++ = color.m_uchB;
         *lpByte++ = color.m_uchG;
         *lpByte++ = color.m_uchR;
      }
   }
   BITMAPINFO bmInfo;
   bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bmInfo.bmiHeader.biWidth = iw;
   bmInfo.bmiHeader.biHeight = ih;
   bmInfo.bmiHeader.biPlanes = 1;
   bmInfo.bmiHeader.biBitCount = 24;
   bmInfo.bmiHeader.biCompression = BI_RGB;
   bmInfo.bmiHeader.biSizeImage = 0;
   bmInfo.bmiHeader.biXPelsPerMeter = 0;
   bmInfo.bmiHeader.biYPelsPerMeter = 0;
   bmInfo.bmiHeader.biClrUsed = 0;
   bmInfo.bmiHeader.biClrImportant = 0;
   int iScanLines = SetDIBits(
      (HDC) pgraphics->get_os_data(),
      (HBITMAP) m_bmpTemplate->get_os_data(),
      0, iHeight,
      lpBitmap,
      &bmInfo,
      DIB_RGB_COLORS);
   delete lpBitmap;

}

//void AudioSpectrumWnd::GetPlacement(LPRECT lprect)
//{
   //lpRect->left = m_iLeft;
   //lpRect->right = m_iRight;
   //lpRect->top = m_iTop;
   //lpRect->bottom = m_iBottom;
//   GetClientRect(lprect);
//}


//int AudioSpectrumWnd::GetBottom()
//{
//   return m_iBottom;

//}

bool AudioSpectrumWnd::GetVisible()
{
    return m_bVisible;
}

void AudioSpectrumWnd::SetVisible(bool bVisible)
{
    m_bVisible = bVisible;
//    if(!m_bVisible)
  //      EraseBackground();
}

VMSRESULT AudioSpectrumWnd::EraseBackground(::ca::graphics * pdc)
{
//      ::ca::graphics * pgraphics = m_pdc;
  //  ::ca::graphics * pDCBack = &m_dcBack;
   //pgraphics->BitBlt(
    //  m_iLeft, m_iTop,
      //width(), height(),
      //pDCBack,
      //m_iLeft, m_iTop,
      //SRCCOPY);
    return VMSR_SUCCESS;
}

VMSRESULT AudioSpectrumWnd::SetDC(::ca::graphics *pdc, ::ca::graphics *pdcBack)
{
    m_pdc = pdc;
    m_pdcBack = pdcBack;
    return VMSR_SUCCESS;
}

void AudioSpectrumWnd::Update(
   LPWAVEFORMATEX lpwaveformatex,
   double dDeltaScore,
   double dScoreAddUp)
{
   m_lpwaveformatex = lpwaveformatex;
   m_dDeltaScore = dDeltaScore;
   m_dScoreAddUp = dScoreAddUp;
   _001RedrawWindow();
}

int AudioSpectrumWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   if (::ca::window::OnCreate(lpCreateStruct) == -1)
      return -1;
   
   Enable();
   
   return 0;
}

void AudioSpectrumWnd::TwiOnDraw(::ca::graphics *pdc)
{
   to(pdc);
}

void AudioSpectrumWnd::OnSize(UINT nType, int cx, int cy) 
{
   ::ca::window::OnSize(nType, cx, cy);
   
   rect rectClient;
   GetClientRect(rectClient);
   ::ca::graphics * pdc = GetDC();
   SetPlacement(
      pdc,
      rectClient.left,
      rectClient.top,
      rectClient.right,
      rectClient.bottom);
   ReleaseDC(pdc);
}

void AudioSpectrumWnd::OnDestroy() 
{
}

void AudioSpectrumWnd::PostNcDestroy() 
{
   ::ca::window::PostNcDestroy();
   delete this;
}

bool AudioSpectrumWnd::Enable(bool bEnable)
{
   audWaveCentral  wavecentral = Application.GetAudioWaveCentral();
    audWaveIn * pwavein = wavecentral.GetWaveIn();
   if(pwavein == NULL)
      return VMSR_SUCCESS;

   audWaveBuffer & buffer = pwavein->GetBuffer();

   LPWAVEFORMATEX lpformatex = pwavein->GetFormatEx();
   ASSERT(lpformatex != NULL);

   //gen::thread * pplusthread  = gen::CPlusThreadContainer::AppGetPlusThread();
      
    if(bEnable)
    {
      if(!m_bEnable)
         pwavein->AddRef();
      if(!pwavein->IsOpened())
      {
         if(pwavein->open(8, 48 * 1024) != MMSYSERR_NOERROR)
         {
            if(!m_bEnable)
               pwavein->Release();
            return false;
         }
      }
      if(pwavein->Start() != MMSYSERR_NOERROR)
      {
         if(!m_bEnable)
            pwavein->Release();
         return false;
      }
    }
    else
    {
      if(!m_bEnable)
         pwavein->Release();
    }
    return true;
}
