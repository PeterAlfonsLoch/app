#pragma once

class AudioPlayer;

// AudioPlayerThread

class AudioPlayerThread : public CWinThread
{
	DECLARE_DYNCREATE(AudioPlayerThread)

protected:
	AudioPlayerThread();           // protected constructor used by dynamic creation
	virtual ~AudioPlayerThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

   AudioPlayer * m_pplayer;

   afx_msg void OnMmWomDone(WPARAM wparam, LPARAM lparam);

protected:
	DECLARE_MESSAGE_MAP()
};


