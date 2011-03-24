// SynchEditorTokenListView.cpp : implementation file
//

#include "stdafx.h"
#include "vmssyncheditor.h"
#include "SynchEditorTokenListView.h"

#include "_vmssyncheditorDoc.h"

#include "_vmsguiNotify.h"
#include "_vmsguiNotifyKey.h"

#include "VmsDataUpdateHint.h"


#include "_vmsmediaplayMediaViewData.h"

#include "KaraokeData.h"
#include "KaraokeStaticData.h"
#include "LyricEventsV2.h"

#include "MidiTracks.h"
#include "International.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorTokenListView

IMPLEMENT_DYNCREATE(CSynchEditorTokenListView, SimpleFormListView)

CSynchEditorTokenListView::CSynchEditorTokenListView()
{
   DISetSection(GetRuntimeClass()->m_lpszClassName);
   
   EnableBuffering(true);

}

CSynchEditorTokenListView::~CSynchEditorTokenListView()
{
}


BEGIN_MESSAGE_MAP(CSynchEditorTokenListView, SimpleFormListView)
	//{{AFX_MSG_MAP(CSynchEditorTokenListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorTokenListView drawing

void CSynchEditorTokenListView::OnDraw(CDC* pDC)
{
	Document* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorTokenListView diagnostics

#ifdef _DEBUG
void CSynchEditorTokenListView::AssertValid() const
{
	SimpleFormListView::AssertValid();
}

void CSynchEditorTokenListView::Dump(CDumpContext& dc) const
{
	SimpleFormListView::Dump(dc);
}
_vmssyncheditorDoc* CSynchEditorTokenListView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(_vmssyncheditorDoc)));
	return (_vmssyncheditorDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSynchEditorTokenListView message handlers

void CSynchEditorTokenListView::_001InsertColumns()
{
   BaseFormInterfaceControl control;

	Column column;

   control.SetType(BaseFormInterfaceControl::TypeEdit);
   control.m_datakey = _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdStartPosition);
   control.m_uiId = _vmssyncheditorDoc::ConfigIdStartPosition;
   control.SetDataType(BaseFormInterfaceControl::DataTypeNatural);


   int iControl =  _001AddControl(control);

   column.m_iWidth = 100;
   column.m_uiText = IDS_SYNCH_EDITOR_TOKEN_LIST_START_POSITION;
   column.m_iSubItem = 0;
	//column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
   column.m_iSmallImageWidth = 16;
   column.m_crSmallMask = RGB(255, 0, 255);
   column.m_iControl = iControl;
   column.m_datakey = _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdStartPosition);
   _001AddColumn(column);

   control.SetType(BaseFormInterfaceControl::TypeEdit);
   control.m_datakey = _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdEndPosition);
   control.m_uiId = _vmssyncheditorDoc::ConfigIdEndPosition;
   control.SetDataType(BaseFormInterfaceControl::DataTypeNatural);

   iControl = _001AddControl(control);

   column.m_uiText = IDS_SYNCH_EDITOR_TOKEN_LIST_END_POSITION;
   column.m_iWidth = 100;
   column.m_iSubItem = 1;
   column.m_iControl = iControl;
   column.m_datakey = _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdEndPosition);
   _001AddColumn(column);


   control.SetType(BaseFormInterfaceControl::TypeEdit);
   control.AddFunction(BaseFormInterfaceControl::FunctionSaveOnChange);
   control.m_datakey = _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdToken);
   control.m_uiId = _vmssyncheditorDoc::ConfigIdToken;
   control.SetDataType(BaseFormInterfaceControl::DataTypeString);

   iControl = _001AddControl(control);

   column.m_uiText = IDS_SYNCH_EDITOR_TOKEN_LIST_TEXT;
   column.m_iWidth = 400;
   column.m_iSubItem = 2;
   column.m_iControl = iControl;
   column.m_datakey = _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdToken);
   _001AddColumn(column);

}


bool CSynchEditorTokenListView::_001GetItemText(WString &wstr, int iItem, int iSubItem, int iListItem)
{
   if(BaseListInterface::_001GetItemText(
      wstr,
      iItem, 
      iSubItem, 
      iListItem))
   {
      return true;
   }
   if(iSubItem == 0)
   {
            CEventsTracksV1 * peventsarray
            = &GetDocument()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_eventsTracksForPositionCB;

      LyricEventsV2 * pevents;
      if(peventsarray == NULL ||
         peventsarray->GetSize() <= 0)
         pevents = NULL;
      else
      {
   //      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.GetSize());
         pevents = (LyricEventsV2 *) peventsarray->ElementAt(0);
         ASSERT(pevents != NULL);
         ASSERT(pevents->GetClassOrder() == 2);
      }

      if(pevents != NULL && iItem < pevents->m_tkaTokensPosition.GetSize())
      {
         wstr.Format(L"%d", pevents->m_tkaTokensPosition[iItem]);
      }
   }
   else if(iSubItem == 2)
   {
      if(GetDocument()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens.GetSize() > 0)
      {
         if(iItem < GetDocument()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens[0].GetSize())
         {
            International::ACPToUnicode(wstr, GetDocument()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens[0][iItem]);
         }
      }
   }
	return true;
}

void CSynchEditorTokenListView::OnInitialUpdate() 
{
	SimpleFormListView::OnInitialUpdate();

   VmsDataInitialize(GetDocument());

   GetDocument()->AddClient(this);
	
   _001UpdateColumns();

   RedrawWindow();


	
}

void CSynchEditorTokenListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
   if(lHint == 100)
   {
      _vmssyncheditorDoc * pdoc = GetDocument();

      BaseAStr2DArray & str2aTokens = GetDocument()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens;

      if(str2aTokens.GetSize() > 0)
      {
         _001SetItemCountEx(str2aTokens[0].GetSize());
      }
      else
      {
         _001SetItemCountEx(0);
      }
   }
   else if(lHint == 101)
   {
      _001HideEditingControls();
      _001Highlight(GetDocument()->m_iCurrentToken, false);
      _001EnsureVisible(GetDocument()->m_iCurrentToken);

   }
}



void CSynchEditorTokenListView::_001OnClick(UINT uiFlags, CPoint point, int iItem, int iSubItem)
{
   SimpleFormListView::_001OnClick(
      uiFlags, point, iItem, iSubItem);

   GetDocument()->m_iCurrentToken = iItem;
   GetDocument()->UpdateAllViews(this, 13, 0);
}

void CSynchEditorTokenListView::VmsDataOnAfterChange(
   const VmsDataKeyInterface & key, 
   int iLine, 
   int iColumn, 
   VmsDataUpdateHint * puh)
{
   SimpleFormListView::VmsDataOnAfterChange(
      key,
      iLine, iColumn, puh);
//   if(iConfigId == _vmssyncheditorDoc::ConfigIdToken)
   {
/*      CSynchEditorViewUpdateHint uh;
      uh.m_etype = CSynchEditorViewUpdateHint::TypeConfigIdUpdate;
      uh.m_iConfigId = iConfigId;
      uh.m_iToken = 
      GetDocument()->UpdateAllViews(NULL, 121);*/
   }

}

bool CSynchEditorTokenListView::_001OnMessageNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
{

   BaseFormInterfaceControl & control = m_controla.GetControlById(wparam);

   if(control.IsNull())
      return true;

   _vmsguiNotify * pnotify = (_vmsguiNotify *) lparam;

   switch(control.GetType())
   {
   case BaseFormInterfaceControl::TypeEdit:
      switch(pnotify->m_uiCode)
      {
      case _vmsgui::NotifyKeyDown:
         {
            _vmsguiNotifyKey * pkey = (_vmsguiNotifyKey *) pnotify;
            switch(pkey->m_uiVKey)
            {
            case VK_RETURN:
               {
                  CEdit * pedit = (CEdit *) control.m_pwnd;
                  int iStart;
                  int iEnd;
                  pedit->GetSel(iStart, iEnd);
                  CString str;
                  pedit->GetWindowText(str);
                  int iLength = str.GetLength();
                  if(iStart == iEnd && iStart <= iLength)
                  {
                     pedit->SetWindowText(str.Left(iStart));
                     _001SaveEdit(control);
                     CString strSwap;
                     VmsDataUpdateHint uh;
                     uh.GetUpdateFlags().Signalize(VmsDataUpdateHint::UpdateInternal);
                     uh.AddSelf(this);
                     int iItemEnd = control.GetEditItem() + 1;
                     for(int iItem = _001GetItemCount() - 1; iItem > iItemEnd; iItem--)
                     {
                        GetToken(iItem - 1, strSwap);
                        SetToken(iItem, strSwap, &uh);
                     }
                     SetToken(control.GetEditItem() + 1, str.Mid(iStart));
                     _001Select(control.GetEditItem() + 1, control.GetEditSubItem());
                     _001PlaceControl(control, control.GetEditItem() + 1, control.GetEditSubItem());
                     pedit->SetSel(0, 0);
                     RedrawWindow();
                  }
                  else
                  {
                     _001SaveEdit(control);
                  }
                  pkey->m_bDefault = false;
               }
               break;
            case VK_DELETE:
               {
                  CEdit * pedit = (CEdit *) control.m_pwnd;
                  int iStart;
                  int iEnd;
                  pedit->GetSel(iStart, iEnd);
                  CString str;
                  pedit->GetWindowText(str);
                  int iLength = str.GetLength();
                  if(iStart == iEnd && iStart == iLength)
                  {
                     VmsDataUpdateHint uh;
                     uh.GetUpdateFlags().Signalize(VmsDataUpdateHint::UpdateInternal);
                     uh.AddSelf(this);
                     CString strNext;
                     GetToken(control.GetEditItem() + 1, strNext);
                     str += strNext;
                     int iItemCount = _001GetItemCount() - 1;
                     CString strSwap;
                     for(int iItem = control.GetEditItem() + 1; iItem < iItemCount; iItem++)
                     {
                        GetToken(iItem + 1, strSwap);
                        SetToken(iItem, strSwap, &uh);
                     }
                     SetToken(control.GetEditItem(), str);
                     _001Select(control.GetEditItem(), control.GetEditSubItem());
                     _001PlaceControl(control, control.GetEditItem(), control.GetEditSubItem());
                     RedrawWindow();
                     pkey->m_bDefault = false;
                  }
                  else
                  {
                     _001SaveEdit(control);
                  }
               }
               break;
            case VK_BACK:
               {
                  CEdit * pedit = (CEdit *) control.m_pwnd;
                  int iStart;
                  int iEnd;
                  pedit->GetSel(iStart, iEnd);
                  CString str;
                  pedit->GetWindowText(str);
                  int iLength = str.GetLength();
                  if(iStart == iEnd && iStart == 0)
                  {
                     // go to previous cell.
                     if(control.GetEditItem() == 0)
                     {
                        // there is no previous cell
                        MessageBeep(-1);
                     }
                     else
                     {
                        VmsDataUpdateHint uh;
                        uh.GetUpdateFlags().Signalize(VmsDataUpdateHint::UpdateInternal);
                        uh.AddSelf(this);
                        CString strPrevious;
                        GetToken(control.GetEditItem() - 1, strPrevious);
                        int iPreviousLength = strPrevious.GetLength();
                        str = strPrevious + str;
                        int iItemCount = _001GetItemCount() - 1;
                        CString strSwap;
                        for(int iItem = control.GetEditItem(); iItem < iItemCount; iItem++)
                        {
                           GetToken(iItem + 1, strSwap);
                           SetToken(iItem, strSwap, &uh);
                        }
                        SetToken(control.GetEditItem() - 1, str);
                        _001Select(control.GetEditItem() - 1, control.GetEditSubItem());
                        _001PlaceControl(control, control.GetEditItem() - 1, control.GetEditSubItem());
                        pedit->SetSel(iPreviousLength, iPreviousLength);
                        RedrawWindow();
                     }
                  }
                  else
                  {
                     _001SaveEdit(control);
                  }
                  lresult &= ~_vmsgui::NotifyRetContinue;
               }
               break;
            }
         }
         break;
      }
      break;
   }
   
   return true;
}


bool CSynchEditorTokenListView::GetToken(int i, CString &str)
{
   return VmsDataGet(
      _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdToken),
      i, 0, str);

}

bool CSynchEditorTokenListView::SetToken(int i, LPCTSTR lpcsz,
VmsDataUpdateHint * puh)
{
   return VmsDataSet(
      _vmssyncheditorDoc::VmsDataKey(_vmssyncheditorDoc::ConfigIdToken),
      i, 0, lpcsz, puh);

}
