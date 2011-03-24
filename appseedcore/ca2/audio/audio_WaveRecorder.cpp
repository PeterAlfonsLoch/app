#include "StdAfx.h"

audWaveRecorder::audWaveRecorder(::ca::application * papp) :
   ca(papp),
   thread(papp), 
   m_pluginset(papp),
   m_eventStopped(FALSE, TRUE)
{
   m_pwavein = new audWaveIn(papp);
   m_pencoder = NULL;
}

audWaveRecorder::~audWaveRecorder()
{
}

bool audWaveRecorder::initialize_instance()
{
   if(m_pwavein == NULL)
      return false;
   m_pwavein->Begin(THREAD_PRIORITY_ABOVE_NORMAL);

   //m_pwavein->m_pplayer = this;

   return true;
}

int audWaveRecorder::exit_instance()
{
   // TODO:  perform any per-thread cleanup here
   return thread::exit_instance();
}

void audWaveRecorder::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(audMessageCommand, pinterface, this, &audWaveRecorder::OnaudCommandMessage);
}

/* // BEGIN_MESSAGE_MAP(audWaveRecorder, thread)
   ON_THREAD_MESSAGE(audMessageCommand, OnaudCommandMessage)
 // END_MESSAGE_MAP()
*/

// audWaveRecorder message handlers

void audWaveRecorder::ExecuteCommand(audWaveRecorderCommand & command)
{
   m_eventStopped.ResetEvent();
   switch(command.GetCommand())
   {
   case audCommandExecuteStop:
   case audCommandCloseDevice:
      {
          audCommandMessageProcedure(command);
      }
   break;
   default:
      {
         PostThreadMessage(
            audMessageCommand,
            (WPARAM) command.GetCommand(),
            (LPARAM) (new audWaveRecorderCommand(command)));
      }
      break;
   }

}


void audWaveRecorder::OnaudCommandMessage(gen::signal_object * pobj)
   //WPARAM wparam, // audCommand enumeration
   //LPARAM lparam  // audCommand object pointer
   //)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   audWaveRecorderCommand * pcommand = (audWaveRecorderCommand *) pbase->m_lparam;
   audCommandMessageProcedure(*pcommand);
   if(pcommand->m_pbResult != NULL)
   {
      *pcommand->m_pbResult = pcommand->m_bResult;
   }
   delete pcommand;
}

bool audWaveRecorder::audCommandMessageProcedure(audWaveRecorderCommand &command)
{
//   bool bSetEvents = true;
   command.m_bResult = true;  
   switch(command.GetCommand())
   {
   case audCommandOpenWavFile:
      {
         m_iOutBufferSampleCount = 48 * 1024;
         m_pfile = command.GetOpenFile();
         if(m_pencoder == NULL)
         {
            try
            {
               m_pencoder  = m_pluginset.GetNewEncoder("*.wav");
               if(m_pencoder == NULL)
                  return false;
            }
            catch(...)
            {
               command.m_bResult = false;
               return false;
            }
         }
         m_pwavein->m_pencoder = m_pencoder;
         m_pencoder->EncoderSetFile(m_pfile);
      }
      break;
   case audCommandExecuteRecord:
      {
         /*if(m_pencoder == NULL)
         {
               command.m_bResult = false;
               return false;
         }*/
         m_pwavein->open(8, m_iOutBufferSampleCount);
         m_pwavein->Start();
      }
      break;
   case audCommandCloseDevice:
   case audCommandExecuteStop:
      {
         m_eventStopped.ResetEvent();
         m_pwavein->Stop();
         m_pwavein->m_eventStopped.Lock((1984 + 1977) * 20);
         m_pwavein->close();
         m_pencoder->EncoderFinalize();
         m_eventStopped.SetEvent();
      }
      break;
   default:
      ASSERT(FALSE);
      break;
   }
   command.SetEvents();
   return command.m_bResult;
}


audWaveRecorderCommand::audWaveRecorderCommand()
{
   m_pbResult = NULL;
}

audWaveRecorderCommand::audWaveRecorderCommand(const audWaveRecorderCommand & command)
{
   operator =(command);
}

audWaveRecorderCommand & audWaveRecorderCommand::operator =(const audWaveRecorderCommand & command)
{
   SetCommand(command.GetCommand());
   SetOpenFile(command.GetOpenFile());
   m_bResult = command.m_bResult;
   m_pbResult = command.m_pbResult;
   m_evptra = command.m_evptra;
   return *this;

}

EaudCommand audWaveRecorderCommand::GetCommand() const
{
   return m_ecommand;
}

void audWaveRecorderCommand::SetCommand(EaudCommand ecommand)
{
   m_ecommand = ecommand;
}

ex1::file * audWaveRecorderCommand::GetOpenFile() const
{
   return m_pfileOpen;
}

void audWaveRecorderCommand::SetOpenFile(ex1::file *pfile)
{
   m_pfileOpen = pfile;
}

void audWaveRecorderCommand::OpenWavFile(ex1::file * pfile)
{
   SetCommand(audCommandOpenWavFile);
   SetOpenFile(pfile);
}


void audWaveRecorderCommand::SetEvents()
{
   for(int i = 0;  i < m_evptra.get_size(); i++)
   {
      m_evptra[i]->SetEvent();
   }
}
void audWaveRecorderCommand::Stop()
{
   SetCommand(audCommandExecuteStop);

}

void audWaveRecorderCommand::Record()
{
   SetCommand(audCommandExecuteRecord);

}


void audWaveRecorder::WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr)
{
   UNREFERENCED_PARAMETER(pwavein);
   UNREFERENCED_PARAMETER(dwSampleTime);
   m_pfile->write(lpwavehdr->lpData, lpwavehdr->dwBufferLength);
}

bool audWaveRecorder::IsRecording()
{
   return m_pwavein->IsRecording();
}




