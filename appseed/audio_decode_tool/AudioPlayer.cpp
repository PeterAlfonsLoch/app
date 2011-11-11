#include "StdAfx.h"
#include "AudioPlayer.h"
#include "AudioPlayerThread.h"

AudioPlayer::AudioPlayer(void)
{
   m_bPlay        = false;
   m_hwaveout     = NULL;
   m_uiDeviceId   = WAVE_MAPPER;
   m_pdecoder     = NULL;
   m_pthread      = (AudioPlayerThread *) AfxBeginThread(RUNTIME_CLASS(AudioPlayerThread));
   m_pthread->m_pplayer = this;
}

AudioPlayer::~AudioPlayer(void)
{
}

bool AudioPlayer::Open(LPCTSTR lpcszFileName, HWND hwnd, UINT uiMessage)
{
   if(!m_file.Open(lpcszFileName, CFile::modeRead | CFile::typeBinary))
      return false;

   m_pdecoder = m_pluginset.GetNewDecoder(lpcszFileName, &m_file);
   if(m_pdecoder == NULL)
   {
      AfxMessageBox("Error creating decoder.");
      return false;
   }

   m_pdecoder->DecoderInitialize(&m_file);

   m_waveformat.cbSize = sizeof(m_waveformat);
   m_waveformat.wBitsPerSample = m_pdecoder->DecoderGetBitsPerSample();
   m_waveformat.nSamplesPerSec = m_pdecoder->DecoderGetSamplesPerSec();
   m_waveformat.wFormatTag = WAVE_FORMAT_PCM;
   m_waveformat.nChannels = m_pdecoder->DecoderGetChannelCount();
	m_waveformat.nBlockAlign = m_waveformat.wBitsPerSample * m_waveformat.nChannels / 8;
	m_waveformat.nAvgBytesPerSec = m_waveformat.nSamplesPerSec * m_waveformat.nBlockAlign;

   if(waveOutOpen(&m_hwaveout, m_uiDeviceId, &m_waveformat,
      (DWORD_PTR) m_pthread->m_nThreadID, (DWORD_PTR) 0, CALLBACK_THREAD) != MMSYSERR_NOERROR)
   {
      AfxMessageBox("Error opening wave out device.");
      return false;
   }

   m_bufa.SetSize(8);
   for(int i = 0; i < m_bufa.GetSize(); i++)
   {
      m_bufa[i].SetSize(8 * 1024);
   }
   m_hdra.SetSize(m_bufa.GetSize());
   for(int i = 0; i < m_bufa.GetSize(); i++)
   {
      m_hdra[i].lpData = (LPSTR) m_bufa[i].GetData();
		m_hdra[i].dwBufferLength = m_bufa[i].GetSize();
		m_hdra[i].dwBytesRecorded = 0;
		m_hdra[i].dwUser = i;
		m_hdra[i].dwFlags = 0;      
      if(waveOutPrepareHeader(m_hwaveout, &m_hdra[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
      {
         AfxMessageBox("Error preparing audio buffers.");
         return false;
      }
   }
   m_hwndCallback = hwnd;
   m_uiMessageCallback = uiMessage;
   return true;
}

bool AudioPlayer::Play(void)
{
   m_iPlayBufferCount = 0;
   m_bPlay = true;
   int i = 0;
   while(!m_pdecoder->DecoderEOF() && i < m_bufa.GetSize())
   {
      memset(m_bufa[i].GetData(), 0, m_bufa[i].GetSize());
      m_pdecoder->DecoderFillBuffer(m_bufa[i].GetData(), m_bufa[i].GetSize());
      i++;
   }
   int count = i;
   i = 0;
   while(i < count)
   {
      m_iPlayBufferCount++;
      waveOutWrite(m_hwaveout, &m_hdra[i], sizeof(WAVEHDR));
      i++;
   }
      
   return false;
}

bool AudioPlayer::Stop(void)
{
   m_bPlay = false;
   waveOutReset(m_hwaveout);
   return false;
}

bool AudioPlayer::Close(void)
{
   for(int i = 0; i < m_bufa.GetSize(); i++)
   {
      if(waveOutUnprepareHeader(m_hwaveout, &m_hdra[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
      {
         AfxMessageBox("Error finishing audio buffers.");
      }
   }

   if(waveOutClose(m_hwaveout) != MMSYSERR_NOERROR)
   {
      AfxMessageBox("Error closgin wave out device.");
   }

   m_file.Close();

   return true;
}



void AudioPlayer::OnMmWomDone(HWAVEOUT hwaveout, LPWAVEHDR lpwavehdr)
{
   m_iPlayBufferCount--;
   int i = lpwavehdr->dwUser;
   if(!m_pdecoder->DecoderEOF() && m_bPlay)
   {
      memset(m_bufa[i].GetData(), 0, m_bufa[i].GetSize());
      m_pdecoder->DecoderFillBuffer(m_bufa[i].GetData(), m_bufa[i].GetSize());
      m_iPlayBufferCount++;
      waveOutWrite(m_hwaveout, &m_hdra[i], sizeof(WAVEHDR));
   }
   else if(m_pdecoder->DecoderEOF() && m_iPlayBufferCount == 0)
   {
      if(m_bPlay)
      {
         Close();
      }
      ::PostMessage(m_hwndCallback, m_uiMessageCallback, NotifyPlaybackEnd, 0);
   }
}