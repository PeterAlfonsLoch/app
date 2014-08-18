#include "framework.h"


namespace sockets
{



   http_batch_buffer::http_batch_buffer(sp(::axis::application) papp) :
      element(papp)
   {

      m_nOpenFlags = 0;

   }

   bool http_batch_buffer::open(const char * lpszFileName, UINT nOpenFlags)
   {

      m_strPath = lpszFileName;

      m_nOpenFlags = nOpenFlags;

      if(m_nOpenFlags & ::file::mode_read)
      {

         get_file_data();

      }

      return TRUE;

   }

   void http_batch_buffer::close()
   {
      if(m_nOpenFlags & ::file::mode_write)
      {
         set_file_data();
      }
   }

   void http_batch_buffer::flush()
   {
      if(m_nOpenFlags & ::file::mode_write)
      {
         set_file_data();
      }
   }


} // namespace sockets


