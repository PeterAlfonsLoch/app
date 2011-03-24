#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"
#include <math.h>

#define TYPE(val)      (val)
#define CLOCK_RATE(val)      (val)
#define BITS_PER_SAMPLE(val)   (val)
#define ZERO_PATTERN(val)   (val)
#define PATTERN_LENGTH(val)   (val)
#define NORMAL_BITRATE(val)   (val)
#define MIME_TYPE(val)      (val)
#define CHANNELS(val)      (val)
#define FMTP(val)      (val)

char offset0[4] = {0x00, 0x00, 0x00, 0x00};


double sgn(double x)
{
   if(x == 0.0)
      return 0.0;
   else if(x > 0.0)
      return 1.0;
   else
      return -1.0;
}

namespace rtptx
{

   application::application()
   {
      m_pdecodersetex1  = NULL;
      m_pmemfileMp3     = NULL;
   }

   application::~application(void)
   {
   }

   void application::construct()
   {
      m_strAppName         = "rtptx";
      m_strBaseSupportId   = "votagus_ca2_paint";
      m_strInstallToken    = "rtptx";    
      m_dwSynchSource      = 1;
      m_strLicense         = "";
   }


   bool application::initialize_instance()
   {
      System.factory().creatable_small < rtptx::pane_view >();
      System.factory().creatable_small < rtptx::document >();
      System.factory().creatable_small < rtptx::frame >();
      System.factory().creatable_small < rtptx::view >();

      if(!ca84::application::initialize_instance())
         return false;

      m_pdecodersetex1  = new audio_decode::decoder_plugin_set_ex1(this);
      m_pmemfileMp3     = new gen::memory_file(this);

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

      m_pdecodersetex1  = new audio_decode::decoder_plugin_set_ex1(this);
      m_pmemfileMp3     = new gen::memory_file(this);

      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(html_document),
         &typeid(html_frame),       // main SDI frame ::ca::window
         &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(rtptx::document),
         &typeid(rtptx::frame),       // main SDI frame ::ca::window
         &typeid(rtptx::view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;


      m_ptemplate_html->open_document_file(NULL, TRUE, m_puiInitialPlaceHolderContainer);


























      //if(!spfile->open(unitext("I:\\Música\\Yamaha\\ambient\\Ambient.mp3"), ex1::file::type_binary | ex1::file::mode_read))
         //return false;
         


      return true;
   }


   bool application::bergedge_start()
   {
      m_prtpfile = new rtp::file(this);

      string strHost = System.url().get_server(command_line().m_varFile);
      int iPort = System.url().get_port(command_line().m_varFile);

      if(iPort == 0)
         iPort = 1984;
      if(strHost.is_empty())
         strHost = "127.0.0.1";

      if(!m_prtpfile->tx_open(strHost, iPort))
         return false;

      m_prtpfile->set_payload("mp3", &payload_type_mp3_128);

      audio_decode::encoder_plugin_set encoderset(this);

      audio_decode::encoder_plugin * pencoderplugin = encoderset.LoadPlugin(0, "audio_decode_libmpg123.dll");

      m_pencoder = pencoderplugin->NewEncoder();

      m_pencoder->EncoderInitialize();

      m_pencoder->EncoderSetFile(m_pmemfileMp3);

      //m_pencoder->EncoderSetBitsPerSample(pdecoder->DecoderGetBitsPerSample());
      //m_pencoder->EncoderSetChannelCount(pdecoder->DecoderGetChannelCount());
      //m_pencoder->EncoderSetSamplesPerSec(pdecoder->DecoderGetSamplesPerSecond());
      m_pencoder->EncoderSetBitsPerSample(16);
      m_pencoder->EncoderSetChannelCount(2);
      m_pencoder->EncoderSetSamplesPerSec(44100);

      
      int iMode = command_line().m_varQuery["mode"].get_integer();


      if(iMode == 0)
      {
         m_pwaverecorder = AfxBeginThread < audWaveRecorder > (get_app());
         m_pwaverecorder->m_pwavein->AddListener(this);
         
         //m_pwaverecorder->m_iOutBufferSampleCount = (44100 * 1024 * 8 * 2) / (128 * 1000);
         m_pwaverecorder->m_iOutBufferSampleCount = (1024 * 44100 * 8) / (128 * 1000 * 2);
         //m_pwaverecorder->m_iOutBufferSampleCount = m_pwaverecorder->m_iOutBufferSampleCount * 3 / 2;
         audWaveRecorderCommand reccommand;
         reccommand.Record();
         m_pwaverecorder->ExecuteCommand(reccommand);


         //m_iSize = (44100 * 1024 * 8 * 2) / (128 * 1000); // 44100 kHz * 1024 Samples * 8Bytes / 128 kbps
         //m_iSize =  (44100 * 1024 * 2 * 2) / (16 * 1000 * 2); // 44100 kHz * 1024 Samples * 8Bytes / 128 kbps

         m_bufferWav = (char *) malloc(m_iSize);
         m_bufferMp3 = (char *) malloc(1024 * 128);
      
      }
      else if(iMode == 1)
      {
         ex1::filesp spfile(get_app());
         if(!spfile->open(unitext("V:\\007 Música\\Southern All Stars - Namida no Kiss.mp3"), ex1::file::type_binary | ex1::file::mode_read))
            return false;

         //if(!spfile->open("D:\\005 Arquivo\\007 Gran Archive\\Ambient.wav", ex1::file::type_binary | ex1::file::mode_read))
           // return false;
         audio_decode::decoder_plugin_set decoderset(this);

         audio_decode::decoder_plugin * pdecoderplugin = decoderset.LoadPlugin("audio_decode_libmpg123.dll");

         audio_decode::decoder * pdecoder = pdecoderplugin->NewDecoder();

         pdecoder->DecoderInitialize(spfile);

         int iSize = 1024 * 2 * 2 * 4;

         char * bufferWav = (char *) malloc(iSize);
         char * bufferMp3 = (char *) malloc(iSize * 128);

         UINT uiRead;

         while((uiRead = pdecoder->DecoderFillBuffer(bufferWav, iSize)) > 0)
         {
            m_pencoder->EncoderWriteBuffer(bufferWav, iSize);
            if(m_pmemfileMp3->get_size() > 1024)
            {
               m_pmemfileMp3->seek_to_begin();
               while((uiRead = m_pmemfileMp3->read(bufferMp3,1024)) == 1024)
               {
                  m_prtpfile->write(bufferMp3, 1024);
                  DWORD dwLen = m_pmemfileMp3->GetPosition();
                  m_pmemfileMp3->RemoveBegin(NULL, dwLen);
                  if(m_pmemfileMp3->get_size() < 1024)
                     break;
               }
               m_pmemfileMp3->seek_to_end();
            }
         }
      }
      else if(iMode == 2)
      {
         int iSampleBytes = (sizeof(short) * 2); // 2 channels * sample size
         double dSamplingFrequency = 44100;
         double dRingTime = 10.0;
//         int iTimes = 1;
         int iSize = 1024 * 2 * 2;
         iSize = (int) (dRingTime * dSamplingFrequency * iSampleBytes);

         char * bufferWav = (char *) malloc(iSize);
         char * bufferMp3 = (char *) malloc(1024 * 128);

         double pi = 3.1415926535897932384626433832795;
         double omegaLa220 = 2 * pi * 110;
         double omegaLa = 2 * pi * 440;
         double omegaDo = 2 * pi * 440 * pow(2.0, 4.0 / 12.0);
         double omegaMi = 2 * pi * 440 * 3 / 2;
         double omegaSolSharp = 2 * pi * 440 * pow(2.0, 11.0 / 12.0);
         
         int iSample;
         int iSampleCount = iSize / iSampleBytes;
         int iPos = 0;
         UINT uiRead;
         for(iSample = 0; iSample < iSampleCount; iSample++)
         {
            double t = iSample / dSamplingFrequency;
            short sh = (short)(4000.0 * sgn(sin(omegaLa220 * t)) / exp(t * 0.5));
            sh += (short)(8000.0 * sin(omegaLa * t) / exp(t * 5.0));
            if(t > 0.25)
            {
               double tDo = t - 0.25;
               sh += (short)(8000.0 * sin(omegaDo * tDo) / exp(tDo * 5.0));
            }
            if(t > 0.50)
            {
               double tMi = t - 0.50;
               sh += (short)(8000.0 * sin(omegaMi * tMi) / exp(tMi * 5.0));
            }
            if(t > 0.75)
            {
               double tSolSharp = t - 0.50;
               sh += (short)(8000.0 * sin(omegaSolSharp * tSolSharp) / exp(tSolSharp * 5.0));
            }
            ((short *)bufferWav)[iPos++] = sh;
            ((short *)bufferWav)[iPos++] = sh;
         }

         m_pencoder->EncoderWriteBuffer(bufferWav, iSize);
         m_pmemfileMp3->seek_to_begin();
         if(m_pmemfileMp3->get_size() > 1024)
         {
            m_pmemfileMp3->seek_to_begin();
            while((uiRead = m_pmemfileMp3->read(bufferMp3,1024)) == 1024)
            {
               m_prtpfile->write(bufferMp3, 1024);
               DWORD dwLen = m_pmemfileMp3->GetPosition();
               m_pmemfileMp3->RemoveBegin(NULL, dwLen);
               if(m_pmemfileMp3->get_size() < 1024)
                  break;
            }
            m_pmemfileMp3->seek_to_end();
         }
      }
      
      return true;
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

   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplateVideo->open_document_file(itema[0].m_strPath);
   }

   void application::WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr)
   {
      UNREFERENCED_PARAMETER(pwavein);
      UNREFERENCED_PARAMETER(dwSampleTime);

      UINT uiRead;
      m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);
      if(m_pmemfileMp3->get_size() >= 1024)
      {
         m_pmemfileMp3->seek_to_begin();
         while((uiRead = m_pmemfileMp3->read(m_bufferMp3,1024)) == 1024)
         {
            m_prtpfile->write(m_bufferMp3, 1024);
            DWORD dwLen = m_pmemfileMp3->GetPosition();
            m_pmemfileMp3->RemoveBegin(NULL, dwLen);
            if(m_pmemfileMp3->get_size() < 1024)
               break;
         }
         m_pmemfileMp3->seek_to_end();
      }
   }

} // namespace rtptx



