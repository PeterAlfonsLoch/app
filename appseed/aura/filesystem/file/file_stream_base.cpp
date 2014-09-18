#include "framework.h"


namespace file
{


   stream_base::stream_base()
   {

      m_iostate         = goodbit;
      m_fmtflags        = nofmtflags;
      m_precision       = 0;

   }


   stream_base::stream_base(sp(stream_buffer) pbuffer) :
      m_spbuffer(pbuffer)
   {

      m_iostate         = goodbit;
      m_fmtflags        = nofmtflags;
      m_precision       = 0;

   }


   stream_base::stream_base(const stream_base & buffer)
   {

      m_iostate         = buffer.m_iostate;
      m_fmtflags        = nofmtflags;
      m_precision       = 0;
      m_spbuffer        = buffer.m_spbuffer;

   }


   stream_base::~stream_base()
   {

   }


   string stream_base::GetFilePath() const
   {

      return m_spbuffer->GetFilePath();

   }


   void stream_base::close()
   {

      m_spbuffer.release();

   }


   file_position stream_base::seek(file_offset offset, e_seek eseek)
   {

      return m_spbuffer->seek(offset, eseek);

   }

   fmtflags stream_base::setf(fmtflags flagsAdd)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) ((uint32_t) m_fmtflags | (uint32_t) flagsAdd);

      return fmtflagsOld;

   }


   fmtflags stream_base::setf(fmtflags flagsAdd, fmtflags flagsRemove)
   {

      fmtflags fmtflagsOld = m_fmtflags;

      m_fmtflags = (fmtflags) (((uint32_t) m_fmtflags | (uint32_t) flagsAdd) & (~(uint32_t)flagsRemove));

      return fmtflagsOld;

   }


   fmtflags stream_base::flags() const
   {

      return m_fmtflags;

   }

   fmtflags stream_base::flags(fmtflags flags)
   {

      return m_fmtflags = flags;

   }



   file_size stream_base::precision() const
   {

      return m_precision;

   }

   file_size stream_base::precision(file_size prec)
   {

      return m_precision = prec;

   }

   file_size stream_base::width() const
   {

      return m_width;

   }

   file_size stream_base::width(file_size prec)
   {

      return m_width = prec;

   }

   bool stream_base::is_open() const
   {

      if(m_spbuffer.is_null())
         return false;

      if(!m_spbuffer->is_open())
         return false;

      return true;

   }



} // namespace file





