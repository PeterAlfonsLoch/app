#include "StdAfx.h"

CXFInfoHeaders::CXFInfoHeaders()
{

}

CXFInfoHeaders::~CXFInfoHeaders()
{

}

void CXFInfoHeaders::Empty()
{
   m_strSongName.Empty();
   m_xfInfoHeader.Empty();
   m_xfaInfoHeaderLS.remove_all();

}

void CXFInfoHeaders::Prepare()
{
   m_strSongName.trim_left();
   m_strSongName.trim_right();
   m_xfInfoHeader.Prepare();
   for(int i = 0; i < m_xfaInfoHeaderLS.get_size(); i++)
   {
      m_xfaInfoHeaderLS[i].Prepare();
   }

}
