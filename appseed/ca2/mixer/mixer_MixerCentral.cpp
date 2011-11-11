#include "StdAfx.h"
#include "MixerCentral.h"


MixerCentral::MixerCentral(::ca::application * papp) :
   ca(papp)
{
}

MixerCentral::~MixerCentral()
{
}


 // BEGIN_MESSAGE_MAP(MixerCentral, ::user::interaction)
   //{{AFX_MSG_MAP(MixerCentral)
// xxx   ON_WM_CLOSE()
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MixerCentral message handlers


void MixerCentral::OnClose() 
{
   // TODO: add your message handler code here and/or call default
   
// trans    ::user::interaction::OnClose();

    DestroyWindow();
}



/*MMRESULT MixerCentral::CreateNewDevice(UINT uiMixerID)
{
    MMRESULT mmrc;
    if(MMSYSERR_NOERROR != (mmrc = m_pmixer->SetNewDevice(
        uiMixerID,
        (DWORD) m_hWnd,
        0,
        CALLBACK_WINDOW)))
    {
        System.simple_message_box("Could not open mixer device!");
        PostMessage(WM_CLOSE);
        return mmrc;
    }
    m_pmixer->m_pdevice->GetCaps();
    return mmrc;
}

MMRESULT MixerCentral::CreateNewDestination(DWORD dwComponentType)
{
    MMRESULT mmrc;
    CMixerDestination * pdestination = NULL;

    if(MMSYSERR_NOERROR != (mmrc =  m_pmixer->m_pdevice->GetDestination(
        dwComponentType,
        &pdestination)))
    {
        System.simple_message_box("Could not open default mixer destination!");
        PostMessage(WM_CLOSE);
        return mmrc;
    }

    m_destinationpa.add(pdestination);

    pdestination->GetSourcesInfo();

    pdestination->GetAllControls();

    m_pmixer->m_pdevice->MapLines();
    m_pmixer->m_pdevice->MapControls();

    pdestination->SendOnChangeAllControls();

    return mmrc;
}*/


bool MixerCentral::Initialize()
{
//   m_pmixerthread = (CMixerThread *) AfxBeginThread(::ca::get_type_info < CMixerThread > ());
//   if(m_pmixerthread == NULL)
//      return false;
//   return true«
   return true;
}
