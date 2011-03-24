#include "StdAfx.h"
#include "document_manager.h"

#include "KaraokeSDIFrame.h"
#include "XfplayerDoc.h"
#include "XfplayerView.h"
#include "XfplayerFrame.h"


#include "AudioSpectrumDoc.h"
#include "AudioSpectrumView.h"


namespace vmsp
{

   document_manager::document_manager(::ca::application * papp) :
      ca(papp)
   {
   }

   document_manager::~document_manager()
   {

   }

   bool document_manager::CreateTemplates()
   {
      vmsp::application * papp = dynamic_cast < vmsp::application * > (&System);
      musctrl::MusicalPlayerCentral & playercentral = papp->GetMusicalPlayerCentral();

      playercentral.m_pruntimeclassDocument = &typeid(XfplayerDoc);
      playercentral.m_typeinfoFrameWnd = &typeid(KaraokeSDIFrame);
      playercentral.m_typeinfoView = &typeid(XfplayerView);
      playercentral.m_strMatter = "mplite/mainframe";
   //   playercentral.m_uiResourceIdEmbedding = IDR_XFPLAYER_SERVER_EMBEDDING;
   //   playercentral.m_uiResourceIdInPlace = IDR_XFPLAYER_SERVER_INPLACE;

      musctrl::single_document_template* pPlayerSingleDocTemplate;
      pPlayerSingleDocTemplate = playercentral.CreateDocTemplate();
      papp->userbase::application::add_document_template(pPlayerSingleDocTemplate);


      m_pdoctemplateAudioSpectrum = new
         ::userbase::single_document_template(
         get_app(),
         "vmsp/playlist",
         &typeid(AudioSpectrumDoc),
         &typeid(simple_frame_window),
         &typeid(AudioSpectrumView));

         // Connect the COleTemplateServer to the document template.
      //  The COleTemplateServer creates new documents on behalf
      //  of requesting OLE containers by using information
      //  specified in the document template.
   //   m_serverMid.ConnectTemplate(clsidMid, playercentral.get_document_template(), FALSE);

      return true;
   }
   bool document_manager::UpdateRegistry()
   {


      return true;
   }

} // namespace vmsp


