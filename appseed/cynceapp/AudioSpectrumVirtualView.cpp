#include "stdafx.h"

AudioSpectrumVirtualView::AudioSpectrumVirtualView()
{
   
   m_pWaveBuffer = NULL;

}

AudioSpectrumVirtualView::~AudioSpectrumVirtualView()
{
	gen::Thread & highthread = gen::ThreadContainer::AppGetHighThread();
   if(&highthread != NULL)
   {
	   highthread.DeleteTimer(this);
   }

}

void AudioSpectrumVirtualView::_001OnDraw(CDC *pdc)
{
   if(m_pWaveBuffer == NULL)
      return;
	BOOL bresult;

	CRect rectClient;
	GetClientRect(rectClient);

	LPWAVEFORMATEX pWaveFormatEx = m_lpwaveformatex;
	double dDeltaScore = m_dDeltaScore;
	double dScoreAddUp = m_dScoreAddUp;

	if(pWaveFormatEx == NULL)
		return;


   ASSERT(m_pWaveBuffer != NULL);
	int x, i, j, k, d, idx;
	double dy, dj, dk, ddx, ddy, ddl;
	double * pfData = m_pWaveBuffer->FFTGetResult();
	int iWidth = rectClient.Width();
	int iHeight = rectClient.Height();
   double dMaxLevel;
   //dMaxLevel = m_pWaveBuffer->GetMaxLevel();
   dMaxLevel = 16384.0;

	ddx = m_pWaveBuffer->m_uiInterestSize / (double) iWidth;
	ddy = iHeight / (double) dMaxLevel;
	ddl = iHeight / (double) m_pens.GetSize();
	dk = 0;
//	CDC dcMem;
//	dcMem.CreateCompatibleDC(pdc);
//	CBitmap *pOldBitmap = dcMem.SelectObject(m_pBmpMono);
	//dcMem.SelectObject(m_pBmpMono);
	CString str;
	double dMaxAmplitude;
	double dFrequency = m_pWaveBuffer->PeakValueFrequency(220, 880, pWaveFormatEx->nSamplesPerSec / 2.0, &dMaxAmplitude);
	if(dMaxAmplitude > dMaxLevel / 3.0)
	{
		
		str.Format(_T("%0.0fHz"), dFrequency );
//		CRect rect;
//		GetPlacement(&rect);
		CFont *pOldFont = pdc->SelectObject(m_pFont->GetFont());
		pdc->SetTextColor(RGB(255, 255, 255));
		pdc->SetTextAlign(TA_LEFT | TA_TOP);
		pdc->SelectObject(&m_pen);
		CRect rectTextOut;
		GetClientRect(rectTextOut);
		m_pFont->EmbossedTextOut(pdc, rectTextOut, 1.0, rectTextOut.Height(), str);
		pdc->SelectObject(pOldFont);
	}

	CBitmap *pOldBackBitmap;
	CBitmap *pOldBitmap;
	if(m_bUsePlgBlt)
	{
		pOldBackBitmap = m_dcBack.SelectObject(&m_bmpMask);
	}
	else
	{
		pOldBackBitmap = m_dcBack.SelectObject(&m_bmpTemplate);
		pOldBitmap = pdc->SelectObject(&m_bmpBuffer);
		pdc->BitBlt(
			0, 0,
			iWidth, iHeight,
			&m_dcBack,
			0, 0,
			SRCCOPY);
		m_dcBack.SelectObject(&m_bmpMask);
	}
	
	CPen pen;
	if(m_bUsePlgBlt)
	{
		m_dcBack.FillSolidRect(0, 0, iWidth, iHeight, 0);
		pen.CreatePen(PS_SOLID, 1, 1);
	}
	else
	{
		m_dcBack.FillSolidRect(0, 0, iWidth, iHeight, RGB(0,  0, 0));
		pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	}
	//CPen * pPenOld = dcMem.SelectObject(&pen);
	CPen * pPenOld = m_dcBack.SelectObject(&pen);
	for(x = 0, i = 0; x < iWidth;  x++, i++)
	{
		dj = dk;
		dk += ddx;
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
		m_dcBack.MoveTo(x, iHeight);
		m_dcBack.LineTo(x, (int) (iHeight - dy));
		
	}
	if(m_bUsePlgBlt)
	{
		CPoint points[3];
		points[0].x = rectClient.left;
		points[0].y = rectClient.top;
		points[1].x = rectClient.right;
		points[1].y = rectClient.top;
		points[2].x = rectClient.left;
		points[2].y = rectClient.bottom;

		m_dcBack.SelectObject(&m_bmpTemplate);
		bresult = pdc->PlgBlt(
			points,
			&m_dcBack,
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
			&m_dcBack,
			0, 0,
			SRCAND);
		pdc->SelectObject(pOldBitmap);
		m_dcBack.BitBlt(
			0, 0,
			iWidth, iHeight,
			pdc,
			0, 0,
			DSTINVERT);
		pdc->BitBlt(
			rectClient.left, rectClient.top,
			rectClient.Width(), rectClient.Height(),
			&m_dcBack,
			0, 0,
			SRCAND);
		m_dcBack.SelectObject(&m_bmpBuffer);
		pdc->BitBlt(
			rectClient.left, rectClient.top,
			rectClient.Width(), rectClient.Height(),
			&m_dcBack,
			0, 0,
			SRCPAINT);
	}
	m_dcBack.SelectObject(pOldBackBitmap);
	CRect rect;
	GetClientRect(&rect);
	m_dcBack.SelectObject(pPenOld);
	pen.DeleteObject();

	rect.bottom = rect.top + 10;
	rect.left = rect.right - 10;
	CPen penSignal;
	CBrush brushSignal;
	
	static DWORD dwLastTime0 = 0;
	static int ie = 0;
//	TRACE(_T("dDeltaScore = %f ie = %d dwLastTime0 = %d\n"), dDeltaScore, ie, dwLastTime0);
//	TRACE(_T("dScoreAddUP = %f\n"), dScoreAddUp);
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
		penSignal.CreatePen(PS_SOLID, 0, RGB(127, 127, 0));	
		brushSignal.CreateSolidBrush(RGB(255,255,0));
	}
	else if (ie > 0)
	{
		penSignal.CreatePen(PS_SOLID, 0, RGB(0, 127, 0));	
		brushSignal.CreateSolidBrush(RGB(0,255,0));
	}
	else
	{
		penSignal.CreatePen(PS_SOLID, 0, RGB(127, 0, 0));	
		brushSignal.CreateSolidBrush(RGB(255,0,0));
	}
	pPenOld = pdc->SelectObject(&penSignal);
	CBrush *pBrushOld = pdc->SelectObject(&brushSignal);
	pdc->Ellipse(rect);
	

	pdc->SelectObject(pPenOld);
	pdc->SelectObject(pBrushOld);
	penSignal.DeleteObject();
	brushSignal.DeleteObject();

}

void AudioSpectrumVirtualView::Layout(LPCRECT lpcrect)
{
//	int iWidth = Width();
//	int iHeight = Height();
//	if(m_iLeft == iLeft &&
//		m_iTop == iTop &&
//		m_iRight == iRight &&
//		m_iBottom == iBottom)
//		return;
//	m_iLeft		= iLeft;
//	m_iTop		= iTop;
//	m_iRight	= iRight;
//	m_iBottom	= iBottom;
//	if(Width() <= 0 ||
//		Height() <= 0 ||
//		(iWidth == Width() &&
//		 iHeight == Height()))
//		return;

   CDC * pdc = GetDC();

	CRect rectClient;
	GetClientRect(rectClient);
	int iw = rectClient.Width();
	int ih = rectClient.Height();

	m_bmpTemplate.DeleteObject();
	m_bmpTemplate.CreateCompatibleBitmap(
		pdc,
		iw, ih);

	m_dcBack.DeleteDC();

//	m_pBmpTemplate->CreateBitmap(
//		Width(), Height(),
//		1,
//		24,
//		NULL);
	if(m_bUsePlgBlt)
	{
		m_bmpBack.DeleteObject();
		m_bmpBack.CreateCompatibleBitmap(
			pdc,
			iw, ih);

		m_bmpMask.DeleteObject();
		m_bmpMask.CreateBitmap(
			iw, ih,
			1,
			1,
			NULL);


	}
	else
	{
		m_bmpBack.DeleteObject();
		m_bmpBack.CreateCompatibleBitmap(
			pdc,
			iw, ih);

		m_bmpBuffer.DeleteObject();
		m_bmpBuffer.CreateCompatibleBitmap(
			pdc,
			iw, ih);

	//	m_pBmpBuffer->CreateBitmap(
	///		Width(), Height(),
	//		1,
	//		24,
	//		NULL);
		
		m_bmpMask.DeleteObject();
	//	m_pBmpMask->CreateBitmap(
	//		Width(), Height(),
	//		1,
	//		24,
	//		NULL);
		m_bmpMask.CreateCompatibleBitmap(
			pdc,
			iw, ih);
	}

	m_dcBack.CreateCompatibleDC(pdc);
	m_dcBack.SelectObject(&m_bmpBack);

//	m_pBmpColor->CreateCompatibleBitmap(pdc, Width(), Height());
//	m_pBmpColor->CreateBitmap(
//		Width(), Height(),
//		1,
//		24,
//		NULL);
	int iWidthAligned = (iw * 3 + 3) & ~3;
	int iHeight = ih;
	LPBYTE lpBitmap = new BYTE[iWidthAligned * iHeight];
	int iWidth = iw * 3;
	LPBYTE lpByte;
	int x, y;
	Color color;
	double dHue;
	double dLightness = 0.57;
	double dSaturation = 0.57;
	for(y = 0; y < iHeight; y++)
	{
		dHue = 4.0 / 6.0 * (1.0 - y / (double) iHeight);
		color.SetHLS(dHue, dLightness, dSaturation);
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
		pdc->GetSafeHdc(),
		m_bmpTemplate,
		0, iHeight,
		lpBitmap,
		&bmInfo,
		DIB_RGB_COLORS);
	delete lpBitmap;

   m_pFont = new gdi::Font();
	m_pFont->SetFont(new CFont());
	m_pFont->GetFont()->CreatePointFont(140, _T("Arial"));
	m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

   ReleaseDC(pdc);

}

void AudioSpectrumVirtualView::InstallMessageHandling(igui::win::message::Dispatch *pinterface)
{
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
/*xxx   aud::WaveCentral & wavecentral =
	aud::WaveCentralContainer::AppGetAudioWaveCentral();
   aud::WaveIn * pwavein = wavecentral.GetWaveIn();
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
      CRect rectClient;
      GetClientRect(rectClient);
	   VirtualGetWnd()->RedrawWindow(rectClient);
   }
}


void AudioSpectrumVirtualView::VirtualOnSize()
{
   CRect rect;
   GetClientRect(rect);
   Layout(rect);
}

