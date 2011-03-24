#include "StdAfx.h"
#include "resource.h"
#include "MidiTrackSelectView.h"

#include "MidiFile.h"
#include "MidiSequence.h"
#include "MidiTracks.h"
#include "Imaging.h"
//#include "GenericViewUpdateHint.h"
//#include "MenuCentral.h"
#include "FontCentral.h"
//#include "MenuV033.h"
#include "Savings.h"

#include "DBCentral.h"
#include "DBCentralContainer.h"

#include "_vmsdbMidiInstrumentSet.h"
//#include "ResourceCentral.h"

#include "MidiTrackSelectControlInterface.h"
#include "MidiTrackSelectDDX.h"
#include "MidiTrackSelectDoc.h"
#include "MidiTrackSelectViewUpdateHint.h"

#include "BaseRectArray.h"
#include "_vmsgenHighThread.h"
#include "_vmsgenHighThreadContainer.h"

CMidiTrackSelectView::CMidiTrackSelectView()
{
	m_penInstrument.CreatePen(PS_SOLID, 1, RGB(200, 200, 255));
	m_pmidisequence = NULL;
}

CMidiTrackSelectView::~CMidiTrackSelectView()
{
}


BEGIN_MESSAGE_MAP(CMidiTrackSelectView, BaseView)
	//{{AFX_MSG_MAP(CMidiTrackSelectView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER, OnUserMessage)
	ON_CONTROL_RANGE(BN_CLICKED, 100, 115, OnPushButtonTrackNoteOn)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMidiTrackSelectView message handlers

bool CMidiTrackSelectView::Initialize(MidiSequence * pmidisequence, bool bEnable)
{
	m_pmidisequence = pmidisequence;
	m_iaDisplayLevel.SetSize(16);
	m_iaRealLevel.SetSize(16);
	m_iaTimer.SetSize(16);
	m_recta.SetSize(16);
	m_rect2a.SetSize(16);
	m_iaLastLevel.SetSize(16);
	m_buttonaTrackNoteOn.SetSize(16);
	m_lineaInstrument.SetSize(16);
	m_iaInstrument.SetSize(16);
	
	for(int i = 0; i < m_rect2a.get_size(); i++)
	{
		m_rect2a.element_at(i).SetSize(11);
	}
	for(i = 0; i < m_lineaInstrument.get_size(); i++)
	{
		m_lineaInstrument.element_at(i).m_bVisible = true;
	}
	for(i = 0; i < m_buttonaTrackNoteOn.get_size(); i++)
	{
		if(!m_buttonaTrackNoteOn.element_at(i).Create(
			WS_VISIBLE
			| WS_CHILD,
			base_rect(0, 0, 0, 0),
			this,
			100 + i))
			return false;

	}
   
   if(!Enable(bEnable))
      return false;

   Layout();

   return true;

}

int CMidiTrackSelectView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (BaseView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if(!Enable())
		return -1;

/*	_vmsgen::CHighThread & highthread = _vmsgen::CHighThreadContainer::AppGetHighThread();
	highthread.CreateTimer(
		this,
		33,
		1);*/

	Layout();

	return 0;
}

void CMidiTrackSelectView::OnSize(UINT nType, int cx, int cy) 
{
	
	BaseView::OnSize(nType, cx, cy);

	Layout();
	
}

void CMidiTrackSelectView::GetUpperRect(LPRECT lprect, int iChannel)
{
	base_rect & rect = m_recta.element_at(iChannel);
	lprect->left = rect.left;
	lprect->right = rect.right;
	lprect->top = rect.top;
	lprect->bottom = (long) (rect.top + rect.Height() * GetRateComplement(iChannel));
}

void CMidiTrackSelectView::GetLowerRect(LPRECT lprect, int iChannel)
{
	base_rect & rect = m_recta.element_at(iChannel);
	lprect->left = rect.left;
	lprect->right = rect.right;
	lprect->bottom = rect.bottom;
	lprect->top = (long) (rect.bottom - rect.Height() * GetRate(iChannel));

}

void CMidiTrackSelectView::TwiOnDraw(CDC * pdc)
{
	base_rect rect;
	int i;

	base_rect rectClipBox;
	pdc->GetClipBox(rectClipBox);

   pdc->FillSolidRect(
      rectClipBox,
      RGB(72, 72, 72));

	base_rect rectIntersect;
	CVmsGdiFont * pfont = CFontCentral::AppGetFontCentral()->GetMidiTrackNameFont();
	base_rect rectClient;
	GetClientRect(rectClient);

	for(i = 0; i < m_lineaInstrument.get_size(); i++)
	{
		m_lineaInstrument[i].Render(
			pdc,
			//NULL,
			true,
			rectClient, 
			NULL_REF(BaseRectArray),
         false);
//			NULL,
//			pfont,
//			false,
//			RGB(200, 200, 255),
//			m_penInstrument);
	}

	RenderLevelMeter(pdc);
}

double CMidiTrackSelectView::GetRate(int iChannel)
{
	int iLevel = m_iaDisplayLevel.element_at(iChannel);
	return (double) iLevel / 127;
}

double CMidiTrackSelectView::GetRateComplement(int iChannel)
{
	int iLevel = 127 - m_iaDisplayLevel.element_at(iChannel);
	return (double) iLevel / 127;
}

void CMidiTrackSelectView::TimerProc(UINT uiIDEvent)
{
	SendMessage(WM_USER, WM_TIMER, uiIDEvent);
}

LRESULT CMidiTrackSelectView::OnUserMessage(WPARAM wParam, LPARAM lParam)
{
	if(wParam == WM_TIMER)
	{
		OnTimerProc(lParam);
	}

	return 0;
}

void CMidiTrackSelectView::OnTimerProc(UINT nIDEvent)
{
	if(nIDEvent == 1)
	{
		Update(true);
	}

}

void CMidiTrackSelectView::Update(bool bRedraw)
{
	if(IsEnabled())
	{
		CDC * pdc = GetDC();
		WString wstr;
		CVmsGdiFont * pfont = CFontCentral::AppGetFontCentral()->GetMidiTrackNameFont();
		if(m_pmidisequence == NULL)
			return;
		MidiFile & file = m_pmidisequence->GetFile();
		MidiTracks & tracks = file.GetTracks();
		base_rect rectClient;
		GetClientRect(rectClient);
		for(int i = 0; i < m_iaInstrument.get_size(); i++)
		{
			if(m_iaInstrument[i] != tracks.m_iaInstrument[i]
				|| m_lineaInstrument[i].m_wstr.IsEmpty())
			{
				m_iaInstrument[i] = tracks.m_iaInstrument[i];
				wstr.Empty();
   			DB()->GetMidiInstrumentSet()->GetName(m_iaInstrument[i], wstr);
				m_lineaInstrument[i].PrepareLine(
					pdc,
					wstr,
					0,
					rectClient);
			}
		}
		for(i = 0; i < m_buttonaTrackNoteOn.get_size(); i++)
		{
			SimplePushButton & button = m_buttonaTrackNoteOn.element_at(i);
			if(file.IsTrackMute(i))
			{
				if(!button.IsPushed())
				{
					button.Push();
				}
			}
			else
			{
				if(button.IsPushed())
				{
					button.Push(false);
				}
			}
		}
		int iRealLevel;
		int iDisplayLevel;
		int iTimer;
		for(i = 0; i < m_iaDisplayLevel.get_size(); i++)
		{
			iRealLevel = m_pmidisequence->m_iaLevel.element_at(i);
			iDisplayLevel = m_iaDisplayLevel.element_at(i);
			iTimer = m_iaTimer.element_at(i);
			if(iRealLevel > iDisplayLevel)
			{
				iTimer = 0;
				iDisplayLevel = iRealLevel;
			}
			else
			{
				iTimer++;
				if(iRealLevel > 0)
				{
					iDisplayLevel = iRealLevel;
				}
				else
				{

					if(iTimer > 5)
					{
						iDisplayLevel -= (int) (iTimer * .2);
						if(iRealLevel > iDisplayLevel)
							iDisplayLevel = iRealLevel;

					}
				}
			}
			m_iaDisplayLevel.element_at(i) =
				iDisplayLevel;
			m_iaTimer.element_at(i) = iTimer;

		}
		if(bRedraw)
		{
		
			base_rect rect;
			int i;
			int j;
			int iLevel;
			int iLastLevel;
			int jStart;
			int jEnd;

//			if(TwiIsValid())
			{
				for(i = 0; i < m_rect2a.get_size(); i++)
				{
					iLastLevel = m_iaLastLevel.element_at(i);
					iLevel = GetLowerLevel(i);
					jStart = min(iLastLevel, iLevel);
					jEnd = max(iLastLevel, iLevel);
					rect.SetRect(0, 0, 0, 0);
					for(j = jStart; j < jEnd; j++)
					{
						base_rect & rectj = m_rect2a.element_at(i).element_at(j);
						rect.UnionRect(rect, rectj);
					}
					RedrawWindow(rect);
					m_iaLastLevel.element_at(i) = iLevel;
				}
			}
				
		}
		ReleaseDC(pdc);
	}
}




void CMidiTrackSelectView::Layout()
{
	base_rect rectClient;
	GetClientRect(rectClient);
	int cx = rectClient.Width();
	int cy = rectClient.Height();

	const CSize sizeButton(50, 10);
	const CSize sizeExButton(54, 14);
	const CSize sizeInstrumentName(cx * 3 / 10, 10);
	const CSize sizeExInstrumentName(cx * 3 / 10 + 4, 14);
	CSize sizeLevelMeter;
	sizeLevelMeter.cx = cx - sizeExButton.cx - sizeExInstrumentName.cx;
	sizeLevelMeter.cy = cy;
	const double cdGapX = 1.0;
	const double cdGapY = 3.0;
	double dx = 0.0;
	double dh = (sizeLevelMeter.cy - cdGapY * (m_recta.get_size() - 1)) / m_recta.get_size();
	double dw = 0.0;
	if(m_rect2a.get_size() > 0)
	{
		int iSize = m_rect2a.element_at(0).get_size();
		dw = (sizeLevelMeter.cx - cdGapX * (iSize - 1)) / iSize;
	}
	int i;
	double dy = 0;
	int left = 0;
	for(i = 0; i < m_buttonaTrackNoteOn.get_size(); i++)
	{
		base_rect & recti = m_recta.element_at(i);
		recti.top = (int) dy;
		recti.bottom = (int) (dy + dh);
		recti.left = left;
		recti.right = left + sizeExButton.cx;
		dy += dh + cdGapY;
		m_buttonaTrackNoteOn[i].SetWindowPos(
			&wndTop,
			recti.left,
			recti.top,
			recti.Width(),
			recti.Height(),
			SWP_SHOWWINDOW);
	}
	dy = 0;
	left += sizeExButton.cx;
	base_rect rectx;

	for(i = 0; i < m_lineaInstrument.get_size(); i++)
	{
		rectx.top = (int) dy;
		rectx.bottom = (int) (dy + dh);
		rectx.left = left;
		rectx.right = left + sizeExInstrumentName.cx;
		dy += dh + cdGapY;
		m_lineaInstrument.element_at(i).SetPlacement(rectx);
	}
	left += sizeExInstrumentName.cx;
	dy = 0;
	m_rectLevelMeter.left = left;
	m_rectLevelMeter.right = rectClient.right;
	m_rectLevelMeter.top = rectClient.top;
	m_rectLevelMeter.bottom = rectClient.bottom;
	for(i = 0; i < m_recta.get_size(); i++)
	{
		base_rect & recti = m_recta.element_at(i);
		recti.top = (int) dy;
		recti.bottom = (int) (dy + dh);
		recti.left = left;
		recti.right = left + sizeLevelMeter.cx;
		dy += dh + cdGapY;
		//dx = left + sizeLevelMeter.cx;
		dx = left;
		for(int j = 0; j < m_rect2a.element_at(i).get_size(); j++)
		{
			base_rect & rectj = m_rect2a.element_at(i).element_at(j);
			rectj.top = recti.top ;
			rectj.bottom = recti.bottom ;
			rectj.left = (long) (dx - dw);
			rectj.right = (long) (dx);
			//dx -= dw + cdGapX;
			dx += dw + cdGapX;
		}
	}

	base_rect rectLevelMeter(m_rectLevelMeter);
	int iw = rectLevelMeter.Width();
	int ih = rectLevelMeter.Height();

	CDC * pdc = GetDC();

	m_dcBack.DeleteDC();

	m_bmpBack.DeleteObject();
	m_bmpBack.CreateCompatibleBitmap(
		pdc,
		iw, ih);


	m_dcBack.CreateCompatibleDC(pdc);
	m_dcBack.SelectObject(&m_bmpBack);

//	m_pBmpColor->CreateCompatibleBitmap(pDC, Width(), Height());
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
	CColor color;
	double dHue;
	double dLightness = 0.67;
	double dSaturation = 0.77;
	for(x = 0; x < iWidth; x += 3)
	{
		dHue = 4.0 / 6.0 * (1.0 - x / (double) iWidth);
		color.SetHLS(dHue, dLightness, dSaturation);
		for(y = 0; y < iHeight; y++)
		{
			lpByte = lpBitmap + y * iWidthAligned + x;
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
		m_bmpBack,
		0, iHeight,
		lpBitmap,
		&bmInfo,
		DIB_RGB_COLORS);
	delete lpBitmap;

	ReleaseDC(pdc);

}

int CMidiTrackSelectView::GetLowerLevel(int iChannel)
{
	int iLevel = 0;
	if(m_rect2a.get_size() > 0)
	{
		int iSize = m_rect2a.element_at(0).get_size() + 1;
		iLevel = (int) (GetRate(iChannel) * iSize);
		if(iLevel == iSize)
			iLevel--;
	}
	return iLevel;
}

void CMidiTrackSelectView::OnDestroy() 
{
	PointerInterfaceClearReferences();
	BaseView::OnDestroy();
	
/*	_vmsgen::CHighThread & highthread =
		_vmsgen::CHighThreadContainer::AppGetHighThread();
    highthread.DeleteTimerWnd(m_ptimerwnd);*/

	//GetParent()->SendMessage(APPM_NOTIFY, APPN_CHILDDELETE, (LPARAM) this);

//	TwiEnable(false);
	//TwiRedraw();
	
}

void CMidiTrackSelectView::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	BaseView::PostNcDestroy();
}

bool CMidiTrackSelectView::Enable(bool bEnable)
{
	m_bEnabled = bEnable;
	return true;
}

bool CMidiTrackSelectView::IsEnabled()
{
	return m_bEnabled;
}

void CMidiTrackSelectView::OnUpdate(view* pSender, LPARAM lHint, base_object* phint) 
{
/*	if(pHint != NULL &&
		pHint->IsKindOf(RUNTIME_CLASS(CGenericViewUpdateHint)))
	{
		CGenericViewUpdateHint * puh = (CGenericViewUpdateHint *) pHint;
		if(puh->m_iParamA == 8791)
		{
			Initialize((CMidiSequence *) puh->m_pvoid, true);
		}
	}*/
	if(phint != NULL)
   {
      if(phint->IsKindOf(RUNTIME_CLASS(CMidiTrackSelectViewUpdateHint)))
	   {
		   CMidiTrackSelectViewUpdateHint * puh = (CMidiTrackSelectViewUpdateHint *) phint;
         if(puh->GetType() == CMidiTrackSelectViewUpdateHint::TypeInitialize)
		   {
			   puh->m_bResult = Initialize(puh->m_pmidisequence, true);
		   }
	   }
   }
	
}

void CMidiTrackSelectView::_001OnDraw(CDC* pdc) 
{
   TwiOnDraw(pdc);
}

void CMidiTrackSelectView::OnContextMenu(uie* pWnd, point point) 
{
//    CMenuV033 menu(CMenuCentral::GetMenuCentral());
/*	if (menu.LoadMenu(IDR_POPUP_LEVELMETER))
	{
		CMenuV033* pPopup = (CMenuV033 *) menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
        CFrameWnd * pframe = GetParentFrame();
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			point.x, point.y,
			(uie *) pframe);
	}*/
	
}

void CMidiTrackSelectView::OnPushButtonTrackNoteOn(UINT nID)
{
	int i = nID - 100;

   CMidiTrackSelectDoc * pdoc = (CMidiTrackSelectDoc *) get_document();
   pdoc->m_pddx->m_pcontrol->OnSelectTrack(i);

	/*bool bMute = m_pmidisequence->GetFile().IsTrackMute(i);
	if(bMute)
	{
		m_pmidisequence->GetFile().MuteTrack(i, false);
	}
	else
	{
		m_pmidisequence->GetFile().MuteTrack(i);
	}*/
	Update(true);
}

void CMidiTrackSelectView::UpdatePushButtonMute(int iIndex)
{
	SimplePushButton & button = m_buttonaTrackNoteOn[iIndex];
	button.Push(m_pmidisequence->GetFile().IsTrackMute(iIndex));
}

void CMidiTrackSelectView::RenderLevelMeter(CDC *pdc)
{
	base_rect rect;
	base_rect rectIntersect;
	base_rect rectClipBox;
	pdc->GetClipBox(rectClipBox);
	int iLevel;
	int j;
	base_rect rectLevelMeter(m_rectLevelMeter);

	CSavings & savings = CSavings::AppGetSavings();

	bool bSaveProcessing = savings.SavingsSaveWhat().IsSignalized(CSavings::SaveProcessing);

	for(int i = 0; i < m_rect2a.get_size(); i++)
	{
		rect = m_recta.element_at(i);
		if(!rectIntersect.IntersectRect(rectClipBox, rect))
			continue;


		iLevel = GetLowerLevel(i);
		if(!bSaveProcessing)
		{
			for(j = 0; j < iLevel && j < 12; j++)
			{
				base_rect & rectj = m_rect2a.element_at(i).element_at(j);
				if(!rectIntersect.IntersectRect(rectClipBox, rectj))
					continue;
				pdc->BitBlt(rectj.left, rectj.top, rectj.Width(), rectj.Height(),
					&m_dcBack, rectj.left - rectLevelMeter.left, rectj.top - rectLevelMeter.top, SRCCOPY);
			}
		}
		else
		{

			for(j = 0; j < iLevel && j < 5; j++)
			{
				base_rect & rectj = m_rect2a.element_at(i).element_at(j);
				if(!rectIntersect.IntersectRect(rectClipBox, rectj))
					continue;
				pdc->FillSolidRect(rectj, RGB(50, 100, 200));
			}
			for(;j < iLevel && j < 10; j++)
			{
				base_rect & rectj = m_rect2a.element_at(i).element_at(j);
				if(!rectIntersect.IntersectRect(rectClipBox, rectj))
					continue;
				pdc->FillSolidRect(rectj, RGB(200, 50, 100));
			}
			for(;j < iLevel && j < 12; j++)
			{
				base_rect & rectj = m_rect2a.element_at(i).element_at(j);
				if(!rectIntersect.IntersectRect(rectClipBox, rectj))
					continue;
				pdc->FillSolidRect(rectj, RGB(255, 255, 100));
			}
		}

	}


}
