#include "StdAfx.h"
#include "MixerVisualCentral.h"

#include "MixerDoc.h"

#include "MixerFrameWnd.h"
#include "MixerVisualThread.h"

#define IDR_MIXER 150

MixerVisualCentral::MixerVisualCentral(::ca::application * papp) :
   ca(papp)
{
   m_pdoctemplate = NULL;
}

MixerVisualCentral::~MixerVisualCentral()
{
   if(m_pdoctemplate != NULL)
   {
      delete m_pdoctemplate;
      m_pdoctemplate = NULL;
   }
}




void MixerVisualCentral::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::user::interaction::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &MixerVisualCentral::_001OnClose);
}

void MixerVisualCentral::_001OnClose(gen::signal_object * pobj) 
{
   UNREFERENCED_PARAMETER(pobj);
// trans   ::user::interaction::OnClose();
   DestroyWindow();
}



/*MMRESULT MixerVisualCentral::CreateNewDevice(UINT uiMixerID)
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
}*/

/*MMRESULT MixerVisualCentral::CreateNewDestination(DWORD dwComponentType)
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

::userbase::multiple_document_template * MixerVisualCentral::CreateDocTemplate(::ca::application * papp)
{
   if(m_pdoctemplate == NULL)
   {
      m_pdoctemplate = new ::userbase::multiple_document_template(
         papp,
         "mixeruserbase/mixer",
         &typeid(MixerDoc),
         &typeid(MixerFrameWnd),
         &typeid(MixerMainView));
   }
   return m_pdoctemplate;
}

bool MixerVisualCentral::Initialize(::ca::application * papp)
{
   set_app(papp);
   m_pvisualthread = AfxBeginThread < MixerVisualThread >(get_app());

   if(m_pvisualthread == NULL)
      return false;

   m_pvisualthread->m_event.Lock();

   MixerVisualThread::CInitialize * pinitialize = new MixerVisualThread::CInitialize;

   pinitialize->m_pvisualcentral = this;

   m_pvisualthread->PostThreadMessage(
      MixerVisualThread::MessageMain,
      MixerVisualThread::MessageMainWparamInitialize,
      (LPARAM) pinitialize);

   CreateDocTemplate(get_app());

   if(get_document_template() == NULL)
      return false;

   return true;
}

void MixerVisualCentral::DisplayAMixer()
{
   m_pvisualthread->PostThreadMessage(
      MixerVisualThread::MessageMain,
      MixerVisualThread::MessageMainWparamDisplayAMixer,
      0);
}

void MixerVisualCentral::OnVisualThreadExitInstance()
{
   m_pdoctemplate->close_all_documents(false);
}

::userbase::multiple_document_template * MixerVisualCentral::get_document_template()
{
   return m_pdoctemplate;
}



