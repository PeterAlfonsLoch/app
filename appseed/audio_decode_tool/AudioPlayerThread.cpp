// AudioPlayerThread.cpp : implementation file
//

#include "stdafx.h"
#include "notsad_tool.h"
#include "AudioPlayerThread.h"
#include "AudioPlayer.h"


// AudioPlayerThread

IMPLEMENT_DYNCREATE(AudioPlayerThread, CWinThread)

AudioPlayerThread::AudioPlayerThread()
{
}

AudioPlayerThread::~AudioPlayerThread()
{
}

BOOL AudioPlayerThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int AudioPlayerThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(AudioPlayerThread, CWinThread)
   ON_THREAD_MESSAGE(MM_WOM_DONE, OnMmWomDone)
END_MESSAGE_MAP()


// AudioPlayerThread message handlers

void AudioPlayerThread::OnMmWomDone(WPARAM wparam, LPARAM lparam)
{
   m_pplayer->OnMmWomDone((HWAVEOUT) wparam, (LPWAVEHDR) lparam);
}