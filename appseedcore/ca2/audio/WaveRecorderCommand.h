#pragma once

class audWaveOut;
class audWavePreBuffer;

class CLASS_DECL_ca audWaveRecorderCommand
{
protected:
   EaudCommand                         m_ecommand;
   ex1::file *                         m_pfileOpen;
   base_array < CEvent *, CEvent * >   m_evptra;
public:
   bool                                m_bResult;
   bool *                              m_pbResult;
//      void CloseDevice();
//    void OpenDevice();
   void SetEvents();
   void AttachEvent(CEvent * pevent);
   audWaveRecorderCommand();
   audWaveRecorderCommand(const audWaveRecorderCommand & command);
   audWaveRecorderCommand & operator =(const audWaveRecorderCommand & command);
   void OpenWavFile(ex1::file * pfile);
   void Record();
   void Stop();
   void SetOpenFile(ex1::file * pfile);
   ex1::file * GetOpenFile() const;
   void SetCommand(EaudCommand ecommand);
   EaudCommand GetCommand() const;
};

