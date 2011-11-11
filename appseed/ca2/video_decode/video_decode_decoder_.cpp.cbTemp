#include "StdAfx.h"

namespace video_decode
{

   decoder::decoder(::ca::application * papp) :
      ca(papp),
      m_diba(papp)
   {
      m_iPlayDib = 0;
      m_iDib = 0;
      m_iLastDib = -1;
      m_diba.set_size(11);
      m_ptsa.set_size(m_diba.get_size());
   }

   decoder::~decoder()
   {

   }

   bool decoder::DecoderGetAttribute(EAttribute eattribute, string & str)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(eattribute);
      return false;
   }

   __int64 decoder::DecoderGetMillisLength()
   {
      UINT uiRate = DecoderGetSamplesPerSecond();
      if(uiRate != 0)
         return DecoderGetSampleCount() * 1000 / uiRate;
      else
         return 0;
   }

   bool decoder::DecoderSetSeekable(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
      return true;
   }

   int decoder::DecoderSetReadBlockSize(int iSize)
   {
      UNREFERENCED_PARAMETER(iSize);
      return -1;
   }

   void decoder::DecoderSeekEnd()
   {
   }

   bool decoder::DecoderSetNonStopOnEofMode(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
      return false;
   }

   bool decoder::step()
   {
      if(m_iPlayDib == m_iLastDib)
      {
         return false;
      }
      if(!decode())
         return false;
      m_iPlayDib++;
      if(m_iPlayDib >= m_diba.get_size())
         m_iPlayDib = 0;
      if(m_iPlayDib == m_iLastDib)
      {
         return false;
      }
      Sleep(max(0, m_ptsa[m_iPlayDib] - 1));
      return true;
   }

   bool decoder::decode()
   {
      if(!DecoderNextFrame())
         return false;
      m_iDib++;
      if(m_iDib >= m_diba.get_size())
         m_iDib = 0;
      return true;
   }

} // namespace auddev