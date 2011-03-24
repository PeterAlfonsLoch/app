#include "StdAfx.h"
#include "AudioSpectrumVirtualView.h"

AudioSpectrumVirtualView::AudioSpectrumVirtualView(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   m_bmpTemplate(papp),
   m_dcBack(papp),
   m_bmpBack(papp),
   m_bmpMask(papp),
   m_font(papp),
   m_pen(papp),
   m_bmpBuffer(papp)
{
   
   m_pWaveBuffer = NULL;

}

AudioSpectrumVirtualView::~AudioSpectrumVirtualView()
{
/*   gen::Thread & highthread = gen::ThreadContainer::AppGetHighThread();
   if(&highthread != NULL)
   {
      highthread.DeleteTimer(this);
   }
*/
}

void AudioSpectrumVirtualView::_001OnDraw(::ca::graphics *pdc)
{
   if(m_pWaveBuffer == NULL)
      return;
   BOOL bresult;

   rect rectClient;
   GetClientRect(rectClient);

   LPWAVEFORMATEX pWaveFormatEx = m_lpwaveformatex;
   double dDeltaScore = m_dDeltaScore;
   double dScoreAddUp = m_dScoreAddUp;

   if(pWaveFormatEx == NULL)
      return;


   ASSERT(m_pWaveBuffer != NULL);
   int x, i, j, k, d, idx;
   double dy, dj, dk, pdata, ddy, ddl;
   double * pfData = m_pWaveBuffer->FFTGetResult();
   int iWidth = rectClient.width();
   int iHeight = rectClient.height();
   double dMaxLevel;
   //dMaxLevel = m_pWaveBuffer->GetMaxLevel();
   dMaxLevel = 16384.0;

   pdata = m_pWaveBuffer->m_uiInterestSize / (double) iWidth;
   ddy = iHeight / (double) dMaxLevel;
   ddl = iHeight / (double) m_pens.get_size();
   dk = 0;
//   ::ca::graphics_sp graphicsMem->
//   graphicsMem->CreateCompatibleDC(pdc);
//   ::ca::bitmap *pOldBitmap = graphicsMem->SelectObject(m_pBmpMono);
   //graphicsMem->SelectObject(m_pBmpMono);
   string str;
   double dMaxAmplitude;
   double dFrequency = m_pWaveBuffer->PeakValueFrequency(220, 880, pWaveFormatEx->nSamplesPerSec / 2.0, &dMaxAmplitude);
   if(dMaxAmplitude > dMaxLevel / 3.0)
   {
      
      str.Format("%0.0fHz", dFrequency );
//      rect rect;
//      GetPlacement(&rect);
      ::ca::font *pOldFont = pdc->SelectObject(m_font);
      pdc->SetTextColor(RGB(255, 255, 255));
      pdc->SetTextAlign(TA_LEFT | TA_TOP);
      pdc->SelectObject(m_pen);
      rect rectTextOut;
      GetClientRect(rectTextOut);
      ::visual::font font(get_app());
      font.SetFont(m_font);
      font.EmbossedTextOut(pdc, rectTextOut, 1.0, rectTextOut.height(), str);
      pdc->SelectObject(pOldFont);
   }

   ::ca::bitmap *pOldBackBitmap;
   ::ca::bitmap *pOldBitmap;
   if(m_bUsePlgBlt)
   {
      pOldBackBitmap = m_dcBack->SelectObject(m_bmpMask);
   }
   else
   {
      pOldBackBitmap = m_dcBack->SelectObject(m_bmpTemplate);
      pOldBitmap = pdc->SelectObject(m_bmpBuffer);
      pdc->BitBlt(
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
      dj = dk;
      dk += pdata;
      j = (int) dj;
      k = int (dk);
      d = k - j;
      if(d > 0)
      {
         dy = 0;
         for(idx = j; idx < k; idx++)
         {
            dy += pfData[idx];
         }
         dy /= (double) d;
         dy *= ddy;
      }
      m_dcBack->MoveTo(x, iHeight);
      m_dcBack->LineTo(x, (int) (iHeight - dy));
      
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
      bresult = pdc->PlgBlt(
         points,
         m_dcBack,
         0, 0,
         iWidth, iHeight,
         m_bmpMask,
         0, 0);
   }
   else
   {
      pdc->BitBlt(
         0, 0,
         iWidth, iHeight,
         m_dcBack,
         0, 0,
         SRCAND);
      pdc->SelectObject(pOldBitmap);
      m_dcBack->BitBlt(
         0, 0,
         iWidth, iHeight,
         pdc,
         0, 0,
         DSTINVERT);
      pdc->BitBlt(
         rectClient.left, rectClient.top,
         rectClient.width(), rectClient.height(),
         m_dcBack,
         0, 0,
         SRCAND);
      m_dcBack->SelectObject(m_bmpBuffer);
      pdc->BitBlt(
         rectClient.left, rectClient.top,
         rectClient.width(), rectClient.height(),
         m_dcBack,
         0, 0,
         SRCPAINT);
   }
   m_dcBack->SelectObject(pOldBackBitmap);
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
   pPenOld = pdc->SelectObject(penSignal);
   ::ca::brush *pBrushOld = pdc->SelectObject(brushSignal);
   pdc->Ellipse(rect);
   

   pdc->SelectObject(pPenOld);
   pdc->SelectObject(pBrushOld);
   penSignal->delete_object();
   brushSignal->delete_object();

}

void AudioSpectrumVirtualView::layout()
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

   ::ca::graphics * pdc = GetDC();

   rect rectClient;
   GetClientRect(rectClient);
   int iw = rectClient.width();
   int ih = rectClient.height();

   if(m_bmpTemplate->get_os_data() != NULL)
   {
      m_bmpTemplate->delete_object();
   }
   m_bmpTemplate->CreateCompatibleBitmap(
      pdc,
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
         pdc,
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
         pdc,
         iw, ih);

      m_bmpBuffer->delete_object();
      m_bmpBuffer->CreateCompatibleBitmap(
         pdc,
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
         pdc,
         iw, ih);
   }

   m_dcBack->CreateCompatibleDC(pdc);
   m_dcBack->SelectObject(m_bmpBack);

//   m_pBmpColor->CreateCompatibleBitmap(pdc, width(), height());
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
   double dLightness = 0.57;
   double dSaturation = 0.57;
   for(y = 0; y < iHeight; y++)
   {
      dHue = 4.0 / 6.0 * (1.0 - y / (double) iHeight);
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
   SetDIBits(
      (HDC)pdc->get_os_data(),
      (HBITMAP) m_bmpTemplate->get_os_data(),
      0, iHeight,
      lpBitmap,
      &bmInfo,
      DIB_RGB_COLORS);
   delete lpBitmap;


   if(m_font->get_os_data() != NULL)
   {
      m_font->delete_object();
   }
   m_font->CreatePointFont(140, "Arial");

   if(m_pen->get_os_data() != NULL)
   {
      m_pen->delete_object();
   }
   m_pen->CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

   ReleaseDC(pdc);

}

void AudioSpectrumVirtualView::InstallMessageHandling(::user::win::message::dispatch *pinterface)
{
   ::user::interaction::_001InstallMessageHandling(pinterface);
}


void AudioSpectrumVirtualView::Update(
   LPWAVEFORMATEX lpwaveformatex,
   double dDeltaScore,
   double dScoreAddUp)
{
   m_lpwaveformatex = lpwaveformatex;
   m_dDeltaScore = dDeltaScore;
   m_dScoreAddUp = dScoreAddUp;
}

bool AudioSpectrumVirtualView::_001OnCreate()
{
/*xxx   audWaveCentral & wavecentral =
   audWaveCentralContainer::AppGetAudioWaveCentral();
   audWaveIn * pwavein = wavecentral.GetWaveIn();
   pwavein->AddListener(this);
   m_pWaveBuffer = &pwavein->GetBuffer();
   m_lpwaveformatex = pwavein->GetFormatEx();*/


   OSVERSIONINFO versionInformation;
   versionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
   GetVersionEx(&versionInformation);
   m_bUsePlgBlt = versionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT;

   /*gen::Thread & highthread = gen::ThreadContainer::AppGetHighThread();
   highthread.CreateTimer(
      this,
      100,
      1);*/
   return true;
}


void AudioSpectrumVirtualView::TimerProc(UINT uiIDEvent)
{
   if(uiIDEvent == 1)
   {
      rect rectClient;
      GetClientRect(rectClient);
      _001RedrawWindow();
   }
}


void AudioSpectrumVirtualView::VirtualOnSize()
{
   layout();
}

