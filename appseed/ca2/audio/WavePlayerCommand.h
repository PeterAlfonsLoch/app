#pragma once

#include "Command.h"

class audWaveOut;
class audWavePreBuffer;

class CLASS_DECL_ca audWavePlayerCommand
{
public:


   EaudCommand                         m_ecommand;
   ex1::filesp                         m_pfileOpen;
   base_array < event *, event * >     m_evptra;
   bool                                m_bResult;
   bool *                              m_pbResult;
   bool                                m_bSeekable;
   imedia::position                    m_position;
   ::audio_decode::decoder *           m_pdecoderOpen;


   audWavePlayerCommand();
   audWavePlayerCommand(const audWavePlayerCommand & command);


   void SetOpenFile(ex1::file * pfile);
   void SetOpenDecoder(::audio_decode::decoder * pdecoder);
   ex1::file * GetOpenFile() const;
   void SetCommand(EaudCommand ecommand);
   EaudCommand GetCommand() const;


   void SetEvents();
   void AttachEvent(event * pevent);
   

   void OpenDecoder(::audio_decode::decoder * pdecoder);
   void OpenRtpFile(ex1::file * pfile);
   void OpenMp3File(ex1::file * pfile);
   void OpenAiffFile(ex1::file * pfile);
   void OpenCdaFile(ex1::file * pfile);
   void OpenWmFile(ex1::file * pfile);
   void OpenWavFile(ex1::file * pfile);
   void OpenFile(ex1::file * pfile, bool bSeekable = true);
   void OpenVqfFile(ex1::file * pfile);

   void Play(const imedia::position & position);
   void Stop();
   void OpenDevice();
   void CloseDevice();

   audWavePlayerCommand & operator =(const audWavePlayerCommand & command);

};

