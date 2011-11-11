#include "StdAfx.h"

SoftKaraokeInfo::SoftKaraokeInfo()
{

}

SoftKaraokeInfo::~SoftKaraokeInfo()
{

}

void SoftKaraokeInfo::Prepare()
{
   m_strSongName.trim_left();
   m_strSongName.trim_right();
   m_strAuthor.trim_left();
   m_strAuthor.trim_right();
   m_strCopyright.trim_left();
   m_strCopyright.trim_right();
}

void SoftKaraokeInfo::Empty()
{
   m_strSongName.Empty();
   m_strAuthor.Empty();
   m_strCopyright.Empty();
}

bool SoftKaraokeInfo::is_empty()
{
   return m_strSongName.is_empty()
      &&  m_strAuthor.is_empty() 
      &&  m_strCopyright.is_empty();
}
