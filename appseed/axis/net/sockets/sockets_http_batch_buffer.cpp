#include "framework.h" // from "axis/net/net_sockets.h"
#include "axis/net/net_sockets.h"


namespace sockets
{



   http_batch_buffer::http_batch_buffer(::aura::application * papp) :
      element(papp)
   {

      m_nOpenFlags = 0;

   }

   fesp http_batch_buffer::open(const char * lpszFileName, UINT nOpenFlags)
   {

      m_strPath = lpszFileName;

      m_nOpenFlags = nOpenFlags;

      if(m_nOpenFlags & ::file::mode_read)
      {

         get_file_data();

      }

      return ::file::no_exception();

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


