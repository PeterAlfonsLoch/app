#include "framework.h"


namespace file
{


   plain_text_stream_base::plain_text_stream_base()
   {

      m_fmtflags = nofmtflags;

   }


   plain_text_stream_base::~plain_text_stream_base()
   {

   }


   fmtflags plain_text_stream_base::setf(fmtflags flagsAdd)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) ((uint32_t) m_fmtflags | (uint32_t) flagsAdd);

      return fmtflagsOld;

   }


   fmtflags plain_text_stream_base::setf(fmtflags flagsAdd, fmtflags flagsRemove)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) (((uint32_t) m_fmtflags | (uint32_t) flagsAdd) & (~(uint32_t)flagsRemove));

      return fmtflagsOld;

   }


} // namespace file


