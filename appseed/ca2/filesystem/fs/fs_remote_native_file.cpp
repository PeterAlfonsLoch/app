#include "framework.h"


namespace fs
{


   remote_native_file::remote_native_file(sp(base_application) papp, var varFile) :
      element(papp),
      ::sockets::http::batch_file(papp),
      m_httpfile(new ::sockets::http::file(papp)),
      m_memfile(papp),
      m_varFile(varFile)
   {
   }

   remote_native_file::~remote_native_file()
   {
   }

   ::primitive::memory_size remote_native_file::read(void *lpBuf, ::primitive::memory_size nCount)
   {
      return m_httpfile->read(lpBuf, nCount);
   }

   void remote_native_file::write(const void * lpBuf, ::primitive::memory_size nCount)
   {
      m_memfile.write(lpBuf, nCount);
   }


   file_size remote_native_file::get_length() const
   {
      if((m_nOpenFlags & ::file::mode_read) != 0)
      {
         return m_httpfile->get_length();
      }
      else
      {
         return m_memfile.get_length();
      }
   }

   file_position remote_native_file::seek(file_offset lOff, ::file::e_seek nFrom)
   {
      if((m_nOpenFlags & ::file::mode_read) != 0)
      {
         return m_httpfile->seek(lOff, nFrom);
      }
      else
      {
         return m_memfile.seek(lOff, nFrom);
      }
   }


   void remote_native_file::get_file_data()
   {
      /*if(m_nOpenFlags & ::file::file::mode_write)
      {
      throw "Cannot open remote_native_file for reading and writing simultaneously due the characteristic of possibility of extreme delayed streaming. The way it is implemented would also not work.\n It is build with this premisse.";
      return;
      }*/

      string strUrl;

      strUrl = "http://fs.veriwell.net/fs/get?path=" + System.url().url_encode(System.url().get_script(m_strPath))
         + "&server=" + System.url().url_encode(System.url().get_server(m_strPath));

      uint32_t dwAdd = 0;

      if(m_nOpenFlags & hint_unknown_length_supported)
      {
         dwAdd |= hint_unknown_length_supported;
      }

      m_httpfile->open(strUrl, ::file::type_binary | ::file::mode_read | dwAdd);
   }

   void remote_native_file::set_file_data()
   {
      string strUrl;


      if(m_varFile["xmledit"].element < ::primitive::memory_file > () != NULL)
      {

         strUrl = "http://fs.veriwell.net/fs/xmledit?path=" + System.url().url_encode(System.url().get_script(m_varFile["url"]))
            + "&server=" + System.url().url_encode(System.url().get_server(m_varFile["url"]));

         string strResponse;

         Application.http().put(strResponse, strUrl, m_varFile["xmledit"].element < ::primitive::memory_file >());

         property_set set(get_app());

         set.parse_url_query(strResponse);

         string strMd5Here = System.crypt().md5(*m_varFile["xml"].element < ::primitive::memory_file >()->get_primitive_memory());
         string strMd5There = set["md5"];

         if(strMd5Here == strMd5There)
            return;

         strUrl = "http://fs.veriwell.net/fs/set?path=" + System.url().url_encode(System.url().get_script(m_varFile["url"]))
            + "&server=" + System.url().url_encode(System.url().get_server(m_varFile["url"]));

         Application.http().put(strUrl, m_varFile["xml"].element < ::primitive::memory_file >());

         return;
      }


      strUrl = "http://fs.veriwell.net/fs/set?path=" + System.url().url_encode(System.url().get_script(m_strPath))
         + "&server=" + System.url().url_encode(System.url().get_server(m_strPath));

      Application.http().put(strUrl, &m_memfile);


   }



} // namespace fs



