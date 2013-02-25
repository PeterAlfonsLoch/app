#include "framework.h"


namespace sockets
{


   namespace http
   {


      batch_file::batch_file(::ca::application * papp) :
         ca(papp)
      {

         m_nOpenFlags = 0;

      }

      bool batch_file::open(const char * lpszFileName, UINT nOpenFlags)
      {

         m_strPath = lpszFileName;

         m_nOpenFlags = nOpenFlags;

         if(m_nOpenFlags & ::ca::file::mode_read)
         {

             get_file_data();

         }

         return TRUE;

      }
      
      void batch_file::close()
      {
         if(m_nOpenFlags & ::ca::file::mode_write)
         {
            set_file_data();
         }
      }

      void batch_file::flush()
      {
         if(m_nOpenFlags & ::ca::file::mode_write)
         {
            set_file_data();
         }
      }


   } // namespace http


} // namespace sockets


