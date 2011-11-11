#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace rtprx
{

	application::rtprx_start::rtprx_start()
	{
		m_pfile = NULL;
	}

   application::application()
   {
      m_ptemplateVideo = NULL;
   }

   application::~application(void)
   {
   }

   void application::construct()
   {
      m_strAppName         = "rtprx";
      m_strBaseSupportId   = "votagus_ca2_paint";
      m_strInstallToken    = "rtprx";    
      m_strLicense         = "";
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < rtprx::pane_view >();
      System.factory().creatable_small < rtprx::document >();
      System.factory().creatable_small < rtprx::frame >();
      System.factory().creatable_small < rtprx::view >();

      if(!cube2::application::initialize_instance())
         return false;


      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";

      if(!midi_central_container::initialize_central_container(this))
      {
         return false;
      }

      if(!MusicalPlayerCentralContainer::Initialize(this))
      {
         return false;
      }


      defer_initialize_document_template();


      return TRUE;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   void application::_001OnFileNew()
   {
      userbase::application::m_pdocmanager->_001OnFileNew();
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::ca::application * application::get_app() const
   {
      return m_papp;
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      defer_initialize_document_template();
      UNREFERENCED_PARAMETER(pdata);
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_spCommandLine->m_varFile = itema[0].m_strPath;
      createcontext->m_bMakeVisible = true;
      m_ptemplateVideo->open_document_file(createcontext);
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      defer_initialize_document_template();
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_spCommandLine->m_varFile = varFile;
      createcontext->m_bMakeVisible = true;
      return m_ptemplateVideo->open_document_file(createcontext);
   }

   void application::on_request(::ca::create_context * pcreatecontext)
   {

      if(pcreatecontext->m_spCommandLine->m_ecommand == gen::command_line::command_file_open)
      {
         m_ptemplateVideo->open_document_file(pcreatecontext);
      }

   }


   void application::rtprx(const char * pszUrl)
   {
      defer_initialize_document_template();
      ::ca::create_context_sp createcontext(get_app());
      createcontext->m_spCommandLine->m_varFile = pszUrl;
      createcontext->m_bMakeVisible = true;
      m_ptemplateVideo->open_document_file(createcontext);
   }

   void application::start_rtprx(ex1::file * pfileRawPcm, const char * pszUrl)
   {
      rtprx_start * pstart		= new rtprx_start();
      pstart->m_papp			   = this;
      string strHost          = System.url().get_server(pszUrl);
      int iPort               = System.url().get_port(pszUrl);

      pstart->m_strHost			= strHost;
      pstart->m_iPort			= iPort;
      pstart->m_pfile			= pfileRawPcm;
      
      AfxBeginThread(this, &::rtprx::application::thread_proc_rtprx, (LPVOID) pstart);
   }

   UINT application::thread_proc_rtprx(LPVOID lpparam)
   {
      rtprx_start * pstart = (rtprx_start *) lpparam;
      pstart->m_papp->rtprx(pstart->m_pfile, pstart->m_strHost, pstart->m_iPort, pstart->m_iMode);
      return 0;
   }

   bool application::rtprx(::ex1::file * pfile, const char * pszHost, int iPort, int iMode)
   {
      UNREFERENCED_PARAMETER(iMode);
         //audio_decode::decoder_plugin_set_ex1  * pdecodersetex1  = new audio_decode::decoder_plugin_set_ex1(this);

//         gen::memory_file * pmemfileMp3     = new gen::memory_file(this);

      string strHost(pszHost);

      rtp::file * prtpfile = new rtp::file(this);

      if(iPort == 0)
         iPort = 1984;
      if(strHost.is_empty())
         strHost = "127.0.0.1";

      if(!prtpfile->rx_open(strHost, iPort))
         return false;

      prtpfile->set_payload("mp3", &payload_type_mp3_128);

		audio_decode::decoder_plugin_set decoderset(this);

		audio_decode::decoder_plugin * pdecoderplugin = decoderset.LoadPlugin("audio_decode_libmpg123.dll");

		audio_decode::decoder * pdecoder = pdecoderplugin->NewDecoder();

		pdecoder->DecoderInitialize(prtpfile);

		int iSize = 1024 * 2 * 2 * 4;

		char * bufferWav = (char *) malloc(iSize);

		::primitive::memory_size uiRead;

		while((uiRead = pdecoder->DecoderFillBuffer(bufferWav, iSize)) > 0)
		{
		pfile->write(bufferWav, 1024);
		}
      return true;
   }


   void application::defer_initialize_document_template()
   {
      if(m_ptemplateVideo != NULL)
         return;
      ::userbase::single_document_template* pdoctemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < rtprx::document > (),
         ::ca::get_type_info < rtprx::frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < rtprx::view > ());
      userbase::application::add_document_template(pdoctemplate);
      m_ptemplateVideo = pdoctemplate;

   }

} // namespace rtprx

