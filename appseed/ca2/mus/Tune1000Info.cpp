#include "StdAfx.h"

CTune1000Info::CTune1000Info()
{

}

CTune1000Info::~CTune1000Info()
{

}

void CTune1000Info::Prepare()
{
   m_strSongName.trim_left();
   m_strSongName.trim_right();
   m_straOther.trim_left();
   m_straOther.trim_right();

}

void CTune1000Info::Empty()
{
   m_strSongName.Empty();
   m_straOther.remove_all();
}

bool CTune1000Info::is_empty()
{
   return m_strSongName.is_empty() &&
         m_straOther.get_size() == 0;
}
