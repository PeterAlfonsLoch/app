#include "framework.h"

namespace sockets
{

   namespace http
   {

      batch_file::batch_file(::ca::application * papp) :
         ca(papp)
      {
      }

      BOOL batch_file::open(const char * lpszFileName, UINT nOpenFlags, ::ex1::file_exception_sp * pError)
      {
         UNREFERENCED_PARAMETER(pError);
         m_strPath = lpszFileName;
         m_nOpenFlags = nOpenFlags;
         if(m_nOpenFlags & ex1::file::mode_read)
         {
             get_file_data();
         }
         return TRUE;
      }
      
      void batch_file::close()
      {
         if(m_nOpenFlags & ex1::file::mode_write)
         {
            set_file_data();
         }
      }

      void batch_file::Flush()
      {
         if(m_nOpenFlags & ex1::file::mode_write)
         {
            set_file_data();
         }
      }

   } // namespace http

} // namespace sockets