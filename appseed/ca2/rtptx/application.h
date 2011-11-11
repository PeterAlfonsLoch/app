#pragma once

namespace rtptx
{

   class CLASS_DECL_ca application :
      virtual public rtprx::application,
      virtual public audWaveInListener
   {
   public:

      class rtptx_start
      {
      public:
         rtptx_start();
         rtptx::application * m_papp;
         string m_strHost;
         int m_iPort;
         int m_iMode;
         ::ex1::file * m_pfile;
      };


      ::userbase::single_document_template *    m_ptemplate_html;
      ::userbase::single_document_template *    m_ptemplateVideo;
      audio_decode::decoder *                   m_pdecoder;
      audio_decode::decoder_plugin_set_ex1 *       m_pdecodersetex1;
      rtp::file *                               m_prtpfile;

      audio_decode::encoder *                   m_pencoder;
      audWaveRecorder *                         m_pwaverecorder;
      DWORD                                     m_dwSynchSource;

      int                                       m_iSize;

      gen::memory_file *                             m_pmemfileMp3;

      char *                                    m_bufferWav;
      char *                                    m_bufferMp3;

      application(void);
      virtual ~application(void);

      virtual void construct();


      virtual bool initialize_instance();
      virtual int exit_instance();

      virtual void on_request(::ca::create_context * pline);

      bool start_rtptx(const char * pszHost, int iPort, ex1::file * pfileRawPcm);
      bool start_rtptx(const char * pszHost, int iPort, int iMode);
      static UINT thread_proc_rtptx(LPVOID lpparam);
      bool rtptx(const char * pszHost, int iPort, int iMode, ex1::file * pfileRawPcm);

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);


      virtual ::ca::application * get_app() const;
      virtual void OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema);


      virtual void WaveInDataProc(audWaveIn *pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
   };


} // namespace rtptx
