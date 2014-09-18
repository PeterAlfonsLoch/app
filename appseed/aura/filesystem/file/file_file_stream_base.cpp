#include "framework.h"


namespace file
{


   file_stream_base::file_stream_base()
   {

   }


   file_stream_base::~file_stream_base()
   {

   }


   void file_stream_base::open(const char * lpszFileName,uint32_t nOpenFlags,sp(::aura::application) papp)
   {

      m_spbuffer.release();

      try
      {

         if(papp == NULL)
         {

            m_spbuffer = canew(::file::streambuf(lpszFileName,nOpenFlags | ::file::mode_read));

         }
         else
         {

            m_spbuffer = App(papp).file_get_file(lpszFileName,nOpenFlags | ::file::mode_read);

         }

      }
      catch(...)
      {

      }

      if(m_spbuffer.is_null())
      {

         setstate(failbit);

      }


   }


} // namespace file



















