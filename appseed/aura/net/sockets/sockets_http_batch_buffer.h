#pragma once


namespace sockets
{


   class CLASS_DECL_AURA http_batch_buffer : 
      virtual public ::file::binary_file
   {
   public:

      UINT                 m_nOpenFlags;
      string               m_strPath;



      http_batch_buffer(::aura::application * papp);

      virtual cres open(const char * lpszFileName, UINT nOpenFlags);
      virtual void close();
      virtual void flush();

      virtual void get_file_data() = 0;
      virtual void set_file_data() = 0;


   };

} // namespace sockets




