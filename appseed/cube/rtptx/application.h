#pragma once

namespace rtptx
{

   class CLASS_DECL_CA2_CUBE application :
      virtual public rtprx::application,
      virtual public audWaveInListener
   {
   public:
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

      virtual bool bergedge_start();

      virtual void _001OnFileNew();

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         

      virtual ::ca::application * get_app() const;
      virtual void OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema);


      virtual void WaveInDataProc(audWaveIn *pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
   };


} // namespace rtptx
