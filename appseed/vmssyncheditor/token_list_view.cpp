#include "StdAfx.h"

namespace vmssyncheditor
{

   token_list_view::token_list_view(::ca::application * papp) :
      ::ca::ca(papp),
         Ex1ScrollViewInterface(papp),
         ex1::form_interface(papp),
         Ex1ListInterface(papp),
         Ex1FormListInterface(papp),
         SimpleFormListView(papp)
   {
      m_dataid = "vmssyncheditor::token_list_view";
      
      //EnableBuffering(true);

   }

token_list_view::~token_list_view()
{
}

/*

BEGIN_MESSAGE_MAP(token_list_view, SimpleFormListView)
	//{{AFX_MSG_MAP(token_list_view)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

#ifdef _DEBUG
void token_list_view::AssertValid() const
{
	SimpleFormListView::AssertValid();
}

void token_list_view::Dump(CDumpContext& dc) const
{
	SimpleFormListView::Dump(dc);
}
document* token_list_view::get_document() // non-debug version is inline
{
   ASSERT(base<document>::bases(m_pDocument));
	return dynamic_cast < document* > (m_pDocument);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// token_list_view message handlers

void token_list_view::_001InsertColumns()
{
   Ex1FormInterfaceControl control;

	Column column;

   control.SetType(Ex1FormInterfaceControl::TypeEdit);
   control.m_dataid = document::ConfigIdStartPosition;
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);


   int iControl =  _001AddControl(control);

   column.m_iWidth = 100;
   //column.m_uiText = IDS_SYNCH_EDITOR_TOKEN_LIST_START_POSITION;
   column.m_iSubItem = 0;
	//column.m_uiSmallBitmap = IDB_ALBUM_SMALL_256;
   column.m_iSmallImageWidth = 16;
   column.m_crSmallMask = RGB(255, 0, 255);
   column.m_iControl = iControl;
   column.m_datakey = document::ConfigIdStartPosition;
   _001AddColumn(column);

   control.SetType(Ex1FormInterfaceControl::TypeEdit);
   control.m_dataid = document::ConfigIdEndPosition;
   //control.m_uiId = document::ConfigIdEndPosition;
   control.SetDataType(Ex1FormInterfaceControl::DataTypeNatural);

   iControl = _001AddControl(control);

   //column.m_uiText = IDS_SYNCH_EDITOR_TOKEN_LIST_END_POSITION;
   column.m_iWidth = 100;
   column.m_iSubItem = 1;
   column.m_iControl = iControl;
   column.m_datakey = document::ConfigIdEndPosition;
   _001AddColumn(column);


   control.SetType(Ex1FormInterfaceControl::TypeEdit);
   control.AddFunction(Ex1FormInterfaceControl::FunctionSaveOnChange);
   control.m_dataid = document::ConfigIdToken;
   //control.m_uiId = document::ConfigIdToken;
   control.SetDataType(Ex1FormInterfaceControl::DataTypeString);

   iControl = _001AddControl(control);

   //column.m_uiText = IDS_SYNCH_EDITOR_TOKEN_LIST_TEXT;
   column.m_iWidth = 400;
   column.m_iSubItem = 2;
   column.m_iControl = iControl;
   column.m_datakey = document::ConfigIdToken;
   _001AddColumn(column);

}


bool token_list_view::_001GetItemText(string &wstr, int iItem, int iSubItem, int iListItem)
{
   if(Ex1ListInterface::_001GetItemText(
      wstr,
      iItem, 
      iSubItem, 
      iListItem))
   {
      return true;
   }
   if(iSubItem == 0)
   {
            EventsTracksV1 * peventsarray
            = &get_document()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_eventsTracksForPositionCB;

      LyricEventsV2 * pevents;
      if(peventsarray == NULL ||
         peventsarray->get_size() <= 0)
         pevents = NULL;
      else
      {
   //      pevents = (LyricEventsV2 *) peventsarray->operator [](staticdata.m_str2aRawTokens.get_size());
         pevents = (LyricEventsV2 *) peventsarray->element_at(0);
         ASSERT(pevents != NULL);
         ASSERT(pevents->GetClassOrder() == 2);
      }

      if(pevents != NULL && iItem < pevents->m_tkaTokensPosition.get_size())
      {
         wstr.Format("%d", pevents->m_tkaTokensPosition[iItem]);
      }
   }
   else if(iSubItem == 2)
   {
      if(get_document()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens.get_size() > 0)
      {
         if(iItem < get_document()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens[0].get_size())
         {
            wstr = get_document()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens[0][iItem];
         }
      }
   }
	return true;
}

void token_list_view::_001OnInitialUpdate(gen::signal_object * pobj) 
{
	SimpleFormListView::_001OnInitialUpdate(pobj);

   initialize(get_document());

   _001UpdateColumns();

	
}

int token_list_view::_001GetItemCount()
{
   BaseAStr2DArray & str2aTokens = get_document()->GetMediaViewData()->GetKaraokeData().GetStaticData().m_str2aRawTokens;

   if(str2aTokens.get_size() > 0)
   {
      return str2aTokens[0].get_size();
   }
   else
   {
      return 0;
   }
}

void token_list_view::OnUpdate(view* pSender, LPARAM lHint, base_object* pHint) 
{
   if(lHint == 101)
   {
      _001HideEditingControls();
      _001Highlight(get_document()->m_iCurrentToken, false);
      _001EnsureVisible(get_document()->m_iCurrentToken);

   }
}



void token_list_view::_001OnClick(UINT uiFlags, point point, int iItem, int iSubItem)
{
   SimpleFormListView::_001OnClick(
      uiFlags, point, iItem, iSubItem);

   get_document()->m_iCurrentToken = iItem;
   get_document()->UpdateAllViews(this, 13, 0);
}

void token_list_view::data_on_after_change(gen::signal_object * pobj)
{
   SCAST_PTR(idb::event::data_change, pchange, pobj);
   SimpleFormListView::data_on_after_change(pobj);
   if(pchange->m_dataidKey == document::ConfigIdToken)
   {
/*      CSynchEditorViewUpdateHint uh;
      uh.m_etype = CSynchEditorViewUpdateHint::TypeConfigIdUpdate;
      uh.m_iConfigId = iConfigId;
      uh.m_iToken = 
      get_document()->UpdateAllViews(NULL, 121);*/
   }

}

bool token_list_view::_001OnMessageNotify(WPARAM wparam, LPARAM lparam, LRESULT & lresult)
{

   Ex1FormInterfaceControl & control = m_controla.GetControlById(wparam);

   if(control.IsNull())
      return true;

   /*igui::Notify * pnotify = (igui::Notify *) lparam;

   switch(control.GetType())
   {
   case Ex1FormInterfaceControl::TypeEdit:
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
                  string str;
                  pedit->GetWindowText(str);
                  int iLength = str.GetLength();
                  if(iStart == iEnd && iStart <= iLength)
                  {
                     pedit->SetWindowText(str.Left(iStart));
                     _001SaveEdit(control);
                     string strSwap;
                     data_update_hint uh;
                     uh.GetUpdateFlags().Signalize(data_update_hint::UpdateInternal);
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
                  string str;
                  pedit->GetWindowText(str);
                  int iLength = str.GetLength();
                  if(iStart == iEnd && iStart == iLength)
                  {
                     data_update_hint uh;
                     uh.GetUpdateFlags().Signalize(data_update_hint::UpdateInternal);
                     uh.AddSelf(this);
                     string strNext;
                     GetToken(control.GetEditItem() + 1, strNext);
                     str += strNext;
                     int iItemCount = _001GetItemCount() - 1;
                     string strSwap;
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
                  string str;
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
                        data_update_hint uh;
                        uh.GetUpdateFlags().Signalize(data_update_hint::UpdateInternal);
                        uh.AddSelf(this);
                        string strPrevious;
                        GetToken(control.GetEditItem() - 1, strPrevious);
                        int iPreviousLength = strPrevious.GetLength();
                        str = strPrevious + str;
                        int iItemCount = _001GetItemCount() - 1;
                        string strSwap;
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
   }*/
   
   return true;
}


bool token_list_view::GetToken(int i, string &str)
{
   gen::variable var;
   if(data_get(document::ConfigIdToken, i, var))
   {
      str = var.get_string();
      return true;
   }
   return false;
}

bool token_list_view::SetToken(int i, LPCTSTR lpcsz,
data_update_hint * puh)
{
   return data_set(document::ConfigIdToken, i, lpcsz, puh);

}

} // namespace vmssyncheditor