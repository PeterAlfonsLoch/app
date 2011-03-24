#include "StdAfx.h"
#include "ToolV023Dialog.h"

#include "AlbumMainView.h"
#include "AlbumFrameWnd.h"

#include "XfplayerDoc.h"

CToolV023Dialog::CToolV023Dialog(::ca::application * papp) :
   ca(papp),
   ::user::scroll_view(papp),
   ::userbase::view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   form(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   dialog(papp)
{
   m_pwndCloseWindow = NULL;
   m_pobjSource = NULL;
}


/*
void CToolV023Dialog::DoDataExchange(CDataExchange* pDX)
{
//   dialog::DoDataExchange(pDX);
}
*/


/////////////////////////////////////////////////////////////////////////////
// CToolV023Dialog message handlers


/*afx_msg void CToolV023Dialog::OnKeyDownEdit(_vmsgui::NMHDR * pNotifyStruct, LRESULT * result )
{
   _vmsgui::EDIT_KEYINFO  & nmkey = *(_vmsgui::EDIT_KEYINFO*)pNotifyStruct;
    if(nmkey.wVKey == VK_RETURN)
    {
 /*       simple_edit * pEdit = (simple_edit *) pEdit->from_handle(nmkey.hdr.hwndFrom);
        string str;
        pEdit->GetWindowText(str);
        const char * lpcsz = str;
        LPTSTR lpend;
        long lValue = _tcstol(lpcsz, &lpend, 10);
        LPTSTR lpnull;
        lpnull = _tcschr(lpcsz, NULL);
        if(lpend != lpcsz &&
            lpend == lpnull)
        {
            pEdit->ShowWindow(SW_HIDE);
            pEdit->clear();
            vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
            XfplayerDoc * pPlayerDoc  = pApp->GetPlayerDocument();
            if(pPlayerDoc != NULL)
            {
                XfplayerView * pLyricView = pPlayerDoc->GetLyricView();
                if(pLyricView != NULL)
                {
                    PlaylistDoc * pPlaylistDoc = pLyricView->GetPlaylistDoc();
                    if(pPlaylistDoc == NULL)
                    {
                        ::userbase::multiple_document_template * pPlaylistDocTemplate = pApp->GetPlaylistDocTemplate();
                        pPlaylistDoc
                         = (PlaylistDoc *) pPlaylistDocTemplate->open_document_file(NULL);
                        pLyricView->AttachPlaylistDoc(pPlaylistDoc);
                    }
                    pPlaylistDoc->AddSong(lValue);
                    pPlaylistDoc->update_all_views(NULL);
//                     CMainFrame *pFrame = (CMainFrame *) pApp->GetMainWnd();
//                   pFrame->UpdateReserveList();
                }
            }
        }
        else
        {

        } */
        /**result = 0;
    }
    else if(nmkey.wVKey == VK_ESCAPE)
    {
        PostMessage(WM_CLOSE);
        *result = 0;
    }
    else if(nmkey.wVKey == VK_NUMPAD0 ||
        nmkey.wVKey == VK_NUMPAD1 ||
        nmkey.wVKey == VK_NUMPAD2 ||
        nmkey.wVKey == VK_NUMPAD3 ||
        nmkey.wVKey == VK_NUMPAD4 ||
        nmkey.wVKey == VK_NUMPAD5 ||
        nmkey.wVKey == VK_NUMPAD6 ||
        nmkey.wVKey == VK_NUMPAD7 ||
        nmkey.wVKey == VK_NUMPAD8 ||
        nmkey.wVKey == VK_NUMPAD9 ||
        nmkey.wVKey == '0' ||
        nmkey.wVKey == '1' ||
        nmkey.wVKey == '2' ||
        nmkey.wVKey == '3' ||
        nmkey.wVKey == '4' ||
        nmkey.wVKey == '5' ||
        nmkey.wVKey == '6' ||
        nmkey.wVKey == '7' ||
        nmkey.wVKey == '8' ||
        nmkey.wVKey == '9')
    {
        *result = 0;
    }
    else
    {
//        MessageBeep(MB_OK);
        *result = -1;
    }
}*/

afx_msg LRESULT CToolV023Dialog::OnVMSNotify(WPARAM wParam, LPARAM lParam)
{
    LRESULT lresult;
/*    _vmsgui::NMHDR * lpnmhdr = (_vmsgui::NMHDR *) lParam;
    if(wParam == IDC_EDIT)
    {
        if(lpnmhdr->code == E17N_KEYDOWN)
        {
            OnKeyDownEdit(lpnmhdr, &lresult);
            return lresult;
        }
//        else if(lpnmhdr->code == E17N_SYSKEYDOWN)
  //      {
    //        OnSysKeyDownEdit(lpnmhdr, &lresult);
      //      return lresult;
        //}


    }
    else
    {
        ASSERT(FALSE);
    }*/
    return -1;
}

void CToolV023Dialog::OnClose() 
{
   // TODO: add your message handler code here and/or call default

//   dialog::OnClose();

    if(m_pwndCloseWindow != NULL)
        m_pwndCloseWindow->BringWindowToTop();
    DestroyWindow();
    
}

BOOL CToolV023Dialog::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   cs.style &= ~WS_CAPTION;
//   return dialog::PreCreateWindow(cs);
   return FALSE;
}

void CToolV023Dialog::OnOK()
{
/*    simple_edit * pEdit = dynamic_cast < simple_edit * > (this->GetDlgItem(IDC_EDIT));
    string str;
    pEdit->GetWindowText(str);
    const char * lpcsz = str;
    LPTSTR lpend;
    long lValue = _tcstol(lpcsz, &lpend, 10);
    const char * lpnull;
    lpnull = _tcschr(lpcsz, NULL);
    vmsp::application *pApp = dynamic_cast < vmsp::application * > (&System);
   musctrl::MusicalPlayerCentral & playercentral =
      musctrl::MusicalPlayerCentral::AppGetMusicalPlayerCentral(get_app());
   musctrl::single_document_template * pdoctemplate =
      playercentral.get_document_template();
    if(lpend != lpcsz &&
        lpend == lpnull)
    {
//        pEdit->ShowWindow(SW_HIDE);
//        pEdit->clear();
        if(m_pobjSource == NULL ||
            base < XfplayerDoc >::bases(m_pobjSource))
        {
            XfplayerDoc * pPlayerDoc;
            if(m_pobjSource != NULL)
                pPlayerDoc = dynamic_cast < XfplayerDoc * > (m_pobjSource);
            else
                pPlayerDoc = dynamic_cast < XfplayerDoc * > (pdoctemplate->get_document(0));
            if(pPlayerDoc != NULL)
            {
                PlaylistDoc * pPlaylistDoc = pPlayerDoc->GetPlaylistDoc();
                if(pPlaylistDoc == NULL)
                {
                     PlaylistCentral & playlistcentral = PlaylistCentral::AppGetPlaylistCentral(get_app());
                        pPlaylistDoc = playlistcentral.OpenPlaylist(NULL, false, true);
                        pPlayerDoc->Attach(pPlaylistDoc);
                }
                pPlaylistDoc->AddSong(lValue, false, true, true);
            }
        }
        else if(base < PlaylistDoc >::bases(m_pobjSource))
        {
            XfplayerDoc * pPlayerDoc = dynamic_cast < XfplayerDoc * > (pdoctemplate->get_document(0));
            PlaylistDoc * pPlaylistDoc = dynamic_cast < PlaylistDoc * > (m_pobjSource);
            pPlaylistDoc->AddSong(lValue, false, true, true);
        }
    }
    else
    {
        pApp->ViewToolsAlbum();
//        AlbumViewUpdateHint * puh = new AlbumViewUpdateHint();
  //      puh->m_i = 15;
    //    puh->m_str = str;
      //  pApp->GetAlbumThread()->AddUpdate(puh);
        pApp->GetAlbumThread()->PostThreadMessage(WM_USER + 113, 23, 0);
    }
    PostMessage(WM_CLOSE);*/
}

void CToolV023Dialog::OnCancel()
{
    //PostMessage(WM_CLOSE);
}

void CToolV023Dialog::OnDestroy() 
{
//   dialog::OnDestroy();
   
   // TODO: add your message handler code here
   
}

BOOL CToolV023Dialog::DestroyWindow() 
{
   // TODO: add your specialized code here and/or call the base class
   
/*   if(dialog::DestroyWindow())
    {
        
        return TRUE;
    }
    else
    {
        return FALSE;
    }*/
   return TRUE;
}

void CToolV023Dialog::PostNcDestroy() 
{
   // TODO: add your specialized code here and/or call the base class
   
//   dialog::PostNcDestroy();
    delete this;
}
