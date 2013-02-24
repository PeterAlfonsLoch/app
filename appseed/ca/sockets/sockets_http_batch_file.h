#pragma once


namespace sockets
{


   namespace http
   {


      class CLASS_DECL_ca batch_file : 
         virtual public ::ca::file
      {
      public:

         UINT                 m_nOpenFlags;
         string               m_strPath;



         batch_file(::ca::application * papp);

         virtual bool open(const char * lpszFileName, UINT nOpenFlags);
         virtual void close();
         virtual void flush();

         virtual void get_file_data() = 0;
         virtual void set_file_data() = 0;


      };


   } // namespace http


} // namespace sockets




