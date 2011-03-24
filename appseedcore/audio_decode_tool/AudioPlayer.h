#pragma once

class AudioPlayerThread;

class AudioPlayer
{
public:
   AudioPlayer(void);

   enum ENotify
   {
      NotifyPlaybackEnd
   };

   notsad::File                  m_file;
   notsad::DecoderPluginSetEx1   m_pluginset;
   notsad::Decoder *             m_pdecoder;
   HWAVEOUT                      m_hwaveout;
   UINT                          m_uiDeviceId;
   WAVEFORMATEX                  m_waveformat;
   CArray < CArray < unsigned char > > m_bufa;
   CArray < WAVEHDR >            m_hdra;
   AudioPlayerThread *           m_pthread;
   bool                          m_bPlay;
   int                           m_iPlayBufferCount;
   HWND                          m_hwndCallback;
   UINT                          m_uiMessageCallback;

   void OnMmWomDone(HWAVEOUT hwaveout, LPWAVEHDR lpwavehdr);

public:
   virtual ~AudioPlayer(void);
public:
   bool Open(LPCTSTR lpcszFileName, HWND hwnd, UINT uiMessage);
public:
   bool Play(void);
public:
   bool Stop(void);
public:
   bool Close(void);
};
