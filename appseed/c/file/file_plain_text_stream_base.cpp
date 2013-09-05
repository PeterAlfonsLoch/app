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


   iostate plain_text_stream_base::rdstate() const
   {
      return m_iostate;
   }

   void plain_text_stream_base::setstate(iostate state)
   {
      clear(rdstate() | state);
   }

   void plain_text_stream_base::clear(iostate state)
   {
      m_iostate = state;
   }

   bool plain_text_stream_base::bad() const
   {
      return (m_iostate & badbit) != 0;
   }

   bool plain_text_stream_base::fail() const
   {
      return (m_iostate & badbit) || ( m_iostate & failbit);
   }

   bool plain_text_stream_base::eof() const
   {
      return m_iostate & eofbit;
   }

   bool plain_text_stream_base::good() const
   {
      return m_iostate == goodbit;
   }


} // namespace file