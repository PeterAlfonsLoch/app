#pragma once

enum EaudMessage
{
   audMessageCommand = WM_APP + 100,
   audMessagePreBufferDone,
};

class CLASS_DECL_ca audWavePreBufferCallback
{
public:
   virtual void OnPreBufferDone(int iId);
};

