#include "StdAfx.h"

midi_exception::midi_exception(::mus::midi::e_file_result mfr)
{
   m_etype = TypeMidiFile;
   m_mfr = mfr;
}
midi_exception::midi_exception(MMRESULT mmr, int iAppError)
{
   m_etype = TypeMultimediaSystem;
   m_mmr = mmr;
   m_iAppError = iAppError;
}

midi_exception::midi_exception()
{
   m_etype = TypeUndefined;
}

midi_exception::~midi_exception()
{

}

void midi_exception::SetMMResult(MMRESULT mmr)
{
   m_etype = TypeMultimediaSystem;
   m_mmr = mmr;
}

string midi_exception::GetDetailsText()
{
   string str;
   //switch(m_mmr)
   //{
   //default:
      str.Format("MMSYSTEMERROR = %d, Error = %d", m_mmr, m_iAppError);
   //   break;
   //}
   return str;
}


void midi_exception::SetUserText(const char * lpsz)
{
   m_strUser = lpsz;
}

string midi_exception::GetUserText()
{
   return m_strUser;
}
